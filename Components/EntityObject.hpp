#pragma once

#include "Component.hpp"
#include "PhysicsComponent.hpp"
#include "../Object/CollisionHandler.hpp"

#include <memory>
#include <utility>
#include <vector>
#include <string>

class TransformComponent;

class EntityObject : public Component {
protected:
    std::vector<std::unique_ptr<Component>> _components;
    TransformComponent* _transformComponent = nullptr;
    PhysicsComponent* _physicsComponent = nullptr;

public:
    std::string entityName;


public:
    explicit EntityObject(EntityId id, std::string name = "") : Component(id),
                                                                entityName(std::move(name)) {

    }

    TransformComponent* getTransform();
    PhysicsComponent *getPhysicsComponent();

    const std::vector<std::unique_ptr<Component>> &getComponents() {
        return _components;
    }

    template<class T>
    T *getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T should inherit from class Component");

        for (auto &comp: _components) {
            if (T *c = dynamic_cast<T *>(comp.get()))
                return c;
        }

        return nullptr;
    }

    Component* getComponent(std::string componentName);

    ~EntityObject() override = default;

    void initializeComponents();

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void addComponent(Component *component);

    [[nodiscard]]std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

};
