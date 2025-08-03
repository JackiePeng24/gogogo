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

            // 显示可用的卡牌
            std::cout << "可选卡牌:\n";
            for (int i = 0; i < hand.size(); ++i) {
                std::cout << i << ": " << hand[i]->getName()
                    << " (费用:" << hand[i]->getCost()
                    << ") - " << (player.getCurrentElixir() >= hand[i]->getCost() ? "可用" : "圣水不足")
                    << "\n";
            }

            // 获取玩家选择
            std::cout << "选择卡牌(0-" << hand.size() - 1 << ")，-1结束回合: ";
            int choice;
            std::cin >> choice;

            if (choice == -1) break;

            if (choice >= 0 && choice < hand.size()) {
                if (player.getCurrentElixir() >= hand[choice]->getCost()) {
                    handleCardPlacement(player, board, choice);
                }
                else {
                    std::cout << "圣水不足！当前圣水: " << player.getCurrentElixir()
                        << "，需要: " << hand[choice]->getCost() << "\n";
                }
            }
            else {
                std::cout << "无效选择！\n";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

private:
    static void handleCardPlacement(Player& player, Board& board, int cardIndex) {
        while (true) {
            std::cout << "选择放置位置(行 列)，或-1取消: ";
            int row, col;
            std::cin >> row;

            if (row == -1) break;

            std::cin >> col;

            BoardPosition pos(row, col);
            if (pos.isValid()) {
                if (player.playCard(cardIndex, pos, board)) {
                    std::cout << "成功使用 " << player.getCurrentDeck().getCurrentHand()[cardIndex]->getName() << "\n";
                    break;
                }
                else {
                    std::cout << "无法在此位置使用卡牌！\n";
                }
            }
            else {
                std::cout << "无效位置！有效范围: 行(0-"
                    << GameConstants::Board::ROWS - 1 << "), 列(0-"
                    << GameConstants::Board::COLS - 1 << ")\n";
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};