#pragma once
#include <iostream>

class ICard {
public:
    virtual ~ICard() = default;

    // 基本信息
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual int getCost() const = 0;          // 费用
    virtual std::string getRarity() const = 0; // 稀有度

    // 使用卡牌
    virtual void playCard() = 0;

    // 升级系统
    virtual int getLevel() const = 0;
    virtual bool canUpgrade() const = 0;
    virtual void upgrade() = 0;

};

class Card : public ICard {
public:

};