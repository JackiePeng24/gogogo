#pragma once
#include <iostream>
#include<vector>


class Board;
class Player;
struct BoardPosition;
class Unit;


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

    // 创建卡牌
    static Card* createUnitCard(std::string name, std::string desc, int cost,
        std::string rarity, int health, int damage, int level = 1);

    static Card* createSpellCard(std::string name, std::string desc, int cost,
        std::string rarity, float radius, int effect, int level = 1);
};

