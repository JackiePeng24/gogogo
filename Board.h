#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Unit.h"
#include "Tower.h"
#include "GameConstants.h"

class Board {
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<std::unique_ptr<Tower>> towers;
    bool gameActive = false;

    // ������
    std::unique_ptr<Tower> createKingTower(bool isPlayer1) {
        std::unique_ptr<KingTower> tower = std::make_unique<KingTower>(isPlayer1);
        tower->setPosition();
        return tower;
    }

    std::unique_ptr<Tower> createPrincessTower(bool isPlayer1, bool isLeft) {
        std::unique_ptr<PrincessTower> tower = std::make_unique<PrincessTower>(isPlayer1, isLeft);
        tower->setPosition();
        return tower;
    }

    void removeDeadUnits() {
        units.erase(
            std::remove_if(units.begin(), units.end(),
                [](const std::unique_ptr<Unit>& unit) {
                    return !unit->isAlive();
                }),
            units.end());
    }

    // Ŀ������߼�
    void assignTargets() {
        for (auto& unit : units) {
            if (unit->isAlive()) {
                // ���û��Ŀ���Ŀ��������
                if (!unit->getAttackTarget() || !unit->getAttackTarget()->isAlive()) {
                    // ����Ѱ������ĵз���λ
                    Unit* closestEnemy = findClosestEnemyUnit(unit.get());

                    if (closestEnemy) {
                        unit->setAttackTarget(closestEnemy);
                    }
                    else {
                        // û�ез���λ��Ѱ������ĵз���
                        Tower* closestTower = findClosestEnemyTower(unit.get());
                        if (closestTower) {
                            unit->setMoveTarget(closestTower->getPosition());
                        }
                    }
                }
            }
        }
    }
    // Ѱ�Ҿ��뵥λ����ĵз���λ
    Unit* findClosestEnemyUnit(Unit* unit) const {
        if (!unit || !unit->isAlive()) return nullptr;

        auto potentialTargets = getUnitsInRange(unit->getPosition(), unit->getAttackRange());
        Unit* closest = nullptr;
        float minDist = std::numeric_limits<float>::max();
        int owner = unit->getOwner();

        for (auto* enemy : potentialTargets) {
            if (enemy->getOwner() != owner) {
                float dist = unit->getPosition().distance(enemy->getPosition());
                if (dist < minDist) {
                    minDist = dist;
                    closest = enemy;
                }
            }
        }
        return closest;
    }

    // Ѱ�Ҿ��뵥λ����ĵз���
    Tower* findClosestEnemyTower(Unit* unit) const {
        if (!unit || !unit->isAlive()) return nullptr;

        Tower* closest = nullptr;
        float minDist = std::numeric_limits<float>::max();
        int owner = unit->getOwner();

        for (auto& tower : towers) {
            if (!tower->isAlive() || tower->isWhoseTower() == owner)
                continue;

            float dist = unit->getPosition().distance(tower->getPosition());
            if (dist < minDist) {
                minDist = dist;
                closest = tower.get();
            }
        }

        return closest;
    }

    //�������Ĺ�������
    void updateTowers(float deltaTime) {
        for (auto& tower : towers) {
            if (!tower->isAlive()) continue;

            auto targets = getUnitsInRange(tower->getPosition(), tower->getAttackRange(), tower->isWhoseTower());
            if (!targets.empty()) {
                targets[0]->takeDamage(tower->getDamage());
            }
        }
    }

    // �����Ϸ�Ƿ����
    void checkGameEnd() {
        bool player1KingAlive = false;
        bool player2KingAlive = false;

        for (auto& tower : towers) {
            if (tower->isAlive() && tower->isKingTower()) {
                if (tower->isWhoseTower()) {
                    player1KingAlive = true;
                }
                else {
                    player2KingAlive = true;
                }
            }
        }

        if (!player1KingAlive || !player2KingAlive) {
            endGame();
        }
    }

public:
    const std::vector<std::unique_ptr<Unit>>& getUnits() const { return units; }
    const std::vector<std::unique_ptr<Tower>>& getTowers() const { return towers; }

    void startNewGame() {
        units.clear();
        towers.clear();

        // ʹ��GameConstants�еĳ���
        towers.push_back(createKingTower(true));  // ���1������
        towers.push_back(createPrincessTower(true, true));  // ���1������
        towers.push_back(createPrincessTower(true, false)); // ���1�ҹ�����

        towers.push_back(createKingTower(false)); // ���2������
        towers.push_back(createPrincessTower(false, true));  // ���2������
        towers.push_back(createPrincessTower(false, false)); // ���2�ҹ�����

        gameActive = true;
    }

    void endGame() { gameActive = false; }
    bool isGameActive() const { return gameActive; }

    void addUnit(std::unique_ptr<Unit> unit) {
        if (!gameActive) return;
        units.push_back(std::move(unit));
    }

    // ��ȡ���й�����Χ�ڵĵз���λ
    std::vector<Unit*> getUnitsInRange(BoardPosition center, float radius, int allyOwner = -1) const {
        std::vector<Unit*> result;
        for (auto& unit : units) {
            if (unit->isAlive() && unit->getPosition().distance(center) <= radius * radius &&
                (allyOwner == -1 || unit->getOwner() != allyOwner)) {
                result.push_back(unit.get());
            }
        }
        return result;
    }

    void update(float deltaTime) {
        if (!gameActive) return;

        assignTargets();

        for (auto& unit : units) {
            unit->update(deltaTime);
        }

        updateTowers(deltaTime);

        removeDeadUnits();

        checkGameEnd();
    }
};
