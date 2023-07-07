#include "Game.hpp"

Game::Game() {
    playing = true;
    gameOption = GameOption::BACK_TO_MAIN_MENU;
    indexOfActivePlayer = 0;
    isPlayerSaved = true;
}

void Game::initialize() {
    this->backstory();
    Event::initialize();
}

void Game::mainMenu() {
    players.clear();
    players = loadPlayers("Players/players.txt");
    bool isAnyPlayerExist = !players.empty();
    do {
        int choice = getValidateAnswer("(0) - Exit\n(1) - Create a new character\n(2) - Load characters\n\nEnter your choice: ", "\nIncorrect choice", 0, 2);

        if(choice == 0) {
            playing = false;
            break;
        }
        else if(choice == 1) {
            createNewPlayer();
            isAnyPlayerExist = true;
        }
        else if(choice == 2) {
            if(!isAnyPlayerExist) {
                std::cout << "\nYou don't have savings. Create a new character first." << std::endl;
            }
            else
                selectPlayer();
        }
    } while(!isAnyPlayerExist);

}

void Game::gameMenu() {
    if(!players[indexOfActivePlayer].isAlive()) {
        std::cout << "\nYou die" << std::endl;
        playing = false;
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
            shop(players[indexOfActivePlayer]);
            break;
        case GameOption::VIEW_STATS:
            players[indexOfActivePlayer].showStats();
            break;
        case GameOption::VIEW_INVENTORY:
            players[indexOfActivePlayer].showInventory();
            break;
        case GameOption::UPGRADE_CHARACTERISTICS:
            players[indexOfActivePlayer].increaseAttributes();
            break;
        case GameOption::SAVE_PLAYER:
            savePlayers();
            break;
        default:
            std::cout << "Incorrect choice" << std::endl;
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
        char saveChoice{};
        do {
            std::cout << "\nDo you want to save the player before returning to the main menu? (Y/N): ";

            std::cin >> saveChoice;
            if(saveChoice == 'Y' || saveChoice == 'y') {
                savePlayers();
            }
            else if(saveChoice == 'N' || saveChoice == 'n') {
                return;
            }
            else {
                std::cout << "\nIncorrect choice" << std::endl;
            }
        } while(saveChoice != 'Y' && saveChoice != 'y' && saveChoice != 'N' && saveChoice != 'n');
    }
}

void Game::printGameMenu() const {
    std::cout << std::endl << std::setw(20) << std::right << "Game Menu" << std::endl
        << "(0) - Back to main menu" << std::endl
        << "(1) - Explore world" << std::endl
        << "(2) - Return to shelter" << std::endl
        << "(3) - Visit Merchant" << std::endl
        << "(4) - Player's characteristics" << std::endl
        << "(5) - Player's inventory" << std::endl
        << "(6) - Upgrade characteristics" << std::endl
        << "(7) - Save player" << std::endl << std::endl;
}

void Game::backstory() const {
    std::cout << "Zombie Project - a simple console game in which you have to survive in an unfair world full of zombies." << std::endl
        << "You come to your senses in an empty New York, which is full of zombies." << std::endl
        << "For now, all you need is to survive, and how to achieve this depends on you." << std::endl
        << "So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive." << std::endl;

    std::cout << std::endl << std::setw(70) << std::right << "/*/*Press Enter to continue*/*/" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("CLS");
}

void Game::explore() {
    Inventory &inventory = players[indexOfActivePlayer].getInventory();
    if(inventory.getInventory().size() == inventory.getSizeOfInventory()) {
        std::cout << "My backpack is full. I need to do something about this and continue searching..." << std::endl;
        return;
    }
    players[indexOfActivePlayer].explore();

    Event event;
    event.generateEvent(players[indexOfActivePlayer]);
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
            number = getNumber("\nCharacter with entered name is already exist. Do you want to exchange him?\n(1) - Yes\n(2) - No\nYour choice: ");

            if(number < 1 || number > 2) {
                std::cout << "\nIncorrect choice. Choose correct number." << std::endl;
            }
            else if(number == 1) {
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
    std::ofstream outFile("Players/players.txt", std::ios::binary);
    int numOfPlayers = players.size();
    outFile << numOfPlayers << '\n';
    for(const auto &player : players) {
        player.writeToTxtFile(outFile);
    }

    outFile.close();
}

void Game::selectPlayer() {
    if(players.empty()) {
        return;
    }

    int choice{};
    displayAllPlayers();
    choice = getValidateAnswer("Which character you want to play: ", "\nThis character does not exist. Choose correct number.", 1, players.size());
    indexOfActivePlayer = choice - 1;
}

void Game::displayAllPlayers() const {
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << players[i].getName() << std::endl;
    }
}

std::vector<Player> Game::loadPlayers(const std::string &filePath) {
    std::ifstream inFile(filePath, std::ios::binary);

    if(!inFile) {
        return {};
    }

    int numOfPlayers{};
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

void Game::deletePlayerByIndex() {
    savePlayers();
    players = loadPlayers("Players/players.txt");
    displayAllPlayers();
    int choice = getValidateAnswer("Choose the index of player you wanna delete: ", "Incorrect choice. Try again", 1, players.size());
    players.erase(players.begin() + choice - 1);
}

void Game::shelter() {
    int choice{};
    do {
        std::cout << "(0) - Back to the street\n(1) - My bed\n(2) - WorkBench\n(3) - My box\n";
        choice = getValidateAnswer("Your choice: ", "Incorrect choice", 0, 3);
        if(choice == 0) {
            return;
        }
        else if(choice == 1) {
            sleep();
        }
        else if(choice == 2) {
            std::cout << "Craft" << std::endl;
        }
        else if(choice == 3) {
            std::cout << "My box" << std::endl;
        }
    } while(choice != 0);
}

void Game::sleep() {
    if(players[indexOfActivePlayer].getHunger() < 40 || players[indexOfActivePlayer].getThirst() < 40) {
        std::cout << "\nI need to raise my hunger and thirst to 40 or I won't be able to sleep" << std::endl;
    }
    else {
        players[indexOfActivePlayer].sleep();
        std::cout << "\nI slept well. My energy are restored" << std::endl;
    }
}