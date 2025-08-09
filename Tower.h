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
    //—™¡ø
    int getHP() {return hp; }
    bool isAlive() const{return hp > 0; }
    void takeDamage(int amount) {hp = (hp > amount) ? (hp - amount) : 0; };//  ‹µΩ…À∫¶

    // Œª÷√–≈œ¢
    BoardPosition getPosition() const {return position; }
    virtual void setPosition() = 0;

    // À˛±Í ∂
    virtual bool isKingTower() const = 0;
    virtual bool isPrincessTower() const = 0;
    bool isWhoseTower() const { return whose; }


    // π•ª˜∑∂Œß
    int getAttackRange() {return attackRange; }

    // …À∫¶
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

    // π•ª˜ Ù–‘
    int getAttackRange() const {return GameConstants::Tower::KING_ATTACK_RANGE; }
    int getDamage() const {  return GameConstants::Tower::KING_DAMAGE; }
};

class PrincessTower : virtual public Tower {
protected:
    bool lr;//◊Û”“
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

    // π•ª˜ Ù–‘
    int getAttackRange() const { return attackRange; }
    int getDamage() const { return damage; }
};