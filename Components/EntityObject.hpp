#pragma once

#include "Component.hpp"

#include <memory>
#include <vector>
#include <string>

class EntityObject : public Component {
private:
    std::vector<std::unique_ptr<Component>> components{};

public:
    explicit EntityObject(EntityId id) : Component(id)
    {

    }

    void update() override;

    [[nodiscard]] std::string name() const override;

    [[nodiscard]] Component *Clone(EntityId entityId) const override;
};
