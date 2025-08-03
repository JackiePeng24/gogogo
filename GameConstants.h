#pragma once
#include <string>
#include"BoardPosition.h"

namespace GameConstants {
	//������س���
	namespace Board {
		const int ROWS = 13 ;
		const int COLS = 15;
	}

	//�����س���
	namespace Player {
		const int INIT_MARKS = 10;
		const int MARKS_REGEN_RATE = 10;
		const int INIT_TROPHY = 0;
	}

	//��������س���

	namespace Deck {
		const int MAX_DECK_SIZE = 10;   // �����������
		const int HAND_SIZE = 4;        // ��������
		const int COOLDOWN_TURNS = 2;   // ʹ�ú����ȴ�غ���

		enum CardState {
			IN_DECK,    // �ڿ����п���
			IN_HAND,    // ��ǰ��������
			IN_COOLDOWN // ��ʹ�ã�������ȴ
		};
	}


	//��Ϸ��λ����
	namespace Unit {
		const int MAX_HP = 100;
	}

	namespace Tower {
		const BoardPosition KING_POS_1 = BoardPosition(0,7);
		const BoardPosition LEFT_PRINCESS_POS_1 = BoardPosition(2,3);
		const BoardPosition RIGHT_PRINCESS_POS_1 = BoardPosition(2, 11);

		const BoardPosition KING_POS_2 = BoardPosition(12, 7);
		const BoardPosition LEFT_PRINCESS_POS_2 = BoardPosition(10, 3);
		const BoardPosition RIGHT_PRINCESS_POS_2 = BoardPosition(10, 11);

		const int KING_HP = 1000;
		const int PRINCESS_HP = 500;
		
		const int KING_ATTACK_RANGE = 4;
		const int PRINCESS_ATTACK_RANGE = 2;

		const int KING_DAMAGE = 100;
		const int PRINCESS_DAMAGE = 50;
	}
}
