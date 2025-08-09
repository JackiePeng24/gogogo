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
	// ��Cards�������ȡһ����
	Card* drawrandomCard();

	// ��ʼ����ս���飨��Player��collection��ѡ��10�ţ�
	bool initialize(std::vector<Card*>& selectedCards);

	//��ʼ���ƣ�4�ţ�
	void drawInitialHand();

	bool playCard(Card* card);

	// ÿ�غϸ�����ȴ״̬
	void updateCooldowns();

	// ��ȡ��ǰ����
	std::vector<Card*>& getCurrentHand(){
		return currentHand;
	}

	// ��ȡ��ȴ�еĿ���
	std::vector<Card*>& getCoolingCards(){
		return coolingCards;
	}
};