#pragma once
#include<unordered_map>
#include "BoardPosition.h"

class Unit {
protected:
    std::string name;
    int hp;
    int maxHp = hp;
    int damage;
    float attackSpeed;
    float moveSpeed;
    int attackRange;
    BoardPosition position;
    int ownerId;

    // 战斗状态
    Unit* attackTarget = nullptr;
    BoardPosition moveTarget;
    float attackCooldown = 0.0f;
    bool isMoving = false;

    float moveRemainder = 0.0f;

    virtual int calculateDamage() const { return damage; }

public:
    Unit(std::string unitName, int health, int dmg, float atkSpeed, float mvSpeed, int range,int Id)
        : name(unitName), hp(health), damage(dmg), attackSpeed(atkSpeed),
        moveSpeed(mvSpeed), attackRange(range), ownerId(Id) {
    }

    virtual ~Unit() = default;
    // 基本信息
    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getDamage() const { return damage; }
    float getAttackSpeed() const { return attackSpeed; }
    float getMoveSpeed() const { return moveSpeed; }
    int getAttackRange() const { return attackRange; }
    int getOwner() const { return ownerId; }
    BoardPosition getPosition() const { return position; }
    bool isAlive() const { return hp > 0; }
    Unit* getAttackTarget() const { return attackTarget; }

    // 设置位置和目标
    void setPosition(const BoardPosition& pos) { position = pos; }
    void setAttackTarget(Unit* target) { attackTarget = target; }
    void setMoveTarget(const BoardPosition& target) {
        moveTarget = target;
        isMoving = true;
    }

    // 战斗
    virtual void attack(Unit* target) {
        if (target && target->isAlive()) {
            target->takeDamage(calculateDamage());
        }
    }

    void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    void moveTowards(const BoardPosition& target, float deltaTime) {
        // 如果已经在目标位置，停止移动
        if (position == target) {
            isMoving = false;
            return;
        }

        // 计算移动方向（仅限于网格线移动）
        int rowDir = 0;
        int colDir = 0;

        if (position.row != target.row) {
            rowDir = (target.row > position.row) ? 1 : -1;
        }

        if (position.col != target.col) {
            colDir = (target.col > position.col) ? 1 : -1;
        }

        // 计算本帧可以移动的格子数
        float moveAmount = moveSpeed * deltaTime;
        int moveSteps = static_cast<int>(moveAmount);
        float remainder = moveAmount - moveSteps;

        // 存储剩余移动量用于下一帧
        moveRemainder += remainder;
        if (moveRemainder >= 1.0f) {
            moveSteps += 1;
            moveRemainder -= 1.0f;
        }

        // 执行移动（每次移动一个格子）
        while (moveSteps > 0 && position != target) {
            // 优先移动行方向
            if (rowDir != 0) {
                position.row += rowDir;
                if (position.row == target.row) rowDir = 0;
            }
            // 然后移动列方向
            else if (colDir != 0) {
                position.col += colDir;
                if (position.col == target.col) colDir = 0;
            }

            moveSteps--;
        }

        // 如果到达目标，停止移动
        if (position == target) {
            isMoving = false;
        }
    }

    // 移动和战斗更新
    virtual void update(float deltaTime) {
        if (!isAlive()) return;

        if (attackTarget) {
            // 攻击逻辑
            if (position.distance(attackTarget->getPosition()) <= attackRange) {
                attackCooldown -= deltaTime;
                if (attackCooldown <= 0) {
                    attack(attackTarget);
                    attackCooldown = 1.0f / attackSpeed;
                }
            }
            else {
                // 目标在攻击范围外，向目标移动
                moveTowards(attackTarget->getPosition(), deltaTime);
            }
        }
        else if (isMoving) {
            // 没有攻击目标，向移动目标前进
            moveTowards(moveTarget, deltaTime);
        }
    }

   

    // 特殊能力接口
    virtual bool hasSpecialAbility() const { return false; }
    virtual void useSpecialAbility() {}

    //回血
    void heal(int amount){
        if (hp + amount > maxHp ) hp = maxHp;
        hp += amount;
    }
};

// 具体的单位类
class Knight : public Unit {
public:
    Knight(int health, int damage, bool isPlayer1)
        : Unit("Knight", health, damage, 1.0f, 1.0f, 1, isPlayer1 ? 1 : 2) {
    }
};

class Archer : public Unit {
public:
    Archer(int health, int damage, bool isPlayer1)
        : Unit("Archer", health, damage, 1.5f, 0.8f, 5, isPlayer1 ? 1 : 2) {
    }
};