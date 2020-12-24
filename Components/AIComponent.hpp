//
// Created by sascha on 12/21/20.
//
#pragma once

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "../Game.hpp"
#include "../Scenes/LevelBase.hpp"
#include <string>
#include <vector>
#include "../../Engine/Astar.hpp"
#include "EntityObject.hpp"

class TransformComponent;

class AIComponent : public Component {
private:
    std::vector<GridLocation> _path;
    int _currentPosition;
    GridLocation _target;
    bool _followTransform = false;
    EntityObject* _parent = nullptr;
    std::unique_ptr<EntityObject> _following;
    float _totalTime = 0;

    void updatePath();
    GridLocation positionToGrid(Vector2 position);
    void navigatePath(const float& deltaTime);
public:
    AIComponent(EntityId& entityId);
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void follow(EntityObject& entityObject);

    Vector2 gridToPosition(GridLocation location);
};


