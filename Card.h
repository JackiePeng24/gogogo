#pragma once
#include <iostream>
#include<vector>
#include"Unit.h"
#include"Board.h"
#include"BoardPosition.h"

class ICard {
protected:
    std::string name;
    std::string description;
    int cost;
    std::string rarity;
    int level;
public:
    ICard(std::string n, std::string desc, int c,std::string r, int lv = 1)
        : name(n), description(desc), cost(c), rarity(r), level(lv) {}
    virtual ~ICard() = default;

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
    virtual void play(BoardPosition position) = 0;
};

class UnitCard : public ICard {
public:
    UnitCard(std::string n, std::string desc, int c,std::string r, std::string type, int lv = 1)
        : ICard(n, desc, c, r, lv) {}

    // ICard接口实现
    std::string getType() const override { return "unit"; }

    
    void upgrade() override {
        if (canUpgrade()) {
            level++;
            //缺少升级后单位属性提升内容
        }
    }

    // 在指定位置放置单位
    void play(BoardPosition position) override {
        // 通过工厂创建单位（工厂根据unitType创建对应单位）
        Unit* unit = UnitFactory::createUnit(name, level);
        unit->setPosition(position);

        // 将单位添加到棋盘
        Board::addUnit(unit);
        std::cout << "Placed " << name << " at ("<< position.row << "," << position.col << ")\n";
    }
};

class SpellCard : public ICard {
private:
    float radius; // 作用半径
public:
    SpellCard(std::string n, std::string desc, int c,std::string r, std::string type, float rad, int lv = 1)
        : ICard(n, desc, c, r, lv), radius(rad) {}

    std::string getType() const override { return "spell"; }
    

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // 升级后法术效果增强

        }
    }

    // 在指定位置释放法术
    void play(BoardPosition position) override {
        Board& board = new Board;

        // 找到位置范围内的单位
        std::vector<IUnit*> unitsInRange = Board::getUnitsInRange(position, radius);

        // 根据法术类型执行效果
        if (spellType == "Fireball") {
            for (IUnit* unit : unitsInRange) {
                unit->takeDamage(150 * level); // 基础伤害乘以等级
            }
        }
        else if (spellType == "Arrows") {
            for (IUnit* unit : unitsInRange) {
                unit->takeDamage(100 * level);
            }
        }
        // 其他法术类型...

        std::cout << "Cast " << name << " at ("
            << position.row << "," << position.col << ")\n";
    }
};
