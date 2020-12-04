#include "ComponentFactory.hpp"

#include "PhysicsComponent.hpp"

ComponentFactory::ComponentFactory() {


    components["PhysicsComponent"] = make_unique<PhysicsComponent>();

//    PhysicsComponent *component = (PhysicsComponent *) components["PhysicsComponent"].get();
//    unique_ptr<PhysicsComponent> newComponent = make_unique<PhysicsComponent>(*component);
//    newComponent->wow = "melisa my love";
//
//    PhysicsComponent *component1 = (PhysicsComponent *) components["PhysicsComponent"].get();

}
