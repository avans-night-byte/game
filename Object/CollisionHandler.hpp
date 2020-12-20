#pragma once

class EntityObject;

class CollisionHandler {
public:
    virtual void onCollisionEnter(const EntityObject *entityObject) = 0;

    virtual void onCollisionExit(const EntityObject *entityObject) = 0;
};


