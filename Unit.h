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

    // ս��״̬
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
    // ������Ϣ
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

    // ����λ�ú�Ŀ��
    void setPosition(const BoardPosition& pos) { position = pos; }
    void setAttackTarget(Unit* target) { attackTarget = target; }
    void setMoveTarget(const BoardPosition& target) {
        moveTarget = target;
        isMoving = true;
    }

    // ս��
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
        // ����Ѿ���Ŀ��λ�ã�ֹͣ�ƶ�
        if (position == target) {
            isMoving = false;
            return;
        }

        // �����ƶ����򣨽������������ƶ���
        int rowDir = 0;
        int colDir = 0;

        if (position.row != target.row) {
            rowDir = (target.row > position.row) ? 1 : -1;
        }

        if (position.col != target.col) {
            colDir = (target.col > position.col) ? 1 : -1;
        }

        // ���㱾֡�����ƶ��ĸ�����
        float moveAmount = moveSpeed * deltaTime;
        int moveSteps = static_cast<int>(moveAmount);
        float remainder = moveAmount - moveSteps;

        // �洢ʣ���ƶ���������һ֡
        moveRemainder += remainder;
        if (moveRemainder >= 1.0f) {
            moveSteps += 1;
            moveRemainder -= 1.0f;
        }

        // ִ���ƶ���ÿ���ƶ�һ�����ӣ�
        while (moveSteps > 0 && position != target) {
            // �����ƶ��з���
            if (rowDir != 0) {
                position.row += rowDir;
                if (position.row == target.row) rowDir = 0;
            }
            // Ȼ���ƶ��з���
            else if (colDir != 0) {
                position.col += colDir;
                if (position.col == target.col) colDir = 0;
            }

            moveSteps--;
        }

        // �������Ŀ�ֹ꣬ͣ�ƶ�
        if (position == target) {
            isMoving = false;
        }
    }

    // �ƶ���ս������
    virtual void update(float deltaTime) {
        if (!isAlive()) return;

        if (attackTarget) {
            // �����߼�
            if (position.distance(attackTarget->getPosition()) <= attackRange) {
                attackCooldown -= deltaTime;
                if (attackCooldown <= 0) {
                    attack(attackTarget);
                    attackCooldown = 1.0f / attackSpeed;
                }
            }
            else {
                // Ŀ���ڹ�����Χ�⣬��Ŀ���ƶ�
                moveTowards(attackTarget->getPosition(), deltaTime);
            }
        }
        else if (isMoving) {
            // û�й���Ŀ�꣬���ƶ�Ŀ��ǰ��
            moveTowards(moveTarget, deltaTime);
        }
    }

   

    // ���������ӿ�
    virtual bool hasSpecialAbility() const { return false; }
    virtual void useSpecialAbility() {}

    //��Ѫ
    void heal(int amount){
        if (hp + amount > maxHp ) hp = maxHp;
        hp += amount;
    }
};

// ����ĵ�λ��
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