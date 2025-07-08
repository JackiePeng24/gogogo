#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
#include "Tower.h"

class Board {
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<Tower> towers;

    // 游戏状态
    bool gameActive = false;

public:
    void startNewGame() {
        units.clear();
        towers.clear();

        // 添加初始塔
        towers.push_back(createKingTower(true));
        towers.push_back(createPrincessTower(true, true));
        towers.push_back(createPrincessTower(true, false));

        towers.push_back(createKingTower(false));
        towers.push_back(createPrincessTower(false, true));
        towers.push_back(createPrincessTower(false, false));

        gameActive = true;
    }

    void endGame() { gameActive = false; }
    bool isGameActive() const { return gameActive; }

    void addUnit(std::unique_ptr<Unit> unit, const std::string& owner) {
        if (!gameActive) return;
        units.push_back(std::move(unit));
    }

    void addTower(Tower tower) {
        towers.push_back(tower);
    }

    std::vector<Unit*> getUnitsInRange(BoardPosition center, float radius) {
        std::vector<Unit*> result;
        for (auto& unit : units) {
            if (unit->getPosition().distance(center) <= radius * radius) {
                result.push_back(unit.get());
            }
        }
        return result;
    }

    void update(float deltaTime) {
        for (auto& unit : units) {
            unit->update(deltaTime);
        }

        // 检查游戏结束条件
        checkGameEnd();
    }

private:
    void checkGameEnd() {
        bool player1KingAlive = false;
        bool player2KingAlive = false;

        for (auto& tower : towers) {
            if (tower.isAlive()) {
                if (tower.getPosition().row < 8) { // 假设上半场是玩家1
                    if (tower.isKingTower()) player1KingAlive = true;
                }
                else {
                    if (tower.isKingTower()) player2KingAlive = true;
                }
            }
        }

        if (!player1KingAlive || !player2KingAlive) {
            endGame();
        }
    }
};