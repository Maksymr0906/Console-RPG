#include "Enemy.hpp"

Enemy::Enemy() :
	Entity{ def_name, def_health, def_health, def_min_damage, def_max_damage, def_level, def_defence }, dropChance{ 0 }, droppedItem{ nullptr } {}

Enemy::Enemy(int level) :
	Entity{ def_name,
	level * 100,
	level * 100,
	level * 2,
	level * 3,
	level,
	level * 3 },
	dropChance{ level * 15 },
	droppedItem{ nullptr } {}

void Enemy::readFromTxtFile(std::ifstream &infile) {
	Entity::readFromTxtFile(infile);
	int itemCategory{};
	infile >> dropChance >> itemCategory;

	if(itemCategory == 1)
		droppedItem = std::make_shared<Weapon>();
	if(itemCategory == 2)
		droppedItem = std::make_shared<Armor>();
	if(itemCategory == 3)
		droppedItem = std::make_shared<Product>();
	if(droppedItem) {
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		droppedItem->readFromTxtFile(infile);
	}
}

void Enemy::writeToTxtFile(std::ofstream &outfile) const {
	Entity::writeToTxtFile(outfile);
	outfile << dropChance << '\n'
		<< static_cast<int>(droppedItem->getCategory()) << '\n';
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

	Category itemCategory = droppedItem->getCategory();
	if(itemCategory == Category::WEAPON)
		itemToDrop = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(droppedItem.get()));
	if(itemCategory == Category::ARMOR)
		itemToDrop = std::make_shared<Armor>(*dynamic_cast<Armor *>(droppedItem.get()));
	if(itemCategory == Category::PRODUCT)
		itemToDrop = std::make_shared<Product>(*dynamic_cast<Product *>(droppedItem.get()));

	return itemToDrop;
}