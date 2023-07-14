#include "Enemy.hpp"

Enemy::Enemy() :
	Entity{ def_name, def_health, def_health, def_min_damage, def_max_damage, def_level, def_defence }, dropChance{ 0 } {}

Enemy::Enemy(int level) : 
  Entity{def_name,
  level * 100,
  level * 100,
  level * 2,
  level * 3,
  level,
  level * 3},
  dropChance{level * 15} {}

