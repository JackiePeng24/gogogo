#pragma once
#include <string>
#include"BoardPosition.h"

namespace GameConstants {
	//棋盘相关常量
	namespace Board {
		const int ROWS = 13 ;
		const int COLS = 15;
	}

	//玩家相关常量
	namespace Player {
		const int INIT_MARKS = 10;
		const int MARKS_REGEN_RATE = 10;
		const int INIT_TROPHY = 0;
	}

	//手牌区相关常量
	namespace Deck {
		const int MAX_CARDS = 10;
		enum CardState {
			IN_DECK, // 牌库
			IN_HAND, // 手牌
			USED // 打出（进入抽牌区）
		}; 
	}


	//游戏单位常量
	namespace Unit {
		const int MAX_HP = 100;
	}

	namespace Tower {
		const BoardPosition KING_POS_1 = BoardPosition(0,7);
		const BoardPosition LEFT_PRINCESS_POS_1 = BoardPosition(2,3);
		const BoardPosition RIGHT_PRINCESS_POS_1 = BoardPosition(2, 11);

		const BoardPosition KING_POS_2 = BoardPosition(15, 7);
		const BoardPosition LEFT_PRINCESS_POS_2 = BoardPosition(13, 3);
		const BoardPosition RIGHT_PRINCESS_POS_2 = BoardPosition(13, 11);

		const int KING_HP = 1000;
		const int PRINCESS_HP = 500;
		
		const int KING_ATTACK_RANGE = 4;
		const int PRINCESS_ATTACK_RANGE = 2;

		const int KING_DAMAGE = 100;
		const int PRINCESS_DAMAGE = 50;
	}
}
