#pragma once
#include"BoardPosition.h"
#include"GameConstants.h"
class Tower {
private:
    int hp;
    int attackRange;
    int damage;
    BoardPosition position;
    bool whose;

public:
    //Ѫ��
    int getHP() {return hp; }
    bool isAlive() {return hp > 0; }
    void takeDamage(int amount) {hp = (hp > amount) ? (hp - amount) : 0; };// �ܵ��˺�

    // λ����Ϣ
    BoardPosition getPosition() {return position; }
    virtual void setPosition() const = 0;

    // ����ʶ
    virtual bool isKingTower() const = 0;
    virtual bool isPrincessTower() const = 0;
    bool isWhoseTower() const { return whose; }


    // ��������
    virtual int getAttackRange() const = 0;
    int getDamage() { return damage; }

    
};

class KingTower : public Tower {
private:
    int hp;
    int attackRange;
    int damage;
    BoardPosition position;
    bool whose;

public:
    KingTower(const BoardPosition& pos, const int initialHP, const int AttackRange, const int Damage, const bool Whose)
        : position(pos), hp(initialHP), attackRange(AttackRange), damage(Damage), whose(Whose) {
    }

    void setPosition() const override {
        if (whose) {
            position = KING_POS_1;
        }
    }

    bool isKingTower() const override { return true; }
    bool isPrincessTower() const override { return false; }

    // ��������
    int getAttackRange() const { return 4; }
    int getDamage() const { return 100; }
};

class PrincessTower : public Tower {
private:
    int hp;
    int attackRange;
    int damage;
    BoardPosition position;
    bool whose;
public:
    PrincessTower(const BoardPosition& pos, const int initialHP, const int AttackRange, const int Damage)
        :position(pos), hp(initialHP), attackRange(AttackRange), damage(Damage) {}

    bool isKingTower() const override { return false; }
    bool isPrincessTower() const override { return true; }

    // ��������
    int getAttackRange() const override { return 2; }
    int getDamage() const override { return 50; }
};