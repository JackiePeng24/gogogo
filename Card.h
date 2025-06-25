#pragma once
#include <iostream>

class ICard {
public:
    virtual ~ICard() = default;

    // ������Ϣ
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual int getCost() const = 0;          // ����
    virtual std::string getRarity() const = 0; // ϡ�ж�

    // ʹ�ÿ���
    virtual void playCard() = 0;

    // ����ϵͳ
    virtual int getLevel() const = 0;
    virtual bool canUpgrade() const = 0;
    virtual void upgrade() = 0;

};

class Card : public ICard {
public:

};