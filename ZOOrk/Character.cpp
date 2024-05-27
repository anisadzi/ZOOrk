//
// Created by Richard Skarbez on 5/7/23.
//

#include "Character.h"

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d), health(100), attack(10), move(5), initiative(1) {}

Character::~Character() {} // Implement the virtual destructor

int Character::getHealth() const {
    return health;
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

void Character::heal(int amount) {
    health += amount;
}
