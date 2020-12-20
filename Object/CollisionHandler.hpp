#pragma once

class EntityObject;

class CollisionHandler {
public:
    virtual void onCollisionEnter(EntityObject entityObject) = 0;
    virtual void onCollisionExit(EntityObject entityObject) = 0;
};


