#include "Product.hpp"

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

void Product::print(std::ostream &os) const {
	Item::print(os);
	os << std::left << "\nHealth: " << this->healthRestored
		<< std::left << "\nEnergy: " << this->energyRestored
		<< std::left << "\nThirst: " << this->thirstRestored
		<< std::left << "\nHunger: " << this->hungerRestored
		<< std::left << "\nRadiation: " << this->radiationRestored << std::endl;
}

void Product::printStatus(std::ostream &os) const {}
void Product::printLevel(std::ostream &os) const {}
void Product::printRarity(std::ostream &os) const {}

bool Product::operator==(const Product &other) const {
	return Item::operator==(other) && hungerRestored == other.hungerRestored &&
		energyRestored == other.energyRestored && healthRestored == other.healthRestored &&
		thirstRestored == other.thirstRestored && radiationRestored == other.radiationRestored;
}