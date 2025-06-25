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
    virtual const std::vector<ICard*>& getCollection() const = 0; // 所有卡牌

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