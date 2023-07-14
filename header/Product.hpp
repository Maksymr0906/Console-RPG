#pragma once

#include "Item.hpp"


class Product : public Item {
private:
	static constexpr const char *def_name = "Unnamed";
	static constexpr const char *def_category = "Product";
	static constexpr const char *def_status = "Unequipped";
	static constexpr const int def_purchase_price = 100;
	static constexpr const int def_sale_price = 80;
	static constexpr const int def_level = 1;
	static constexpr const int def_rarity = 1;
	static constexpr const int def_item_type = 3;
	static constexpr const int def_hunger_restored = 0;
	static constexpr const int def_energy_restored = 0;
	static constexpr const int def_health_restored = 0;
	static constexpr const int def_thirstRestored = 0;
	static constexpr const int def_radiation_restored = 0;
protected:
	int hungerRestored, energyRestored;
	int healthRestored, thirstRestored, radiationRestored;
public:
	Product(const char *name = def_name, const char *category = def_category, const char *status = def_status,
			int purchasePrice = def_purchase_price, int salePrice = def_sale_price,
			int level = def_level, int rarity = def_rarity, int itemType = def_item_type,
			int hungerRestored = def_hunger_restored, int energyRestored = def_energy_restored,
			int healthRestored = def_health_restored, int thirstRestored = def_thirstRestored,
			int radiationRestored = def_radiation_restored)
		:Item{ name, category, status, purchasePrice, salePrice, level, rarity, itemType },
		hungerRestored{ hungerRestored }, energyRestored{ energyRestored },
		healthRestored{ healthRestored }, thirstRestored{ thirstRestored },
		radiationRestored{ radiationRestored } {}
	Product(const Product &other) 
		:Item(other),
		hungerRestored{ other.hungerRestored }, energyRestored{ other.energyRestored },
		healthRestored{ other.healthRestored }, thirstRestored{ other.thirstRestored }, 
		radiationRestored{ other.radiationRestored } {}
	virtual ~Product() = default;

	virtual void equip() override;
	virtual void unequip() override;
	virtual void writeToTxtFile(std::ofstream &outfile) const override;
	virtual void readFromTxtFile(std::ifstream &infile) override;
	virtual void serialize(std::ofstream &outfile) const override;
	virtual void deserialize(std::ifstream &infile) override;
	virtual void print(std::ostream &os) const override;

	int getHungerRestored() const { return hungerRestored; }
	int getEnergyRestored() const { return energyRestored; }
	int getHealthRestored() const { return healthRestored; }
	int getThirstRestored() const { return thirstRestored; }
	int getRadiationRestored() const { return radiationRestored; }

	void setHungerRestored(int hungerRestored) { this->hungerRestored = hungerRestored; }
	void setEnergyRestored(int energyRestored) { this->energyRestored = energyRestored; }
	void setHealthRestored(int healthRestored) { this->healthRestored = healthRestored; }
	void setThirstRestored(int thirstRestored) { this->thirstRestored = thirstRestored; }
	void setRadiationRestored(int radiationRestored) { this->radiationRestored = radiationRestored; }

	bool operator==(const Product &other) const;
};