#include "Product.hpp"

void Product::equip() {}
void Product::unequip() {}

void Product::writeToTxtFile(std::ofstream &outfile) const {
	Item::writeToTxtFile(outfile);
	outfile << hungerRestored << "\n"
			<< energyRestored << "\n"
			<< healthRestored << "\n"
			<< thirstRestored << "\n"
			<< radiationRestored << "\n";
}

void Product::readFromTxtFile(std::ifstream &infile) {
	Item::readFromTxtFile(infile);
	infile >> hungerRestored >> energyRestored >> healthRestored
		   >> thirstRestored >> radiationRestored;
}
void Product::serialize(std::ofstream &outfile) const {
	Item::serialize(outfile);
	outfile.write(reinterpret_cast<const char *>(&hungerRestored), sizeof(hungerRestored));
	outfile.write(reinterpret_cast<const char *>(&energyRestored), sizeof(energyRestored));
	outfile.write(reinterpret_cast<const char *>(&healthRestored), sizeof(healthRestored));
	outfile.write(reinterpret_cast<const char *>(&thirstRestored), sizeof(thirstRestored));
	outfile.write(reinterpret_cast<const char *>(&radiationRestored), sizeof(radiationRestored));
}

void Product::deserialize(std::ifstream &infile) {
	Item::deserialize(infile);
	infile.read(reinterpret_cast<char *>(&hungerRestored), sizeof(hungerRestored));
	infile.read(reinterpret_cast<char *>(&energyRestored), sizeof(energyRestored));
	infile.read(reinterpret_cast<char *>(&healthRestored), sizeof(healthRestored));
	infile.read(reinterpret_cast<char *>(&thirstRestored), sizeof(thirstRestored));
	infile.read(reinterpret_cast<char *>(&radiationRestored), sizeof(radiationRestored));
}

void Product::print(std::ostream &os) const {
	os << std::setw(30) << std::right << this->name << std::endl
		<< std::left << "Health: " << this->healthRestored << std::endl
		<< std::left << "Energy: " << this->energyRestored << std::endl
		<< std::left << "Thirst: " << this->thirstRestored << std::endl
		<< std::left << "Hunger: " << this->hungerRestored << std::endl
		<< std::left << "Radiation: " << this->radiationRestored << std::endl
		<< std::left << "Purchase/Sell Price: " << this->purchasePrice << " / " << this->salePrice << std::endl;
}

bool Product::operator==(const Product &other) const {
	return Item::operator==(other) && hungerRestored == other.hungerRestored &&
		energyRestored == other.energyRestored && healthRestored == other.healthRestored &&
		thirstRestored == other.thirstRestored && radiationRestored == other.radiationRestored;
}