#include<iostream>
#include "Card.h"
#include "Player.h"
#include "Board.h"
#include "Unit.h"

class UnitCard : public Card {
private:
    int baseHealth;       // 基础生命值
    int baseDamage;       // 基础伤害值

public:
    std::string getType() const override { return "unit"; }

    UnitCard(std::string n, std::string desc, int c, std::string r, int health, int damage, int lv = 1)
        : Card(n, desc, c, r, lv), baseHealth(health), baseDamage(damage) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // 每级提升10%属性
            baseHealth = static_cast<int>(baseHealth * 1.1f);
            baseDamage = static_cast<int>(baseDamage * 1.1f);
        }
    }

    void play(Player& player, Board& board, BoardPosition pos) {
        std::unique_ptr<Unit> unit;
        if (name == "Knight") {
            unit = std::make_unique<Knight>(baseHealth, baseDamage, player.getPlayerId());
        }
        else if (name == "Archer") {
            unit = std::make_unique<Archer>(baseHealth, baseDamage, player.getPlayerId());
        }

        if (unit) {
            unit->setPosition(pos);
            board.addUnit(std::move(unit));
        }
    }
};

class SpellCard : public Card {
private:
    int radius;
    int baseEffect; // 法术效果值（伤害/治疗等）

public:
    SpellCard(std::string n, std::string desc, int c, std::string r,
        int rad, int effect, int lv = 1)
        : Card(n, desc, c, r, lv), radius(rad), baseEffect(effect) {
    }

    std::string getType() const override { return "spell"; }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // 每级提升15%效果
            baseEffect = static_cast<int>(baseEffect * 1.15f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;
        player.deductElixir(cost);

        bool isPlayer1 = player.getPlayerId() == 1;
        if (isPlayer1) {
            // 玩家1(上方)只能放在上半场(0-5行)
            if (position.row > 5) {
                std::cout << "错误：玩家1只能在上半场(0-5行)放置单位！\n";
                return;
            }
        }
        else {
            // 玩家2(下方)只能放在下半场(7-12行)
            if (position.row < 7) {
                std::cout << "错误：玩家2只能在下半场(7-12行)放置单位！\n";
                return;
            }
        }

        // 确保位置有效
        if (!position.isValid()) {
            std::cout << "错误：无效的位置坐标！\n";
            return;
        }

        // 获取作用范围内的单位
        auto targets = board.getUnitsInRange(position, radius);

        // 根据法术类型执行效果
        if (getName() == "Fireball") {
            for (Unit* unit : targets) {
                unit->takeDamage(baseEffect);
            }
        }
        else if (getName() == "Heal") {
            for (Unit* unit : targets) {
                if (unit->getOwner() == player.playerId) {
                    unit->heal(baseEffect);
                }
            }
        }
        // 添加更多法术类型
    }
};

Card* Card::createUnitCard(std::string name, std::string desc, int cost,
    std::string rarity, int health, int damage, int level) {
    return new UnitCard(name, desc, cost, rarity, health, damage, level);
}

Card* Card::createSpellCard(std::string name, std::string desc, int cost,
    std::string rarity, float radius, int effect, int level) {
    return new SpellCard(name, desc, cost, rarity, radius, effect, level);
}