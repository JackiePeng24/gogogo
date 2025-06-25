#pragma once
#include "BoardPosition.h"

class IUnit {
public:
    virtual ~IUnit() = default;

    // 基本属性
    virtual std::string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getDamage() const = 0;
    virtual float getAttackSpeed() const = 0;  // 攻击间隔
    virtual float getMovementSpeed() const = 0; // 移动速度
    virtual int getAttackRange() const = 0;    // 攻击范围

    // 位置与状态
    virtual BoardPosition getPosition() const = 0;
    virtual void setPosition(const BoardPosition& pos) = 0;
    virtual bool isAlive() const = 0;

    // 行为
    virtual void moveTowards(const BoardPosition& target) = 0;
    virtual void attack(IUnit* target) = 0;
    virtual void takeDamage(int amount) = 0;

    // 特殊能力
    virtual bool hasSpecialAbility() const = 0;
    virtual void activateAbility() = 0;
};