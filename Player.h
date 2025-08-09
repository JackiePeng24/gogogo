#pragma once
class Card;
class Board;

#include<iostream>
#include <vector>
#include <memory>
#include "Deck.h"
#include "GameConstants.h"
#include "BoardPosition.h"

// Player.h
class Player {
public:
    std::string name;
    int trophies = 0;
    float currentElixir = 5.0f;  // ��ʼʥˮֵ
    float elixirRegenRate = 0.8f; // ÿ��ָ�0.8��ʥˮ
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    int playerId = -1;

    // ʥˮ�ָ���ʱ��
    float elixirTimer = 0.0f;

    Player(std::string playerName) : name(playerName) {}

    //������Ϣ
    void setPlayerId(int id) { playerId = id; }
    int getPlayerId() const { return playerId; }
    std::string getName() const { return name; }
    int getTrophies() const { return trophies; }
    float getCurrentElixir() const { return currentElixir; }
    float getElixirRegenRate() const { return elixirRegenRate; }

    Deck& getCurrentDeck() const { return *currentDeck; }
    bool setCurrentDeck(const Deck& deck) {
        currentDeck = std::make_unique<Deck>(deck);
        return true;
    }

    const std::vector<Card*>& getCollection() const { return collection; }

    bool setbattleDeck(const std::vector<std::string>& cardNames);

    // ʹ�ÿ���
    bool playCard(int handIndex, BoardPosition position, Board& board);


    // ʥˮ�۳�����
    void deductElixir(int amount) {
        currentElixir = std::max(0.0f, currentElixir - amount);
    }

    // ����ʥˮ
    void update(float deltaTime);

    // ��ӿ��Ƶ����ƿ�
    void addCardToCollection(Card* card);
};