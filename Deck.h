#pragma once
#include"Card.h"
#include"GameConstants.h"
#include<iostream>
#include<vector>

class Deck {
public:
	virtual ~Deck() {};
	
	//卡组基本操作(游戏开始前调用)
	virtual bool addCard(std::string cardName) const = 0;
	virtual bool removeCard(std::string cardName) const = 0;

	//卡牌状态管理
	virtual GameConstants::Deck::CardState getCardState(std::string cardName) const = 0;
	virtual void setCardState(std::string cardName, GameConstants::Deck::CardState state) = 0;
};