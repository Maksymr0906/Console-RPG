#pragma once

#include <stdlib.h>
#include <exception>
#include <unordered_map>

#include "Puzzle.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

enum class RandomEvent {
	EMPTY_EVENT = 1,
	PUZZLE,
	FOUND_ITEM,
	FIGHT
};

enum class FightOption {
	ESCAPE = 0,
	ATTACK,
	USE_ITEM,
	RESTORE_ENERGY
};

enum class ShopOption {
	LEAVE_SHOP = 0,
	WEAPON_SHOP,
	ARMOR_SHOP,
	PRODUCTS_SHOP,
	INCREASE_BACKPACK,
	SELL_ITEMS
};

class Event {
private:
	static constexpr const int MAX_ITEMS_TO_SELL_IN_EACH_CATEGORY = 3;
	static constexpr const int MIN_REWARD_FOR_COMPLETED_PUZZLE = 10;
	static constexpr const int MAX_REWARD_FOR_COMPLETED_PUZZLE = 15;
	static constexpr const int STAMINA_TO_ESCAPE_FROM_FIGHT = 60;
	static constexpr const int HUNGER_TO_ESCAPE_FROM_FIGHT = 30;
	static constexpr const int THIRST_TO_ESCAPE_FROM_FIGHT = 30;

	//Methods
	static void readEnemiesFromFile(const std::string &fileName);
	static void readEmptyEventMessagesFromFile(const std::string &fileName);
	static void readPuzzlesFromFile(const std::string &fileName); static void readWeaponsFromFile(const std::string &fileName);
	static void readArmorFromFile(const std::string &fileName);
	static void readProductsFromFile(const std::string &fileName);
	static void readItemsFromFile(const std::string &fileName, std::vector<std::shared_ptr<Item>> &items);
	static void generateItemsToSell();
	static void addRandomItemsToSell(std::vector<std::shared_ptr<Item>> &itemsToSell, std::vector<std::shared_ptr<Item>> &items);
	static bool itemExistsInItemsToSell(const std::vector<std::shared_ptr<Item>> &itemsToSell, std::shared_ptr<Item> &newItem);
	static std::shared_ptr<Item> getRandomItem(std::vector<std::shared_ptr<Item>> &items);

	RandomEvent calculateRandomEvent() const;
	void emptyEventEncouter() const;
	void puzzleEncouter(Player &p);
	Puzzle getRandomPuzzle() const;
	void completePuzzle(Player &p) const;
	void printPuzzleChances(const int &remainingChances) const;
	void foundItemEncouter(Player &p);
	Category getRandomCategory() const;
	void foundWeapon(Player &p) const;
	void foundArmor(Player &p) const;
	void foundProduct(Player &p) const;
	void foundItem(Player &player, const std::vector<std::shared_ptr<Item>> &items) const;
	std::shared_ptr<Item> getFoundItem(const std::vector<std::shared_ptr<Item>> &items, const int &foundItemIndex) const;
	void printMessageAboutFoundItem(const std::string &fileName, const std::string &nameOfItem) const;
	void fightEncouter(Player &p) const;
	Enemy generateRandomEnemy(Player &p) const;
	bool handlePlayerFirstMoveDecision(bool isPlayerTurn, Enemy &enemy) const;
	bool handlePlayerTurn(Player &p, Enemy &enemy, bool &isEscaping) const;
	void printCombatStatus(Player &p, Enemy &enemy) const;
	void printFightOptions() const;
	bool handleEscape(Player &p) const;
	bool isPlayerCanEscape(Player &p) const;
	void handleAttack(Player &p, Enemy &enemy) const;
	bool handleUsingItem(Player &p) const;
	void handleLowVitalParameters(Player &p) const;
	void consumePlayerParameters(Player &p) const;
	void handleEnemyTurn(Player &p, Enemy &enemy) const;
	void handleCombatReward(Player &p, Enemy &enemy) const;
	void weaponShop(Player &p) const;
	void armorShop(Player &p) const;
	void productsShop(Player &p) const;
	void shopInteraction(Player &p, const std::string &shopName, const std::vector<std::shared_ptr<Item>> &itemsToSell) const;
	std::shared_ptr<Item> getItemToSell(const std::string &shopName, size_t index) const;
	void printShopAssortment(const std::string &shopName, const std::vector<std::shared_ptr<Item>> &itemsToSell) const;
	void printItemDetails(size_t index, const std::shared_ptr<Item> &itemToSell) const;
	void increaseBackpack(Player &p) const;
	std::string getBackpackName(size_t choice) const;
	bool setNewBackpack(Player &p, const std::pair<int, size_t> &backpack) const;
	void sellItems(Player &p) const;
protected:
	static std::vector<Enemy> enemies;
	static std::vector<std::shared_ptr<Item>> itemsToSell;
	static std::vector<std::string> emptyEventMessages;
	static std::vector<Puzzle> puzzles;
	static std::vector<std::shared_ptr<Item>> products;
	static std::vector<std::shared_ptr<Item>> weapons;
	static std::vector<std::shared_ptr<Item>> armor;

	int numberOfEvents;
public:
	Event();
	~Event() = default;

	static void initialize();
	static void updateShop();

	void generateEvent(Player &p);
	void shop(Player &p) const;
};

