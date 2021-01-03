#pragma once

#include "Component.hpp"

#include <string>

class TransformComponent;

class PlayerSpawnerComponent : public Component {
private:
    std::string _pointName{};

    TransformComponent *_transformComponent = nullptr;

public:
    inline const TransformComponent *getTransformComponent() { return _transformComponent; }

public:
    inline std::string getPointName() { return _pointName; }

    explicit PlayerSpawnerComponent(EntityId i);

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;
};