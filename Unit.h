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

    // ս��״̬
    BoardPosition targetPosition;
    Unit* attackTarget = nullptr;
    float attackCooldown = 0.0f;

public:
    Unit(std::string unitName, int health, int dmg, float atkSpeed, float mvSpeed, int range)
        : name(unitName), hp(health), damage(dmg), attackSpeed(atkSpeed),
        moveSpeed(mvSpeed), attackRange(range) {
    }

    virtual ~Unit() = default;

    // ������Ϣ
    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getDamage() const { return damage; }
    float getAttackSpeed() const { return attackSpeed; }
    float getMovementSpeed() const { return moveSpeed; }
    int getAttackRange() const { return attackRange; }

    // λ�ú�״̬
    BoardPosition getPosition() const { return position; }
    void setPosition(BoardPosition& pos) { position = pos; }
    bool isAlive() const { return hp > 0; }

    // �ƶ�
    void moveTowards(const BoardPosition& target) {
        //��ҪѰ·ϵͳ
    }

    // ս��
    void attack(Unit* target) {
        attackTarget = target;
    }

    void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    // ����״̬
    void update(float deltaTime) {
        if (!isAlive()) return;

        if (attackTarget) {
            // �����߼�
            attackCooldown -= deltaTime;
            if (attackCooldown <= 0) {
                attackTarget->takeDamage(damage);
                attackCooldown = 1.0f / attackSpeed;
            }
        }
        else {
            // �ƶ��߼�
            // ��ʵ�֣�ֱ���ƶ�
            // ʵ����Ŀ��Ӧ���Ѱ·
        }
    }

    // �����������򻯣�
    bool hasSpecialAbility() const { return false; }
    void activateAbility() {}
};