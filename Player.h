#pragma once
#include "Card.h"
#include "Deck.h"
#include"BoardPosition.h"
#include <vector>

class IPlayer {
public:
    virtual ~IPlayer() = default;

    // 玩家信息
    virtual std::string getName() const = 0;
    virtual int getLevel() const = 0;
    virtual int getTrophies() const = 0;       // 奖杯数

    // 资源管理
    virtual float getCurrentElixir() const = 0; // 当前圣水
    virtual float getElixirRegenRate() const = 0; // 圣水恢复速率

    // 卡组管理
    virtual const Deck& getCurrentDeck() const = 0;
    virtual bool setCurrentDeck(const Deck& deck) = 0;
    virtual const std::vector<Card*>& getCollection() const = 0; // 所有卡牌

    // 战斗状态
    virtual bool getKingTower() = 0;
    virtual bool getLeftPrincessTower() = 0;
    virtual bool getRightPrincessTower() = 0;

    // 游戏操作
    virtual bool playCard(int cardIndex, const BoardPosition& position) = 0;

    // 进度系统
    virtual void addExperience(int amount) = 0;
    virtual void addTrophies(int amount) = 0;

};

// Player.h
class Player : public IPlayer {
public:
    std::string name;
    int trophies;
    float currentElixir = 5.0f;  // 初始圣水值
    float elixirRegenRate = 0.8f; // 每秒恢复0.8点圣水
    std::unique_ptr<Deck> currentDeck;
    std::vector<Card*> collection;
    bool isPlayer1;  // 玩家标识

    // 圣水恢复计时器
    float elixirTimer = 0.0f;

    Player(std::string playerName, bool player1)
        : name(playerName), isPlayer1(player1) {
    }

    // 实现IPlayer接口
    std::string getName() const override { return name; }
    int getLevel() const override { return 1; } // 简化实现
    int getTrophies() const override { return trophies; }
    float getCurrentElixir() const override { return currentElixir; }
    float getElixirRegenRate() const override { return elixirRegenRate; }

    const Deck& getCurrentDeck() const override { return *currentDeck; }
    bool setCurrentDeck(const Deck& deck) override {
        currentDeck = std::make_unique<Deck>(deck);
        return true;
    }

    const std::vector<Card*>& getCollection() const override { return collection; }

    // 圣水扣除方法
    void deductElixir(int amount) {
        currentElixir = std::max(0.0f, currentElixir - amount);
    }

    // 更新圣水
    void update(float deltaTime) {
        elixirTimer += deltaTime;
        if (elixirTimer >= 1.0f) {
            currentElixir = std::min(currentElixir + elixirRegenRate, 10.0f);
            elixirTimer = 0.0f;
        }
    }

    // 添加卡牌到卡牌库
    void addCardToCollection(Card* card) {
        collection.push_back(card);
    }
};