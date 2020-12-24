#pragma once
#include "../Component.hpp"
#include "TransactionData.hpp"
#include <string>

class WalletComponent : public Component {

private:
    int _zombytes = 0;
    int _experience = 0;
    int _score = 0;

public:
    explicit WalletComponent(EntityId id);

    void makeTransaction(TransactionData &data);

    void addExperience(int experience);

    void addScore(int score);

    void addZombytes(int zombytes);

    [[nodiscard]] int getZombytes() const;

    [[nodiscard]] int getExperience() const;

    [[nodiscard]] int getScore() const;

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
};


