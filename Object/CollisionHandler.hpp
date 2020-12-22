#pragma once

class EntityObject;

class CollisionHandler {
public:
    virtual void onCollisionEnter(EntityObject *self, EntityObject *other) = 0;

    virtual void onCollisionExit(EntityObject *self, EntityObject *other) = 0;
};


