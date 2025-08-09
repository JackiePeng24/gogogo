#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "GameConstants.h"

class Card;


class Deck {
private:
	std::vector<Card*>Cards;
	std::vector<Card*>currentHand;
	std::vector<Card*>coolingCards;

	std::unordered_map<Card*, int>cooldownTimers;

	void initRandom();

public:
	// 从Cards中随机抽取一张牌
	Card* drawrandomCard();

	// 初始化对战卡组（从Player的collection中选择10张）
	bool initialize(std::vector<Card*>& selectedCards);

	//初始发牌（4张）
	void drawInitialHand();

	bool playCard(Card* card);

	// 每回合更新冷却状态
	void updateCooldowns();

	// 获取当前手牌
	std::vector<Card*>& getCurrentHand(){
		return currentHand;
	}

	// 获取冷却中的卡牌
	std::vector<Card*>& getCoolingCards(){
		return coolingCards;
	}
};