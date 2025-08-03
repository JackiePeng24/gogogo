#pragma once
#include "Board.h"
#include "Player.h"
#include "GameConstants.h"
#include "Unit.h"
#include "Tower.h"
#include <iostream>
#include <iomanip>
#include <map>

class ConsoleRenderer {
public:
    static void render(const Board& board, const Player& currentPlayer) {
        system("cls"); // Windows清屏

        // 渲染玩家信息
        renderPlayerInfo(currentPlayer);

        // 渲染棋盘
        renderBoard(board);

        // 渲染手牌
        renderHand(currentPlayer);
    }

private:
    static void renderPlayerInfo(const Player& player) {
        std::cout << "玩家: " << player.getName()
            << " | 圣水: " << std::fixed << std::setprecision(1)
            << player.getCurrentElixir()
            << "\n----------------------------------------\n";
    }

    static void renderBoard(const Board& board) {
        // 创建棋盘网格
        char grid[GameConstants::Board::ROWS][GameConstants::Board::COLS];

        // 初始化空白棋盘
        for (int r = 0; r < GameConstants::Board::ROWS; ++r) {
            for (int c = 0; c < GameConstants::Board::COLS; ++c) {
                grid[r][c] = '.';
            }
        }

        // 渲染单位
        const auto& units = board.getUnits();
        for (const auto& unit : units) {
            if (unit->isAlive()) {
                char symbol = '?';
                if (unit->getName() == "Knight") symbol = 'K';
                else if (unit->getName() == "Archer") symbol = 'A';

                // 区分玩家1(大写)和玩家2(小写)
                symbol = unit->getOwner() == 1 ? symbol : tolower(symbol);

                BoardPosition pos = unit->getPosition();
                if (pos.isValid()) {
                    grid[pos.row][pos.col] = symbol;
                }
            }
        }

        // 渲染塔
        const auto& towers = board.getTowers();
        for (const auto& tower : towers) {
            if (tower->isAlive()) {
                char symbol = tower->isKingTower() ? '♔' : '♖';
                BoardPosition pos = tower->getPosition();
                if (pos.isValid()) {
                    grid[pos.row][pos.col] = symbol;
                }
            }
        }

        // 打印棋盘
        std::cout << "  ";
        for (int c = 0; c < GameConstants::Board::COLS; ++c) {
            std::cout << std::setw(2) << c;
        }
        std::cout << "\n";

        for (int r = 0; r < GameConstants::Board::ROWS; ++r) {
            std::cout << std::setw(2) << r;
            for (int c = 0; c < GameConstants::Board::COLS; ++c) {
                std::cout << std::setw(2) << grid[r][c];
            }
            std::cout << "\n";
        }
    }

    static void renderHand(const Player& player) {
        std::cout << "\n手牌:\n";
        const auto& hand = player.getCurrentDeck().getCurrentHand();
        for (int i = 0; i < hand.size(); ++i) {
            std::cout << i << ": " << hand[i]->getName()
                << " (费用:" << hand[i]->getCost()
                << ", 类型:" << hand[i]->getType() << ")\n";
        }
    }
};