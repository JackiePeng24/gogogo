#pragma once
#include<iostream>
#include"BoardPosition.h"
#include"GameConstants.h"

class Tower {
protected:
    int hp;
    int attackRange;
    int damage;
    BoardPosition position;
    bool whose;

public:
    Tower(int hp, int attackRange, int damage, bool whose)
        : hp(hp), attackRange(attackRange), damage(damage), whose(whose) {
    }
    //血量
    int getHP() {return hp; }
    bool isAlive() {return hp > 0; }
    void takeDamage(int amount) {hp = (hp > amount) ? (hp - amount) : 0; };// 受到伤害

    // 位置信息
    BoardPosition getPosition() {return position; }
    virtual void setPosition() = 0;

    // 塔标识
    virtual bool isKingTower() const = 0;
    virtual bool isPrincessTower() const = 0;
    bool isWhoseTower() const { return whose; }


    // 攻击能力
    int getAttackRange() {return attackRange; }
    int getDamage() {return damage; }
    
};

class KingTower : virtual public Tower {
public:
    KingTower(const bool Whose)
        : Tower(GameConstants::Tower::KING_HP,
            GameConstants::Tower::KING_ATTACK_RANGE,
            GameConstants::Tower::KING_DAMAGE,
            Whose){}

    int getHP() { return GameConstants::Tower::KING_HP;}

    void setPosition() override {
        if (whose) {
            position = GameConstants::Tower::KING_POS_1;
        }
        else {
            position = GameConstants::Tower::KING_POS_2;
        }
    }

    bool isKingTower() const override { return true; }
    bool isPrincessTower() const override { return false; }

    // 攻击属性
    int getAttackRange() const {return GameConstants::Tower::KING_ATTACK_RANGE; }
    int getDamage() const {  return GameConstants::Tower::KING_DAMAGE; }
};

class PrincessTower : virtual public Tower {
protected:
    bool lr;//左右
public:
    PrincessTower(const bool Whose, const bool LR)
        : Tower(GameConstants::Tower::PRINCESS_HP,
            GameConstants::Tower::PRINCESS_ATTACK_RANGE,
            GameConstants::Tower::PRINCESS_DAMAGE,
            Whose),
        lr(LR){}

    

    void setPosition() override {
        BoardPosition positions[2][2] = {
       {GameConstants::Tower::LEFT_PRINCESS_POS_1, GameConstants::Tower::RIGHT_PRINCESS_POS_1},
       {GameConstants::Tower::LEFT_PRINCESS_POS_2, GameConstants::Tower::RIGHT_PRINCESS_POS_2}
        };
        position = positions[whose][lr];
    }

    bool isKingTower() const override { return false; }
    bool isPrincessTower() const override { return true; }

    // 攻击属性
    int getAttackRange() const { return attackRange; }
    int getDamage() const { return damage; }
};