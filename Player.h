#pragma once
#include "Card.h"
#include "Deck.h"
#include"BoardPosition.h"
#include <vector>

class IPlayer {
public:
    virtual ~IPlayer() = default;

    // �����Ϣ
    virtual std::string getName() const = 0;
    virtual int getLevel() const = 0;
    virtual int getTrophies() const = 0;       // ������

    // ��Դ����
    virtual float getCurrentElixir() const = 0; // ��ǰʥˮ
    virtual float getElixirRegenRate() const = 0; // ʥˮ�ָ�����

    // �������
    virtual const Deck& getCurrentDeck() const = 0;
    virtual bool setCurrentDeck(const Deck& deck) = 0;
    virtual const std::vector<ICard*>& getCollection() const = 0; // ���п���

    // ս��״̬
    virtual bool getKingTower() = 0;
    virtual bool getLeftPrincessTower() = 0;
    virtual bool getRightPrincessTower() = 0;

    // ��Ϸ����
    virtual bool playCard(int cardIndex, const BoardPosition& position) = 0;

    // ����ϵͳ
    virtual void addExperience(int amount) = 0;
    virtual void addTrophies(int amount) = 0;

};