#pragma once
#include "Card.h"
#include "Deck.h"
#include"BoardPosition.h"
#include <vector>

// Player.h
class Player {
public:
    std::string name;
    int trophies;
    float currentElixir = 5.0f;  // 初始圣水值
    float elixirRegenRate = 0.8f; // 每秒恢复0.8点圣水
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    int playerId = -1;

    // 圣水恢复计时器
    float elixirTimer = 0.0f;

    Player(std::string playerName): name(playerName){}

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

    bool setbattleDeck(const std::vector<std::string>& cardNames) {
        if (cardNames.size() != GameConstants::Deck::MAX_DECK_SIZE) {
            return false;
        }

        // 设置对战卡组（从collection中选择10张）
        std::vector<Card*> selectedCards;
        for (const auto& name : cardNames) {
            for (Card* card : collection) {
                if (card->getName() == name) {
                    selectedCards.push_back(card);
                    break;
                }
            }
        }

        if (selectedCards.size() != GameConstants::Deck::MAX_DECK_SIZE) {
            return false;
        }

        currentDeck = std::make_unique<Deck>();
        return currentDeck->initialize(selectedCards);
    }

    // 使用卡牌
    bool playCard(int handIndex, BoardPosition position, Board& board) {
        if (!currentDeck || handIndex < 0 || handIndex >= currentDeck->getCurrentHand().size()) {
            return false;
        }

        Card* card = currentDeck->getCurrentHand()[handIndex];
        if (currentElixir < card->getCost()) {
            return false;
        }

        deductElixir(card->getCost());
        card->play(*this, board, position);
        return currentDeck->playCard(card);
    }


    // 圣水扣除方法
    void deductElixir(int amount) {
        currentElixir = std::max(0.0f, currentElixir - amount);
    }

    // 更新圣水
    void update(float deltaTime) {
        elixirTimer += deltaTime;
        if (elixirTimer >= 1.0f) {
            currentElixir = std::min(currentElixir + elixirRegenRate, 10.0f);
            elixirTimer = 0.0f;
        }
    }

    // 添加卡牌到卡牌库
    void addCardToCollection(Card* card) {
        collection.push_back(card);
    }
};