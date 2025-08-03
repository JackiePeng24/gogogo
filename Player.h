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
    float currentElixir = 5.0f;  // ��ʼʥˮֵ
    float elixirRegenRate = 0.8f; // ÿ��ָ�0.8��ʥˮ
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    int playerId = -1;

    // ʥˮ�ָ���ʱ��
    float elixirTimer = 0.0f;

    Player(std::string playerName): name(playerName){}

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

    bool setbattleDeck(const std::vector<std::string>& cardNames) {
        if (cardNames.size() != GameConstants::Deck::MAX_DECK_SIZE) {
            return false;
        }

        // ���ö�ս���飨��collection��ѡ��10�ţ�
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

    // ʹ�ÿ���
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