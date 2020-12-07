#pragma once

#include "Component.hpp"

#include <memory>
#include <utility>
#include <vector>
#include <string>

class EntityObject : public Component {
private:
    std::vector<std::unique_ptr<Component>> components{};

public:
    std::string entityName;
    [[nodiscard]] const std::vector<std::unique_ptr<Component>>& getComponents() const {
        return components;
    }

public:
    explicit EntityObject(EntityId id, std::string name = "") : Component(id),
                                                                entityName(std::move(name)) {

    }

    ~EntityObject() {

    }

    void update() override;

    void fixedUpdate(const float &deltaTime) override;

    void AddComponent(Component *component);

    [[nodiscard]] std::string name() const override;

    Component *Clone(EntityId entityId, const LevelResources::component *component) override;
};
