#pragma once
#include <iostream>
#include<vector>
#include"Unit.h"
#include"Player.h"
#include"Board.h"
#include"BoardPosition.h"

class Card {
protected:
    std::string name;
    std::string description;
    int cost;
    std::string rarity;
    int level;
public:
    Card(std::string n, std::string desc, int c,std::string r, int lv = 1)
        : name(n), description(desc), cost(c), rarity(r), level(lv) {}
    virtual ~Card() = default;

    // ������Ϣ
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getCost() const { return cost; }
    std::string getRarity() const { return rarity; }
    virtual std::string getType() const = 0;   // �������ͣ����õ�λ����ʩ�÷�����

    // ����ϵͳ
    int getLevel() const { return level; }
    bool canUpgrade() const { return level < 10; }
    virtual void upgrade() = 0;

    // ʹ�ÿ���
    virtual void play(Player& player, Board& board, BoardPosition position) = 0;
};

class UnitCard : public Card {
private:
    std::string unitType; // ��λ���ͱ�ʶ
    int baseHealth;       // ��������ֵ
    int baseDamage;       // �����˺�ֵ

public:
    UnitCard(std::string n, std::string desc, int c, std::string r,
        std::string type, int health, int damage, int lv = 1)
        : Card(n, desc, c, r, lv), unitType(type),
        baseHealth(health), baseDamage(damage) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // ÿ������10%����
            baseHealth = static_cast<int>(baseHealth * 1.1f);
            baseDamage = static_cast<int>(baseDamage * 1.1f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;

        player.deductElixir(cost); // �۳�ʥˮ

        // ������λ����ӵ�ս��
        std::unique_ptr<Unit> unit;
        if (unitType == "knight") {
            unit = std::make_unique<Knight>(baseHealth, baseDamage, player.isPlayer1);
        }
        else if (unitType == "archer") {
            unit = std::make_unique<Archer>(baseHealth, baseDamage, player.isPlayer1);
        }
        // ��Ӹ��൥λ����...

        unit->setPosition(position);
        board.addUnit(std::move(unit));
    }
};

class SpellCard : public Card {
private:
    float radius;
    int baseEffect; // ����Ч��ֵ���˺�/���Ƶȣ�

public:
    SpellCard(std::string n, std::string desc, int c, std::string r,
        float rad, int effect, int lv = 1)
        : Card(n, desc, c, r, lv), radius(rad), baseEffect(effect) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // ÿ������15%Ч��
            baseEffect = static_cast<int>(baseEffect * 1.15f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;

        player.deductElixir(cost); // �۳�ʥˮ

        // ��ȡ���÷�Χ�ڵĵ�λ
        auto targets = board.getUnitsInRange(position, radius);

        // ���ݷ�������ִ��Ч��
        if (getName() == "Fireball") {
            for (Unit* unit : targets) {
                unit->takeDamage(baseEffect);
            }
        }
        else if (getName() == "Heal") {
            for (Unit* unit : targets) {
                if (unit->getOwner() == player.isPlayer1) {
                    unit->heal(baseEffect);
                }
            }
        }
        // ��Ӹ��෨������
    }
};
