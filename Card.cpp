#include<iostream>
#include "Card.h"
#include "Player.h"
#include "Board.h"
#include "Unit.h"

class UnitCard : public Card {
private:
    int baseHealth;       // ��������ֵ
    int baseDamage;       // �����˺�ֵ

public:
    std::string getType() const override { return "unit"; }

    UnitCard(std::string n, std::string desc, int c, std::string r, int health, int damage, int lv = 1)
        : Card(n, desc, c, r, lv), baseHealth(health), baseDamage(damage) {
    }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // ÿ������10%����
            baseHealth = static_cast<int>(baseHealth * 1.1f);
            baseDamage = static_cast<int>(baseDamage * 1.1f);
        }
    }

    void play(Player& player, Board& board, BoardPosition pos) {
        std::unique_ptr<Unit> unit;
        if (name == "Knight") {
            unit = std::make_unique<Knight>(baseHealth, baseDamage, player.getPlayerId());
        }
        else if (name == "Archer") {
            unit = std::make_unique<Archer>(baseHealth, baseDamage, player.getPlayerId());
        }

        if (unit) {
            unit->setPosition(pos);
            board.addUnit(std::move(unit));
        }
    }
};

class SpellCard : public Card {
private:
    int radius;
    int baseEffect; // ����Ч��ֵ���˺�/���Ƶȣ�

public:
    SpellCard(std::string n, std::string desc, int c, std::string r,
        int rad, int effect, int lv = 1)
        : Card(n, desc, c, r, lv), radius(rad), baseEffect(effect) {
    }

    std::string getType() const override { return "spell"; }

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // ÿ������15%Ч��
            baseEffect = static_cast<int>(baseEffect * 1.15f);
        }
    }

    void play(Player& player, Board& board, BoardPosition position) override {
        if (player.getCurrentElixir() < cost) return;
        player.deductElixir(cost);

        bool isPlayer1 = player.getPlayerId() == 1;
        if (isPlayer1) {
            // ���1(�Ϸ�)ֻ�ܷ����ϰ볡(0-5��)
            if (position.row > 5) {
                std::cout << "�������1ֻ�����ϰ볡(0-5��)���õ�λ��\n";
                return;
            }
        }
        else {
            // ���2(�·�)ֻ�ܷ����°볡(7-12��)
            if (position.row < 7) {
                std::cout << "�������2ֻ�����°볡(7-12��)���õ�λ��\n";
                return;
            }
        }

        // ȷ��λ����Ч
        if (!position.isValid()) {
            std::cout << "������Ч��λ�����꣡\n";
            return;
        }

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
                if (unit->getOwner() == player.playerId) {
                    unit->heal(baseEffect);
                }
            }
        }
        // ��Ӹ��෨������
    }
};

Card* Card::createUnitCard(std::string name, std::string desc, int cost,
    std::string rarity, int health, int damage, int level) {
    return new UnitCard(name, desc, cost, rarity, health, damage, level);
}

Card* Card::createSpellCard(std::string name, std::string desc, int cost,
    std::string rarity, float radius, int effect, int level) {
    return new SpellCard(name, desc, cost, rarity, radius, effect, level);
}