#pragma once
#include"BoardPosition.h"
class Tower {
public:
	virtual ~Tower() {};
    
    //血量
	virtual int getHP() const = 0;
    virtual bool isAlive() const = 0;
    virtual void takeDamage(int amount) = 0;// 受到伤害

    // 位置信息
    virtual BoardPosition getPosition() const = 0;
    virtual void setPosition(const BoardPosition& pos) = 0;

    // 塔类型标识
    virtual bool isKingTower() const = 0;
    virtual bool isPrincessTower() const = 0;

    // 攻击能力
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
    void setPosition(const BoardPosition& pos) override { position = pos; }//这里应该是具体的位置

    bool isKingTower() const override { return true; }
    bool isPrincessTower() const override { return false; }

    // 攻击属性
    int getAttackRange() const override { return 7; }
    int getDamage() const override { return 100; }
};