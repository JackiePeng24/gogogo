#pragma once
#include "BoardPosition.h"

class IUnit {
public:
    virtual ~IUnit() = default;

    // ��������
    virtual std::string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getDamage() const = 0;
    virtual float getAttackSpeed() const = 0;  // �������
    virtual float getMovementSpeed() const = 0; // �ƶ��ٶ�
    virtual int getAttackRange() const = 0;    // ������Χ

    // λ����״̬
    virtual BoardPosition getPosition() const = 0;
    virtual void setPosition(const BoardPosition& pos) = 0;
    virtual bool isAlive() const = 0;

    // ��Ϊ
    virtual void moveTowards(const BoardPosition& target) = 0;
    virtual void attack(IUnit* target) = 0;
    virtual void takeDamage(int amount) = 0;

    // ��������
    virtual bool hasSpecialAbility() const = 0;
    virtual void activateAbility() = 0;
};