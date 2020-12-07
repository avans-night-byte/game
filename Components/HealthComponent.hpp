//
// Created by marco on 12/7/20.
//
#pragma once

#ifndef NIGHTBYTE_HEALTHCOMPONENT_HPP
#define NIGHTBYTE_HEALTHCOMPONENT_HPP


class HealthComponent {
private:
    float _healthPoints = 100;
public:
    HealthComponent() = default;

    [[nodiscard]] float getHealth() const;
    void setHealth(float newHealthPoints);
    void doDamage(float amountOfHealthPoints);
    void die();
};


#endif //NIGHTBYTE_HEALTHCOMPONENT_HPP
