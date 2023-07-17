#include "Enemy.hpp"

Enemy::Enemy() :
	Entity{ def_name, def_health, def_health, def_min_damage, def_max_damage, def_level, def_defence }, dropChance{ 0 }, droppedItem{nullptr} {}

Enemy::Enemy(int level) : 
  Entity{def_name,
  level * 100,
  level * 100,
  level * 2,
  level * 3,
  level,
  level * 3},
  dropChance{level * 15} {}

void Enemy::readFromTxtFile(std::ifstream &infile) {
	Entity::readFromTxtFile(infile);
	infile >> dropChance;
	std::string itemCategory{};
	infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(infile, itemCategory);
	if(itemCategory == "Weapon")
		droppedItem = std::make_shared<Weapon>();
	if(itemCategory == "Armor")
		droppedItem = std::make_shared<Armor>();
	if(itemCategory == "Product")
		droppedItem = std::make_shared<Product>();
	droppedItem->readFromTxtFile(infile);
}

void Enemy::writeToTxtFile(std::ofstream &outfile) const {
	Entity::writeToTxtFile(outfile);
	outfile << dropChance << '\n'
			<< droppedItem->getCategory() << '\n';
	droppedItem->writeToTxtFile(outfile);
}

void Enemy::print() const {
	std::cout << "\nName: " << this->name << std::endl;
	std::cout << "Health: " << this->health << " / " << this->maxHealth << std::endl
		<< "Damage: " << this->minDamage << " / " << this->maxDamage << std::endl
		<< "Level: " << this->level << std::endl
		<< "Drop chance: " << this->dropChance << std::endl
		<< "Defence: " << this->defence << std::endl
		<< "\nDropped item: " << std::endl
		<< *droppedItem << std::endl;
}

void Enemy::updateCharacteristics(int playerLevel) {
	if(playerLevel > 1) {
		this->level = playerLevel;
		this->maxHealth = this->maxHealth + (std::max((int)(this->maxHealth * 0.10), 1) * playerLevel);
		this->health = this->maxHealth;
		this->minDamage = this->minDamage + (std::max((int)(this->minDamage * 0.10), 1) * playerLevel);
		this->maxDamage = this->maxDamage + (std::max((int)(this->maxDamage * 0.10), 1) * playerLevel);
		this->defence = this->defence + (std::max((int)(this->defence * 0.10), 1) * playerLevel);
	}
}

std::shared_ptr<Item> Enemy::getDroppedItem() {
	std::shared_ptr<Item> itemToDrop;
	
	std::string itemCategory = droppedItem->getCategory();
	if(itemCategory == "Weapon")
		itemToDrop = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(droppedItem.get()));
	if(itemCategory == "Armor")
		itemToDrop = std::make_shared<Armor>(*dynamic_cast<Armor *>(droppedItem.get()));
	if(itemCategory == "Product")
		itemToDrop = std::make_shared<Product>(*dynamic_cast<Product *>(droppedItem.get()));

	return itemToDrop;
}