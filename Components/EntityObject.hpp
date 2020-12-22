#pragma once

#include "Component.hpp"
#include "PhysicsComponent.hpp"
#include "../Object/CollisionHandler.hpp"

#include <memory>
#include <utility>
#include <vector>
#include <string>

class TransformComponent;

class Pool;

class EntityObject : public Component {
public:
    //Weapons = Pistol, RPG etc
    //Resource = Water, Cookie, etc,
    //Object = Wall, Turret, Box, etc
    //Level_chagne = go to diffrent level
    enum EntityType {
        weapon, resource, object, level_change, character
    };
protected:
    std::vector<std::unique_ptr<Component>> _components;
    TransformComponent *_transformComponent = nullptr;
    PhysicsComponent *_physicsComponent = nullptr;

    Pool *_pool = nullptr;
    EntityType _type;
public:
    std::string entityName;
public:
    explicit EntityObject(EntityId id, const std::string name, const std::string &type) : Component(id),
                                                                                          entityName(std::move(name)) {
        if (type == "object") {
            _type = EntityType::object;
        }

        if (type == "character") {
            _type = EntityType::character;
        }

        if (type == "level_change") {
            _type = EntityType::level_change;
        }

        if (type == "weapon") {
            _type = EntityType::weapon;
        }

        if (type == "resource") {
            _type = EntityType::resource;
        }
    }

    explicit EntityObject(EntityId id, const std::string name, EntityType type = EntityType::object) : Component(id),
                                                                               entityName(name),
                                                                               _type(type) {}

    TransformComponent *getTransform();

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

    Component *getComponent(std::string componentName);

    EntityType getType();

    ~EntityObject() override = default;

    void initializeComponents();

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void addComponent(Component *component);

    [[nodiscard]]std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void setPool(Pool &pool);

    void destroy();
};
