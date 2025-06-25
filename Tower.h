#pragma once
#include"BoardPosition.h"
class Tower {
public:
	virtual ~Tower() {};
    
    //Ѫ��
	virtual int getHP() const = 0;
    virtual bool isAlive() const = 0;
    virtual void takeDamage(int amount) = 0;// �ܵ��˺�

    // λ����Ϣ
    virtual BoardPosition getPosition() const = 0;
    virtual void setPosition(const BoardPosition& pos) = 0;

    // �����ͱ�ʶ
    virtual bool isKingTower() const = 0;
    virtual bool isPrincessTower() const = 0;

    // ��������
    virtual int getAttackRange() const = 0;
    virtual int getDamage() const = 0;
};

class KingTower : public Tower {
    int hp;
    BoardPosition position;

public:
    KingTower(const BoardPosition& pos, const int initialHP)
        : position(pos), hp(initialHP) {
    }

    int getHP() const override { return hp; }
    bool isAlive() const override { return hp > 0; }
    void takeDamage(int amount) override {
        hp = (hp > amount) ? (hp - amount) : 0;
    }

    BoardPosition getPosition() const override { return position; }
    void setPosition(const BoardPosition& pos) override { position = pos; }//����Ӧ���Ǿ����λ��

    bool isKingTower() const override { return true; }
    bool isPrincessTower() const override { return false; }

    // ��������
    int getAttackRange() const override { return 7; }
    int getDamage() const override { return 100; }
};