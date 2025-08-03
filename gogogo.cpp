#include "Player.h"
#include "Board.h"
#include "GameRenderer.h"
#include "ConsoleInputHandler.h"
#include <thread>
#include <chrono>
#include <limits>

void initializePlayerCollection(Player& player) {
    player.addCardToCollection(new UnitCard("骑士", "坚固近战单位", 3, "普通", "knight", 100, 20));
    player.addCardToCollection(new UnitCard("弓箭手", "远程单位", 4, "普通", "archer", 60, 30));
    player.addCardToCollection(new SpellCard("火球术", "范围伤害", 4, "稀有", 2.0f, 50));
    player.addCardToCollection(new SpellCard("治疗术", "恢复生命", 3, "稀有", 2.0f, 40));
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
            std::cout << "按Y确认卡组，按N继续编辑: ";
            char confirm;
            std::cin >> confirm;
            if (tolower(confirm) == 'y') break;
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
    while (board.isGameActive()) {
        Player& current = (currentPlayerId == 1) ? player1 : player2;

        ConsoleRenderer::render(board, current);
        std::cout << "\n=== " << current.getName() << "的回合 ===\n";

        ConsoleInputHandler::handlePlayerTurn(current, board);

        board.update(1.0f);
        current.update(1.0f);
        current.getCurrentDeck().updateCooldowns();

        currentPlayerId = 3 - currentPlayerId; // 在1和2之间切换
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (auto& card : player1.getCollection()) { delete card; }
    for (auto& card : player2.getCollection()) { delete card; }
    // 直接利用Board的结束状态，不再冗余检查
    std::cout << "游戏结束！" << std::endl;
    return 0;
}