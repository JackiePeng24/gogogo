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

	// 从Cards中随机抽取一张牌
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
	// 初始化对战卡组（从Player的collection中选择10张）
	bool initialize(std::vector<Card*>& selectedCards) {
		if (selectedCards.size() != GameConstants::Deck::MAX_DECK_SIZE) {
			return false;
		}
		Cards = selectedCards;
		return true;
	}

	//初始发牌（4张）
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
		// 从手牌移除
		currentHand.erase(it);

		// 放入冷却区（冷却2回合）
		coolingCards.push_back(card);
		cooldownTimers[card] = GameConstants::Deck::COOLDOWN_TURNS;

		// 补充新卡牌
		if (Card* newCard = drawrandomCard()) {
			currentHand.push_back(newCard);
		}
		return true;
	}

	// 每回合更新冷却状态
	void updateCooldowns() {
		for (auto it = coolingCards.begin(); it != coolingCards.end(); ) {
			Card* card = *it;
			if (--cooldownTimers[card] <= 0) {
				// 冷却结束
				cooldownTimers.erase(card);
				it = coolingCards.erase(it);
			}
			else {
				++it;
			}
		}
	}

	// 获取当前手牌
	const std::vector<Card*>& getCurrentHand() const {
		return currentHand;
	}

	// 获取冷却中的卡牌
	const std::vector<Card*>& getCoolingCards() const {
		return coolingCards;
	}
};