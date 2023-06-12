#include "Game.hpp"

Game::Game() {
    playing = true;
    option = Option::QUIT;
    indexOfActivePlayer = 0;
}

void printMenu() {
    std::cout << std::endl << std::setw(20) << std::right << "Main Menu" << std::endl
        << "(0) - Quit" << std::endl
        << "(1) - Explore world" << std::endl
        << "(2) - Rest" << std::endl
        << "(3) - Visit Merchant" << std::endl
        << "(4) - Player's characteristics" << std::endl
        << "(5) - Player's inventory" << std::endl
        << "(6) - Level up" << std::endl
        << "(7) - Upgrade characteristics" << std::endl
        << "(8) - Create new player" << std::endl
        << "(9) - Save player" << std::endl
        << "(10) - Load player" << std::endl;
}

void Game::backstory() const {
    std::cout << "Zombie Project - a simple console game in which you have to survive in an unfair world full of zombies." << std::endl
        << "You come to your senses in an empty New York, which is full of zombies." << std::endl
        << "All you have in your pockets is a knife, Coca-Kolya, and a loaf of bread." << std::endl
        << "For now, all you need is to survive, and how to achieve this depends on you." << std::endl
        << "So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive." << std::endl;

    std::cout << std::endl << "/*/*Press any key to continue/*/*" << std::endl;
    _getch();
}

void Game::initialize() {
    
}

void Game::mainMenu() {
    printMenu();
    option = getOption();
    switch (option) {
    case Option::QUIT:
        playing = false;
        break;
    case Option::REST:

        break;
    case Option::EXPLORE_WORLD:
        explore();
        break;
    case Option::SHOP:
        shop(players[indexOfActivePlayer]);
        break;
    case Option::VIEW_STATS:
        players[indexOfActivePlayer].showStats();
        break;
    case Option::VIEW_INVENTORY:
        players[indexOfActivePlayer].showInventory();
        break;
    case Option::LEVEL_UP:
        players[indexOfActivePlayer].levelUp();
        break;
    case Option::UPGRADE_CHARACTERISTICS:
        players[indexOfActivePlayer].increaseAttributes();
        break;
    case Option::CREATE_NEW_PLAYER:
        std::cin.ignore();
        createNewPlayer();
        break;
    case Option::SAVE_PLAYER:
        savePlayers();
        break;
    case Option::LOAD_PLAYER:
        loadPlayers();
        break;
    default:
        std::cout << "Incorrect choice" << std::endl;
        break;
    }
}

void Game::explore() {
    players[indexOfActivePlayer].explore();

    Event event;
    event.generateEvent(players[indexOfActivePlayer]);
}

void Game::createNewPlayer() {
    std::cin.ignore();
    std::string name{};
    std::cout << "\nEnter the name of your character: ";
    getline(std::cin, name);

    players.push_back(Player());
    indexOfActivePlayer = players.size() - 1;
    players[indexOfActivePlayer].initialize(name);
}

void Game::savePlayers() {
 /*   std::ifstream inFile("Players/players.bin", std::ios::binary);

    std::vector<Player> temp;
    while(!inFile.eof()) {
        Player p;
        if(!p.deserialize(inFile))
            break;

        temp.push_back(p);
    }

    inFile.close();

    for(size_t i = 0; i < players.size(); i++) {
        for(size_t j = 0; j < temp.size(); i++) {
            if(players[i] == temp[j]) {

            }
        }
    }*/

    std::ofstream outFile("Players/players.bin", std::ios::binary);

    for(const auto &player : players) {
        player.serialize(outFile);
    }
    outFile.close();
    std::cout << "\nYour characters are saved" << std::endl;
}

void Game::loadPlayers() {
    players.clear();
    std::ifstream inFile("Players/players.bin", std::ios::binary);

    while(!inFile.eof()) {
        Player temp;
        if(!temp.deserialize(inFile))
            break;

        players.push_back(temp);
    }

    inFile.close();
    
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << players[i].getName() << std::endl;
    }

    int choice = getNumber("Which character you want to play: ");
    indexOfActivePlayer = choice - 1;
}

void Game::startGame() {
    this->backstory();
    this->initialize();
    std::cout << "(1) - Create new character\n(2) - Savings\n(3) - Exit\n";
    int choice = getNumber("Enter your choice: ");

    if(choice == 1) {
        createNewPlayer();
    }
    else if(choice == 2) {
        loadPlayers();
    }
    else if(choice == 3) {
        playing = false;
    }
}