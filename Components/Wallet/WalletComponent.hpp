#pragma once
#include "../Component.hpp"
#include "TransactionData.hpp"
#include "../../../Engine/Rendering/TextWrapper.hpp"
#include <string>

class WalletComponent : public Component {
private:
    int _experience = 0;
    int _score = 0;
    int _zombytes = 0;

    RenderingAPI *_renderAPI = nullptr;
    std::map<std::string, TextWrapper*> _walletText {};


public:
    explicit WalletComponent(EntityId id);

    void addItemsFromTransaction(TransactionData &data);

    void addExperience(int experience);

    void addScore(int score);

    void addZombytes(int zombytes);

    [[nodiscard]] int getZombytes() const;

    [[nodiscard]] int getExperience() const;

    [[nodiscard]] int getScore() const;

    int setZombytes(int zombytes);

    int setExperience(int experience);

    int setScore(int score) ;
    
public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;


    void reset();
};


