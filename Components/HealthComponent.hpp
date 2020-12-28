#pragma once

#include "Component.hpp"

#include "../../API/Rendering/RenderingAPI.hpp"
#include "../Game.hpp"

class HealthComponent : public Component {
private:
    float _healthPoints = 100;
    bool _damageIsDone = false;
    RenderingAPI& _renderingApi;


public:
    explicit HealthComponent(EntityId id) : Component(id), _renderingApi(Game::getInstance()->getRenderingAPI()) {

    }

    [[nodiscard]] float getHealth() const;
    void setHealth(float newHealthPoints);
    void doDamage(float amountOfHealthPoints);
    void die();

private:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
};