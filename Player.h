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
    virtual const std::vector<Card*>& getCollection() const = 0; // ���п���

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

// Player.h
class Player : public IPlayer {
public:
    std::string name;
    int trophies;
    float currentElixir = 5.0f;  // ��ʼʥˮֵ
    float elixirRegenRate = 0.8f; // ÿ��ָ�0.8��ʥˮ
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    bool isPlayer1;  // ��ұ�ʶ

    // ʥˮ�ָ���ʱ��
    float elixirTimer = 0.0f;

    Player(std::string playerName, bool player1)
        : name(playerName), isPlayer1(player1) {
    }

    // ʵ��IPlayer�ӿ�
    std::string getName() const override { return name; }
    int getLevel() const override { return 1; } // ��ʵ��
    int getTrophies() const override { return trophies; }
    float getCurrentElixir() const override { return currentElixir; }
    float getElixirRegenRate() const override { return elixirRegenRate; }

    const Deck& getCurrentDeck() const override { return *currentDeck; }
    bool setCurrentDeck(const Deck& deck) override {
        currentDeck = std::make_unique<Deck>(deck);
        return true;
    }

    const std::vector<Card*>& getCollection() const override { return collection; }

    // ʥˮ�۳�����
    void deductElixir(int amount) {
        currentElixir = std::max(0.0f, currentElixir - amount);
    }

    // ����ʥˮ
    void update(float deltaTime) {
        elixirTimer += deltaTime;
        if (elixirTimer >= 1.0f) {
            currentElixir = std::min(currentElixir + elixirRegenRate, 10.0f);
            elixirTimer = 0.0f;
        }
    }

    // ��ӿ��Ƶ����ƿ�
    void addCardToCollection(Card* card) {
        collection.push_back(card);
    }
};