#pragma once
#include "BoardPosition.h"

class Unit {
protected:
    std::string name;
    int hp;
    int damage;
    float attackSpeed;
    float moveSpeed;
    int attackRange;
    BoardPosition position;

    // 战斗状态
    BoardPosition targetPosition;
    Unit* attackTarget = nullptr;
    float attackCooldown = 0.0f;

public:
    Unit(std::string unitName, int health, int dmg, float atkSpeed, float mvSpeed, int range)
        : name(unitName), hp(health), damage(dmg), attackSpeed(atkSpeed),
        moveSpeed(mvSpeed), attackRange(range) {
    }

    virtual ~Unit() = default;

    // 基本信息
    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getDamage() const { return damage; }
    float getAttackSpeed() const { return attackSpeed; }
    float getMovementSpeed() const { return moveSpeed; }
    int getAttackRange() const { return attackRange; }

    // 位置和状态
    BoardPosition getPosition() const { return position; }
    void setPosition(BoardPosition& pos) { position = pos; }
    bool isAlive() const { return hp > 0; }

    // 移动
    void moveTowards(const BoardPosition& target) {
        //需要寻路系统
    }

    // 战斗
    void attack(Unit* target) {
        attackTarget = target;
    }

    void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    // 更新状态
    void update(float deltaTime) {
        if (!isAlive()) return;

        if (attackTarget) {
            // 攻击逻辑
            attackCooldown -= deltaTime;
            if (attackCooldown <= 0) {
                attackTarget->takeDamage(damage);
                attackCooldown = 1.0f / attackSpeed;
            }
        }
        else {
            // 移动逻辑
            // 简化实现：直线移动
            // 实际项目中应添加寻路
        }
    }

    // 特殊能力（简化）
    bool hasSpecialAbility() const { return false; }
    void activateAbility() {}
};