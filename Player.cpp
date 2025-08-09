#include<iostream>
#include "Player.h"
#include "Deck.h"
#include "Card.h"

bool Player::setbattleDeck(const std::vector<std::string>& cardNames) {
    if (cardNames.size() != GameConstants::Deck::MAX_DECK_SIZE) {
        return false;
    }

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

bool Player::playCard(int handIndex, BoardPosition pos, Board& board) {
    std::cout << "��������: " << handIndex << " | ʥˮ: " << currentElixir << std::endl;

    if (!currentDeck || handIndex < 0 || handIndex >= currentDeck->getCurrentHand().size()) {
        std::cout << "������Ч����������" << std::endl;
        return false;
    }

    Card* card = currentDeck->getCurrentHand()[handIndex];
    if (currentElixir < card->getCost()) {
        std::cout << "����ʥˮ���㣨��Ҫ " << card->getCost() << "��" << std::endl;
        return false;
    }

    deductElixir(card->getCost());
    card->play(*this, board, pos);  
    return true;
}


void Player::update(float deltaTime) {
    elixirTimer += deltaTime;
    if (elixirTimer >= 1.0f) { // ÿ��ظ�һ��
        currentElixir = std::min(currentElixir + elixirRegenRate, 10.0f);
        elixirTimer -= 1.0f; // ��ȥ������һ�룬��������
    }
}

void Player::addCardToCollection(Card* card) {
    collection.push_back(card);
}