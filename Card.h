#pragma once
#include <iostream>
#include<vector>
#include"Unit.h"
#include"Board.h"
#include"BoardPosition.h"

class ICard {
protected:
    std::string name;
    std::string description;
    int cost;
    std::string rarity;
    int level;
public:
    ICard(std::string n, std::string desc, int c,std::string r, int lv = 1)
        : name(n), description(desc), cost(c), rarity(r), level(lv) {}
    virtual ~ICard() = default;

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
    virtual void play(BoardPosition position) = 0;
};

class UnitCard : public ICard {
public:
    UnitCard(std::string n, std::string desc, int c,std::string r, std::string type, int lv = 1)
        : ICard(n, desc, c, r, lv) {}

    // ICard�ӿ�ʵ��
    std::string getType() const override { return "unit"; }

    
    void upgrade() override {
        if (canUpgrade()) {
            level++;
            //ȱ��������λ������������
        }
    }

    // ��ָ��λ�÷��õ�λ
    void play(BoardPosition position) override {
        // ͨ������������λ����������unitType������Ӧ��λ��
        Unit* unit = UnitFactory::createUnit(name, level);
        unit->setPosition(position);

        // ����λ��ӵ�����
        Board::addUnit(unit);
        std::cout << "Placed " << name << " at ("<< position.row << "," << position.col << ")\n";
    }
};

class SpellCard : public ICard {
private:
    float radius; // ���ð뾶
public:
    SpellCard(std::string n, std::string desc, int c,std::string r, std::string type, float rad, int lv = 1)
        : ICard(n, desc, c, r, lv), radius(rad) {}

    std::string getType() const override { return "spell"; }
    

    void upgrade() override {
        if (canUpgrade()) {
            level++;
            // ��������Ч����ǿ

        }
    }

    // ��ָ��λ���ͷŷ���
    void play(BoardPosition position) override {
        Board& board = new Board;

        // �ҵ�λ�÷�Χ�ڵĵ�λ
        std::vector<IUnit*> unitsInRange = Board::getUnitsInRange(position, radius);

        // ���ݷ�������ִ��Ч��
        if (spellType == "Fireball") {
            for (IUnit* unit : unitsInRange) {
                unit->takeDamage(150 * level); // �����˺����Եȼ�
            }
        }
        else if (spellType == "Arrows") {
            for (IUnit* unit : unitsInRange) {
                unit->takeDamage(100 * level);
            }
        }
        // ������������...

        std::cout << "Cast " << name << " at ("
            << position.row << "," << position.col << ")\n";
    }
};
