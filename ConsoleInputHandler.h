#pragma once
#include <iostream>
#include "Player.h"
#include "GameConstants.h"
#include "Deck.h"
#include "Board.h"
#include"Card.h"
#include <limits>
#include <algorithm>

class ConsoleInputHandler {
public:
    static void handlePlayerTurn(Player& player, Board& board) {
        while (true) {
            system("cls"); // ÿ��ѭ��������ȷ����ʾ����״̬

            // ��ȡ��ǰ���ƵĿ��գ������м�״̬�仯��
            const auto& hand = player.getCurrentDeck().getCurrentHand();

            // ��ʾ��ǰʥˮ�Ϳ��ÿ���
            std::cout << "��ǰʥˮ: " << player.getCurrentElixir() << "/10\n";
            std::cout << "��ѡ����:\n";
            for (int i = 0; i < hand.size(); ++i) {
                std::cout << i << ": " << hand[i]->getName()
                    << " (����:" << hand[i]->getCost() << ") - "
                    << (player.getCurrentElixir() >= hand[i]->getCost() ? "����" : "ʥˮ����")
                    << "\n";
            }

            // ��ȡ�������
            std::cout << "ѡ����(0-" << hand.size() - 1 << ")��-1�����غϣ� ";
            int choice;
            if (!(std::cin >> choice)) { // ����Ƿ�����
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == -1) break;

            // ��֤ѡ����Ч��
            if (choice < 0 || choice >= hand.size()) {
                std::cout << "��Чѡ��\n";
                continue;
            }

            // ��ȡʵ�ʿ��ƶ���
            Card* selectedCard = hand[choice];
            if (player.getCurrentElixir() < selectedCard->getCost()) {
                std::cout << "ʥˮ���㣡\n";
                continue;
            }

            // �����Ʒ���
            handleCardPlacement(player, board, choice);

            // ��ʽ��ӡʵ��ʹ�õĿ��ƣ����������
            std::cout << "�ɹ�ʹ�ÿ���: " << selectedCard->getName() << "\n";

            // ˢ������״̬
            player.getCurrentDeck().updateCooldowns();
        }
    }

private:
    static void handleCardPlacement(Player& player, Board& board, int cardIndex) {
        while (true) {
            std::cout << "ѡ�����λ��(�� ��)����-1ȡ��: ";
            int row, col;
            std::cin >> row;

            if (row == -1) break;

            std::cin >> col;

            BoardPosition pos(row, col);
            if (pos.isValid()) {
                if (player.playCard(cardIndex, pos, board)) {
                    std::cout << "�ɹ�ʹ�� " << player.getCurrentDeck().getCurrentHand()[cardIndex]->getName() << "\n";
                    break;
                }
                else {
                    std::cout << "ʥˮ���㣡�޷��ڴ�λ��ʹ�ÿ��ƣ�\n";
                }
            }
            else {
                std::cout << "��Чλ�ã���Ч��Χ: ��(0-"
                    << GameConstants::Board::ROWS - 1 << "), ��(0-"
                    << GameConstants::Board::COLS - 1 << ")\n";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};