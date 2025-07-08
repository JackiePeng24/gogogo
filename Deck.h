#pragma once
#include"Card.h"
#include"GameConstants.h"
#include<iostream>
#include<vector>

class IDeck {
public:
	virtual ~IDeck() {};
	
	//�����������(��Ϸ��ʼǰ����)
	virtual bool addCard(std::string cardName) const = 0;
	virtual bool removeCard(std::string cardName) const = 0;

	//����״̬����
	virtual GameConstants::Deck::CardState getCardState(std::string cardName) const = 0;
	virtual void setCardState(std::string cardName, GameConstants::Deck::CardState state) = 0;
};
