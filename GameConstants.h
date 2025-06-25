#pragma once
#include <string>

namespace GameConstants {
	//棋盘相关常量
	namespace Board {
		const int ROWS = 18;
		const int COLS = 10;
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
}
