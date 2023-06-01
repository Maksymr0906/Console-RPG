#include "Enemy.hpp"

Enemy::Enemy() :
	maxHealth{def_health},
	health{ def_health },
	minDamage{ def_min_damage },
	maxDamage{ def_max_damage },
	dropChance{ def_drop_chance },
	defence{ def_defence } {}

Enemy::Enemy(int level)
: maxHealth{level * 100},
  health{maxHealth},
  minDamage{level * 2},
  maxDamage{level * 3},
  dropChance{level * 15},
  defence{level * 3} {}

