#include "EntityObject.hpp"
#include "RenderComponent.hpp"

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {
    for (auto &component : components) {
        component->fixedUpdate(deltaTime);
    }
}

void EntityObject::addComponent(Component *component) {
    components.push_back(std::unique_ptr<Component>(component));
}

Component *EntityObject::clone(EntityId entityId, const Components::component *component) {
    return new EntityObject(entityId);
}

void EntityObject::render() {
    for (auto &component : components) {
        component->render();
    }
}

void EntityObject::update(const Input &inputSystem) {
    for (auto &component : components) {
        component->update(inputSystem);
    }
}

void EntityObject::initializeComponents() {
    // TODO : Poop
    for(auto &comp: components)
    {
        if(comp->name() == "RenderComponent")
        {
            auto* renderComponent = (RenderComponent*)comp.get();
            for(auto &comp1: components)
            {
                if(comp1->name() == "TransformComponent")
                {
                    renderComponent->setTransform((TransformComponent*)comp1.get());
                }

                if(comp1->name() == "PhysicsComponent")
                {
                    renderComponent->setPhysicsComponent((PhysicsComponent*)comp1.get());
                }
            }
        }
    }
}
