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
    float currentElixir = 5.0f;  // 初始圣水值
    float elixirRegenRate = 0.8f; // 每秒恢复0.8点圣水
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    int playerId = -1;

    // 圣水恢复计时器
    float elixirTimer = 0.0f;

    Player(std::string playerName) : name(playerName) {}

    //基本信息
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

    // 使用卡牌
    bool playCard(int handIndex, BoardPosition position, Board& board);


    // 圣水扣除方法
    void deductElixir(int amount) {
        currentElixir = std::max(0.0f, currentElixir - amount);
    }

    // 更新圣水
    void update(float deltaTime);

    // 添加卡牌到卡牌库
    void addCardToCollection(Card* card);
};