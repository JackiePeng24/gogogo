#include<iostream>
#include "Player.h"
#include "Board.h"
#include "GameRenderer.h"
#include "ConsoleInputHandler.h"
#include<sstream>
#include <thread>
#include <chrono>
#include <limits>

void initializePlayerCollection(Player& player) {
    player.addCardToCollection(Card::createUnitCard("Knight", "坚固近战单位", 3, "普通", 100, 20, 1));
    player.addCardToCollection(Card::createUnitCard("Archer", "远程单位", 4, "普通", 60, 30, 1));
    player.addCardToCollection(Card::createSpellCard("Fireball", "范围伤害", 4, "稀有", 2.0f, 50, 1));
    player.addCardToCollection(Card::createSpellCard("Healing", "恢复生命", 3, "稀有", 2.0f, 40, 1));
}

void selectDeckInteractively(Player& player) {
    const auto& collection = player.getCollection();
    std::vector<std::string> selectedCards;

    while (true) {
        system("cls");
        std::cout << player.getName() << "选择卡组 (需要选择"
            << GameConstants::Deck::MAX_DECK_SIZE << "张卡牌)\n";
        std::cout << "当前已选: " << selectedCards.size()
            << "/" << GameConstants::Deck::MAX_DECK_SIZE << "\n\n";

        for (int i = 0; i < collection.size(); ++i) {
            auto card = collection[i];
            bool selected = std::find(selectedCards.begin(), selectedCards.end(), card->getName()) != selectedCards.end();

            std::cout << i << ": " << card->getName()
                << (selected ? " (已选择)" : "")
                << "\n   费用:" << card->getCost()
                << " 类型:" << card->getType()
                << "\n   描述:" << card->getDescription() << "\n\n";
        }

        if (selectedCards.size() == GameConstants::Deck::MAX_DECK_SIZE) {
            std::cout << "按y确认卡组，按n继续编辑: ";
            char confirm;
            std::cin >> confirm;
            if (confirm == 'y') break;
            continue;
        }

        std::cout << "输入卡牌编号(0-" << collection.size() - 1 << ")添加，-1移除卡牌: ";
        int choice;
        std::cin >> choice;

        //移除卡牌
        if (choice == -1 && !selectedCards.empty()) {
            std::cout << "输入要移除的卡牌名称: ";
            std::string name;
            std::cin >> name;

            auto it = std::find(selectedCards.begin(), selectedCards.end(), name);
            if (it != selectedCards.end()) {
                selectedCards.erase(it);
                std::cout << "已移除卡牌: " << name << "\n";
            }
            else {
                std::cout << "错误：未找到卡牌 '" << name << "'！\n";
            }
        }

        //添加卡牌
        if (choice >= 0 && choice < collection.size()) {
            std::string name = collection[choice]->getName();
            if (selectedCards.size() < GameConstants::Deck::MAX_DECK_SIZE &&
                std::find(selectedCards.begin(), selectedCards.end(), name) == selectedCards.end()) {
                selectedCards.push_back(name);
            }
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    player.setbattleDeck(selectedCards);
}

void handleCardPlacement(Player& player, Board& board, int cardIndex) {
    while (true) {
        std::cout << "输入放置位置(行 列)，或按q取消: ";

        std::string input;
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        std::istringstream iss(input);
        int row, col;
        if (iss >> row >> col) {
            BoardPosition pos(row, col);
            if (pos.isValid()) {
                if (player.playCard(cardIndex, pos, board)) {
                    std::cout << "成功放置卡牌: "
                        << player.getCurrentDeck().getCurrentHand()[cardIndex]->getName()
                        << "\n";
                    break;
                }
                else {
                    std::cout << "无法在此位置放置卡牌！\n";
                }
            }
            else {
                std::cout << "无效位置！有效范围: 行(0-"
                    << GameConstants::Board::ROWS - 1 << "), 列(0-"
                    << GameConstants::Board::COLS - 1 << ")\n";
            }
        }
        else {
            std::cout << "无效输入！请输入两个数字(行 列)或q取消\n";
        }
    }
}

float renderAccumulator = 0.0f;
const float renderInterval = 0.3f;

//main函数
int main() {
    Board board;
    board.startNewGame();

    Player player1("玩家1");
    Player player2("玩家2");
    player1.setPlayerId(1);
    player2.setPlayerId(2);

    initializePlayerCollection(player1);
    initializePlayerCollection(player2);

    selectDeckInteractively(player1);
    selectDeckInteractively(player2);

    player1.getCurrentDeck().drawInitialHand();
    player2.getCurrentDeck().drawInitialHand();

    int currentPlayerId = 1;
    bool placementPhase = true;
    float autoPhaseDuration = 5.0f;
    float autoPhaseTimer = 0.0f;

    while (board.isGameActive()) {
        Player& current = (currentPlayerId == 1) ? player1 : player2;

        if (placementPhase) {
            system("cls");
            ConsoleRenderer::render(board, current);
            std::cout << "\n=== " << current.getName() << "的放置阶段 ===\n";
            std::cout << "放置你的单位 (剩余自动阶段时间: "
                << autoPhaseDuration - autoPhaseTimer << "秒)\n";

            bool processingInput = true;
            while (processingInput) {
                system("cls");
                ConsoleRenderer::render(board, current);
                std::cout << "\n=== " << current.getName() << "的放置阶段 ===\n";
                std::cout << "放置你的单位 (剩余自动阶段时间: "
                    << autoPhaseDuration - autoPhaseTimer << "秒)\n";

                // 显示手牌
                const auto& hand = current.getCurrentDeck().getCurrentHand();
                for (int i = 0; i < hand.size(); ++i) {
                    std::cout << i << ": " << hand[i]->getName()
                        << " (费用:" << hand[i]->getCost() << ")\n";
                }

                // 读取输入
                std::cout << "选择卡牌(0-" << hand.size() - 1 << ")或按q结束放置: ";
                std::string inputStr;
                std::getline(std::cin, inputStr);  // 读取整行

                if (inputStr == "q") {
                    processingInput = false;
                    placementPhase = false;
                    autoPhaseTimer = 0.0f;
                }
                else if (!inputStr.empty() && isdigit(inputStr[0])) {
                    int choice = inputStr[0] - '0';
                    if (choice >= 0 && choice < hand.size()) {
                        handleCardPlacement(current, board, choice);
                    }
                    else {
                        std::cout << "无效选择！请输入 0-" << hand.size() - 1 << " 或 q\n";
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                }

                // 更新时间
                autoPhaseTimer += 0.1f;
                if (autoPhaseTimer >= autoPhaseDuration) {
                    processingInput = false;
                    placementPhase = false;
                    autoPhaseTimer = 0.0f;
                }
            }
        }
        else {
            // 自动战斗阶段
            renderAccumulator += 0.1f;
            autoPhaseTimer += 0.1f;

            // 更新游戏逻辑
            board.update(0.1f);
            current.update(0.1f);
            current.getCurrentDeck().updateCooldowns();

            // 按固定间隔渲染
            if (renderAccumulator >= renderInterval) {
                system("cls");
                ConsoleRenderer::render(board, current);
                std::cout << "\n=== 自动战斗阶段 ===\n";
                std::cout << "战斗进行中... (" << autoPhaseDuration - autoPhaseTimer << "秒后返回放置阶段)\n";
                renderAccumulator = 0.0f;
            }

            if (autoPhaseTimer >= autoPhaseDuration) {
                placementPhase = true;
                autoPhaseTimer = 0.0f;
                currentPlayerId = 3 - currentPlayerId;
                renderAccumulator = 0.0f; // 重置渲染计时器

                if (Card* newCard = current.getCurrentDeck().drawrandomCard()) {
                    current.getCurrentDeck().getCurrentHand().push_back(newCard);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 清理资源
    for (auto& card : player1.getCollection()) { delete card; }
    for (auto& card : player2.getCollection()) { delete card; }

    std::cout << "游戏结束！" << std::endl;
    return 0;
}