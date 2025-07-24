#pragma once
#include <iostream>
#include<vector>
#include"Unit.h"
#include"Player.h"
#include"Board.h"
#include"BoardPosition.h"

class Card {
protected:
    std::string name;
    std::string description;
    int cost;
    std::string rarity;
    int level;
public:
    Card(std::string n, std::string desc, int c,std::string r, int lv = 1)
        : name(n), description(desc), cost(c), rarity(r), level(lv) {}
    virtual ~Card() = default;

    // 基本信息
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getCost() const { return cost; }
    std::string getRarity() const { return rarity; }
    virtual std::string getType() const = 0;   // 卡牌类型（放置单位或者施用法术）

    // 升级系统
    int getLevel() const { return level; }
    bool canUpgrade() const { return level < 10; }
    virtual void upgrade() = 0;

    // 使用卡牌
    virtual void play(Player& player, Board& board, BoardPosition position) = 0;
};

class UnitCard : public Card {
private:
    std::string unitType; // 单位类型标识
    int baseHealth;       // 基础生命值
    int baseDamage;       // 基础伤害值

public:
    UnitCard(std::string n, std::string desc, int c, std::string r,
        std::string type, int health, int damage, int lv = 1)
        : Card(n, desc, c, r, lv), unitType(type),
        baseHealth(health), baseDamage(damage) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // 每级提升10%属性
            baseHealth = static_cast<int>(baseHealth * 1.1f);
            baseDamage = static_cast<int>(baseDamage * 1.1f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;

        player.deductElixir(cost); // 扣除圣水

        // 创建单位并添加到战场
        std::unique_ptr<Unit> unit;
        if (unitType == "knight") {
            unit = std::make_unique<Knight>(baseHealth, baseDamage, player.isPlayer1);
        }
        else if (unitType == "archer") {
            unit = std::make_unique<Archer>(baseHealth, baseDamage, player.isPlayer1);
        }
        // 添加更多单位类型...

        unit->setPosition(position);
        board.addUnit(std::move(unit));
    }
};

class SpellCard : public Card {
private:
    float radius;
    int baseEffect; // 法术效果值（伤害/治疗等）

public:
    SpellCard(std::string n, std::string desc, int c, std::string r,
        float rad, int effect, int lv = 1)
        : Card(n, desc, c, r, lv), radius(rad), baseEffect(effect) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // 每级提升15%效果
            baseEffect = static_cast<int>(baseEffect * 1.15f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;

        player.deductElixir(cost); // 扣除圣水

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
                if (unit->getOwner() == player.isPlayer1) {
                    unit->heal(baseEffect);
                }
            }
        }
        // 添加更多法术类型
    }
};
