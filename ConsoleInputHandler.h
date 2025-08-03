#pragma once
#include "Player.h"
#include "GameConstants.h"
#include "Board.h"
#include <iostream>
#include <limits>
#include <algorithm>

class ConsoleInputHandler {
public:
    static void handlePlayerTurn(Player& player, Board& board) {
        while (true) {
            const auto& hand = player.getCurrentDeck().getCurrentHand();

            // ��ʾ���õĿ���
            std::cout << "��ѡ����:\n";
            for (int i = 0; i < hand.size(); ++i) {
                std::cout << i << ": " << hand[i]->getName()
                    << " (����:" << hand[i]->getCost()
                    << ") - " << (player.getCurrentElixir() >= hand[i]->getCost() ? "����" : "ʥˮ����")
                    << "\n";
            }

            // ��ȡ���ѡ��
            std::cout << "ѡ����(0-" << hand.size() - 1 << ")��-1�����غ�: ";
            int choice;
            std::cin >> choice;

            if (choice == -1) break;

            if (choice >= 0 && choice < hand.size()) {
                if (player.getCurrentElixir() >= hand[choice]->getCost()) {
                    handleCardPlacement(player, board, choice);
                }
                else {
                    std::cout << "ʥˮ���㣡��ǰʥˮ: " << player.getCurrentElixir()
                        << "����Ҫ: " << hand[choice]->getCost() << "\n";
                }
            }
            else {
                std::cout << "��Чѡ��\n";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                    std::cout << "�޷��ڴ�λ��ʹ�ÿ��ƣ�\n";
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