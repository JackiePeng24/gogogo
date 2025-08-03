#pragma once
#include"Card.h"
#include"GameConstants.h"
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<ctime>

class Deck {
private:
	std::vector<Card*>Cards;
	std::vector<Card*>currentHand;
	std::vector<Card*>coolingCards;

	std::unordered_map<Card*, int>cooldownTimers;

	void initRandom() {
		bool initialized = false;
		if (!initialized) {
			srand(static_cast<unsigned int>(time(nullptr)));
			initialized = true;
		}
	}

	// ��Cards�������ȡһ����
	Card* drawrandomCard() {
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

public:
	// ��ʼ����ս���飨��Player��collection��ѡ��10�ţ�
	bool initialize(std::vector<Card*>& selectedCards) {
		if (selectedCards.size() != GameConstants::Deck::MAX_DECK_SIZE) {
			return false;
		}
		Cards = selectedCards;
		return true;
	}

	//��ʼ���ƣ�4�ţ�
	void drawInitialHand() {
		currentHand.clear();
		for (int i = 0; i < GameConstants::Deck::HAND_SIZE; ++i) {
			if (Card* card = drawrandomCard()) {
				currentHand.push_back(card);
			}
		}
	}

	bool playCard(Card* card) {
		auto it = std::find(currentHand.begin(), currentHand.end(), card);
		if (it == currentHand.end()) {
			return false;
		}
		// �������Ƴ�
		currentHand.erase(it);

		// ������ȴ������ȴ2�غϣ�
		coolingCards.push_back(card);
		cooldownTimers[card] = GameConstants::Deck::COOLDOWN_TURNS;

		// �����¿���
		if (Card* newCard = drawrandomCard()) {
			currentHand.push_back(newCard);
		}
		return true;
	}

	// ÿ�غϸ�����ȴ״̬
	void updateCooldowns() {
		for (auto it = coolingCards.begin(); it != coolingCards.end(); ) {
			Card* card = *it;
			if (--cooldownTimers[card] <= 0) {
				// ��ȴ����
				cooldownTimers.erase(card);
				it = coolingCards.erase(it);
			}
			else {
				++it;
			}
		}
	}

	// ��ȡ��ǰ����
	const std::vector<Card*>& getCurrentHand() const {
		return currentHand;
	}

	// ��ȡ��ȴ�еĿ���
	const std::vector<Card*>& getCoolingCards() const {
		return coolingCards;
	}
};