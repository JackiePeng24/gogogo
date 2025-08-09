#include <iostream>
#include "Deck.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

void Deck::initRandom() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
}

Card* Deck::drawrandomCard() {
	initRandom();
	std::vector<Card*>availableCards;
	for (Card* card : Cards) {
		bool inHand = std::find(currentHand.begin(), currentHand.end(), card) != currentHand.end();
		bool inCooling = std::find(coolingCards.begin(), coolingCards.end(), card) != coolingCards.end();
		if (!inHand && !inCooling) {
			availableCards.push_back(card);
		}
	}
	if (availableCards.empty()) {
		return nullptr;
	}
	int randomIndex = rand() % availableCards.size();
	return availableCards[randomIndex];
}

bool Deck::initialize(std::vector<Card*>& selectedCards) {
	if (selectedCards.size() != GameConstants::Deck::MAX_DECK_SIZE) {
		return false;
	}
	Cards = selectedCards;
	return true;
}

void Deck::drawInitialHand() {
	currentHand.clear();
	for (int i = 0; i < GameConstants::Deck::HAND_SIZE; ++i) {
		if (Card* card = drawrandomCard()) {
			currentHand.push_back(card);
		}
	}
}

bool Deck::playCard(Card* card) {
	auto it = std::find(currentHand.begin(), currentHand.end(), card);
	if (it == currentHand.end()) {
		return false;
	}
	// ´ÓÊÖÅÆÒÆ³ý
	currentHand.erase(it);

	// ·ÅÈëÀäÈ´Çø£¨ÀäÈ´2»ØºÏ£©
	coolingCards.push_back(card);
	cooldownTimers[card] = GameConstants::Deck::COOLDOWN_TURNS;

	// ²¹³äÐÂ¿¨ÅÆ
	if (Card* newCard = drawrandomCard()) {
		currentHand.push_back(newCard);
	}
	return true;
}

void Deck::updateCooldowns() {
	for (auto it = coolingCards.begin(); it != coolingCards.end(); ) {
		Card* card = *it;
		if (--cooldownTimers[card] <= 0) {
			// ÀäÈ´½áÊø
			cooldownTimers.erase(card);
			it = coolingCards.erase(it);
		}
		else {
			++it;
		}
	}
}