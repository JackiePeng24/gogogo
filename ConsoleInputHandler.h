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
            system("cls"); // 每次循环清屏，确保显示最新状态

            // 获取当前手牌的快照（避免中间状态变化）
            const auto& hand = player.getCurrentDeck().getCurrentHand();

            // 显示当前圣水和可用卡牌
            std::cout << "当前圣水: " << player.getCurrentElixir() << "/10\n";
            std::cout << "可选卡牌:\n";
            for (int i = 0; i < hand.size(); ++i) {
                std::cout << i << ": " << hand[i]->getName()
                    << " (费用:" << hand[i]->getCost() << ") - "
                    << (player.getCurrentElixir() >= hand[i]->getCost() ? "可用" : "圣水不足")
                    << "\n";
            }

            // 获取玩家输入
            std::cout << "选择卡牌(0-" << hand.size() - 1 << ")，-1结束回合： ";
            int choice;
            if (!(std::cin >> choice)) { // 处理非法输入
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == -1) break;

            // 验证选择有效性
            if (choice < 0 || choice >= hand.size()) {
                std::cout << "无效选择！\n";
                continue;
            }

            // 获取实际卡牌对象
            Card* selectedCard = hand[choice];
            if (player.getCurrentElixir() < selectedCard->getCost()) {
                std::cout << "圣水不足！\n";
                continue;
            }

            // 处理卡牌放置
            handleCardPlacement(player, board, choice);

            // 显式打印实际使用的卡牌（避免混淆）
            std::cout << "成功使用卡牌: " << selectedCard->getName() << "\n";

            // 刷新手牌状态
            player.getCurrentDeck().updateCooldowns();
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
                    std::cout << "圣水不足！无法在此位置使用卡牌！\n";
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