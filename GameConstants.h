#pragma once
#include <string>

namespace GameConstants {
	//������س���
	namespace Board {
		const int ROWS = 18;
		const int COLS = 10;
	}

	//�����س���
	namespace Player {
		const int INIT_MARKS = 10;
		const int MARKS_REGEN_RATE = 10;
		const int INIT_TROPHY = 0;
	}

	//��������س���
	namespace Deck {
		const int MAX_CARDS = 10;
		enum CardState {
			IN_DECK, // �ƿ�
			IN_HAND, // ����
			USED // ����������������
		}; 
	}


	//��Ϸ��λ����
	namespace Unit {
		const int MAX_HP = 100;
	}
}
