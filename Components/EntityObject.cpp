#include "EntityObject.hpp"

void EntityObject::update() {

}

std::string EntityObject::name() const {
    return "EntityObject";
}

Component *EntityObject::Clone(EntityId entityId) const {
    return new EntityObject(entityId);
}
