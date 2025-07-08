#pragma once
#include "Card.h"
#include <unordered_map>

class CardFactory {
    static std::unordered_map<std::string, ICard*> cardPrototypes;

public:
    static void initialize() {
        // ��ʼ����λ��
        // ʾ����cardPrototypes["Knight"] = new UnitCard("Knight", "Strong melee unit", 3, "Common", "Knight");


        // ��ʼ��������,ʾ����
        // cardPrototypes["Fireball"] = new SpellCard("Fireball", "Area damage spell", 4, "Rare", "Fireball", 2.5f);

    }

    static ICard* createCard(const std::string& name, int level = 1) {
        auto it = cardPrototypes.find(name);
        if (it != cardPrototypes.end()) {
            // ����ԭ�ʹ����¿���ʵ��
            ICard* prototype = it->second;

            if (prototype->getType() == "unit") {
                UnitCard* unitCard = static_cast<UnitCard*>(prototype);
                return new UnitCard(*unitCard);
            }
            else if (prototype->getType() == "spell") {
                SpellCard* spellCard = static_cast<SpellCard*>(prototype);
                return new SpellCard(*spellCard);
            }
        }
        return nullptr;
    }

    static void cleanup() {
        for (auto& pair : cardPrototypes) {
            delete pair.second;
        }
        cardPrototypes.clear();
    }
};