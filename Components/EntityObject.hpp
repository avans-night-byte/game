#pragma once

#include "Component.hpp"

#include <memory>
#include <utility>
#include <vector>
#include <string>

class EntityObject : public Component {
public:
    std::vector<std::unique_ptr<Component>> components{};

public:
    std::string entityName;


public:
    explicit EntityObject(EntityId id, std::string name = "") : Component(id),
                                                                entityName(std::move(name)) {

    }

    ~EntityObject() override = default;

    void update() override;

    void fixedUpdate(const float &deltaTime) override;

    void addComponent(Component *component);

    [[nodiscard]]std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;
};
