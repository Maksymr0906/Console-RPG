#include "Zombie.hpp"

bool Zombie::isAlive() {
    return health > 0 ? true : false;
}