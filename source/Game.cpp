#include "Game.hpp"

Game::Game() {
    playing = true;
    gameOption = GameOption::BACK_TO_MAIN_MENU;
    indexOfActivePlayer = -1;
    isPlayerSaved = true;
    this->timeToUpdateStore = 0;
}

void Game::initialize() {
    this->backstory();
    Event::initialize();
    this->timeToUpdateStore = 0;
}

void Game::mainMenu() {
    CLEAR_SCREEN;
    this->timeToUpdateStore = 0;
    players.clear();
    players = loadPlayers("players.txt");
    indexOfActivePlayer = -1;

    do {
        int choice = getValidatedAnswer("(0) - Exit\n(1) - Create a new character\n(2) - Load characters\n(3) - Delete characters\n\nEnter your choice: ", "\nInvalid choice", 0, 3);

        if(choice == 0) {
            playing = false;
            break;
        }
        else if(choice == 1) {
            createNewPlayer();
        }
        else if(choice == 2) {
            if(players.empty()) {
                std::cout << "\nYou don't have savings. Create a new character first." << std::endl;
            }
            else {
                int indexOfSelectedPlayer = selectPlayer();
                if(indexOfSelectedPlayer != 0)
                    indexOfActivePlayer = indexOfSelectedPlayer - 1;
            }

        }
        else if(choice == 3) {
            if(players.empty()) {
                std::cout << "\nYou don't have savings to delete." << std::endl;
            }
            else {
                deletePlayer();
            }
        }
    } while(players.empty() || indexOfActivePlayer == -1);
    CLEAR_SCREEN;
}

void Game::gameMenu() {
    if(!players[indexOfActivePlayer].isAlive()) {
        std::cout << "\nYou die\nYour character will be automatically deleted" << std::endl;
        deletePlayerByIndex(indexOfActivePlayer);
        mainMenu();
        if(indexOfActivePlayer == -1)
            return;
    }
    players[indexOfActivePlayer].levelUp();

    if(gameOption != GameOption::VIEW_STATS)
        players[indexOfActivePlayer].previewPlayer();
    printGameMenu();
    gameOption = getGameOption();

    //system("CLS");
    switch(gameOption) {
        case GameOption::BACK_TO_MAIN_MENU:
            askToSavePlayer();
            mainMenu();
            break;
        case GameOption::RETURN_SHELTER:
            shelter();
            break;
        case GameOption::EXPLORE_WORLD:
            explore();
            break;
        case GameOption::SHOP:
            shop();
            break;
        case GameOption::VIEW_STATS:
            players[indexOfActivePlayer].printStats();
            break;
        case GameOption::VIEW_INVENTORY:
            players[indexOfActivePlayer].printInventory();
            break;
        case GameOption::UPGRADE_CHARACTERISTICS:
            players[indexOfActivePlayer].increaseStatAttributes();
            break;
        case GameOption::SAVE_PLAYER:
            savePlayers();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
    }

    if(gameOption != GameOption::SAVE_PLAYER && gameOption != GameOption::BACK_TO_MAIN_MENU) {
        isPlayerSaved = false;
    }
    else {
        isPlayerSaved = true;
    }
}

void Game::askToSavePlayer() {
    if(!isPlayerSaved) {
        int choice{};
        do {
            choice = getValidatedAnswer("\nDo you want to save the player before returning to the main menu?\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);
            if(choice == 1) {
                savePlayers();
            }
        } while(choice != 1 && choice != 2);
    }
}

void Game::printGameMenu() const {
    std::cout << std::endl << std::setw(20) << std::right << "Game Menu" << std::endl
        << "(0) - Back to main menu" << std::endl
        << "(1) - Explore world" << std::endl
        << "(2) - Return to shelter" << std::endl
        << "(3) - Visit Merchant" << std::endl
        << "(4) - My characteristics" << std::endl
        << "(5) - My Inventory" << std::endl
        << "(6) - Upgrade characteristics" << std::endl
        << "(7) - Save game" << std::endl << std::endl;
}

void Game::backstory() const {
    std::cout << "Zombie Project - a simple console-based RPG game in which you have to survive in an unfair world full of zombies." << std::endl
        << "You come to your senses in an empty New York, which is full of zombies." << std::endl
        << "For now, all you need is to survive, and how to achieve this depends on you." << std::endl
        << "So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive." << std::endl;
    std::cout << std::endl << std::setw(70) << std::right << "=== Press Enter to continue ===" << std::endl;
    std::string input{};
    std::getline(std::cin, input);
    CLEAR_SCREEN;
}

void Game::explore() {
    CLEAR_SCREEN;
    Inventory &inventory = players[indexOfActivePlayer].getInventory();
    if(inventory.getItems().size() == inventory.getMaxNumberOfItems()) {
        std::cout << "My backpack is full. I need to do something about this and continue searching..." << std::endl;
        return;
    }
    timeToUpdateStore++;
    players[indexOfActivePlayer].explore();

    Event event;
    event.generateEvent(players[indexOfActivePlayer]);
    if(timeToUpdateStore == 10) {
        timeToUpdateStore = 0;
        std::cout << "Shop updated" << std::endl;
        event.updateShop();
    }
}

void Game::createNewPlayer() {
    std::string name{};
    std::cout << "\nEnter the name of your character: ";
    getline(std::cin, name);

    int indexOfPlayerWithSameName = findPlayerIndexByName(name);

    if(indexOfPlayerWithSameName == -1) {
        players.push_back(Player());
        indexOfActivePlayer = players.size() - 1;
        players[indexOfActivePlayer].initialize(name);
    }
    else {
        int number{};
        do {
            number = getValidatedAnswer("\nCharacter with entered name is already exist. Do you want to exchange him?\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);

            if(number == 1) {
                Player player;
                indexOfActivePlayer = indexOfPlayerWithSameName;
                player.initialize(name);
                players.at(indexOfActivePlayer) = player;
            }
            else if(number == 2) {
                std::cout << "\nThen come up with the new name" << std::endl;
                createNewPlayer();
            }
        } while(number < 1 || number > 2);
    }

    std::cout << std::endl << name << " succesfully created! Welcome to the game!" << std::endl;
    savePlayers();
}

int Game::findPlayerIndexByName(const std::string &name) const {
    for(size_t i = 0; i < players.size(); i++) {
        if(players[i].getName() == name) {
            return i;
        }
    }

    return -1;
}

void Game::savePlayers() {
    std::ofstream outFile("players.txt", std::ios::binary);
    size_t numOfPlayers = players.size();
    outFile << numOfPlayers << '\n';
    for(const auto &player : players) {
        player.writeToTxtFile(outFile);
    }

    outFile.close();
}

int Game::selectPlayer() {
    if(players.empty()) {
        return 0;
    }

    int choice{};
    printAllPlayers();
    choice = getValidatedAnswer("Which character you want to play: ", "\nThis character does not exist. Choose correct number.", 0, players.size());

    return choice;
}

void Game::printAllPlayers() const {
    std::cout << "\n(0) - Exit" << std::endl;
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << players[i].getName() << std::endl;
    }
}

std::vector<Player> Game::loadPlayers(const std::string &filePath) {
    std::ifstream inFile(filePath, std::ios::binary);

    if(!inFile) {
        return {};
    }

    size_t numOfPlayers{};
    inFile >> numOfPlayers;
    std::vector<Player> result;
    while(result.size() < numOfPlayers) {
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Player p;
        p.readFromTxtFile(inFile);

        result.push_back(p);
    }

    inFile.close();

    return result;
}

void Game::deletePlayer() {
    savePlayers();
    players = loadPlayers("players.txt");
    printAllPlayers();
    int choice = getValidatedAnswer("Choose the index of player you wanna delete: ", "Invalid choice. Try again", 0, players.size());
    if(choice != 0) {
        deletePlayerByIndex(choice - 1);
    }
}

void Game::deletePlayerByIndex(int index) {
    players.erase(players.begin() + index);
    savePlayers();
}

void Game::shelter() {
    int choice{};
    do {
        choice = getValidatedAnswer("\n(0) - Back to the outside\n(1) - My bed\n(2) - WorkBench\nYour choice: ", "Invalid choice", 0, 2);
        if(choice == 0) {
            return;
        }
        else if(choice == 1) {
            sleep();
        }
        else if(choice == 2) {
            std::cout << "\nHere I can upgrade your items, such as armor and weapons" << std::endl;
            players[indexOfActivePlayer].upgradeItem();
        }
    } while(choice != 0);
}

void Game::sleep() {
    std::cout << "\nHere I can sleep and restore my energy" << std::endl;
    std::cout << "My stamina: " << players[indexOfActivePlayer].getStamina() << " / " << players[indexOfActivePlayer].getStaminaMax() << std::endl;
    int choice = getValidatedAnswer("Should I sleep?\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);
    
    if(choice == 1)
        players[indexOfActivePlayer].sleep();
    else
        std::cout << "I chose not to waste time sleeping" << std::endl;
}

void Game::shop() {
    Event event;
    event.shop(players[indexOfActivePlayer]);
}