#include "Game.hpp"

Game::Game() {
    playing = true;
    gameOption = GameOption::BACK_TO_MAIN_MENU;
    indexOfActivePlayer = 0;
}

void Game::initialize() {
    this->backstory();
}

void Game::mainMenu() {
    std::cout << "\n(0) - Exit\n(1) - Create a new character\n(2) - Load characters\n";
    int choice = getNumber("\nEnter your choice: ");
    if(choice == 0) {
        playing = false;
    }
    else if(choice == 1) {
        createNewPlayer();
    }
    else if(choice == 2) {
        loadPlayers();
    }
}

void Game::gameMenu() {
    printGameMenu();
    gameOption = getGameOption();
    switch(gameOption) {
        case GameOption::BACK_TO_MAIN_MENU:
            Game::mainMenu();
            break;
        case GameOption::REST:
            //Will be implemented soon
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
        case GameOption::LEVEL_UP:
            players[indexOfActivePlayer].levelUp();
            break;
        case GameOption::UPGRADE_CHARACTERISTICS:
            players[indexOfActivePlayer].increaseAttributes();
            break;
        case GameOption::CREATE_NEW_PLAYER:
            createNewPlayer();
            break;
        case GameOption::SAVE_PLAYER:
            savePlayers();
            break;
        case GameOption::LOAD_PLAYER:
            loadPlayers();
            break;
        default:
            std::cout << "Incorrect choice" << std::endl;
            break;
    }
}

//Remove 8, 9, 10. If I choose 0, then show the message whether to save the player or not, if it did not be saved before
void Game::printGameMenu() const {
    std::cout << std::endl << std::setw(20) << std::right << "Game Menu" << std::endl
        << "(0) - Back to main menu" << std::endl
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

    std::cout << std::endl << std::setw(70) << std::right << "/*/*Press any key to continue*/*/" << std::endl;
    _getch();
}

void Game::explore() {
    //Зробити шось із енергією
    players[indexOfActivePlayer].explore();

    Event event;
    event.generateEvent(players[indexOfActivePlayer]);
}

void Game::createNewPlayer() {
    std::cin.ignore();
    std::string name{};
    std::cout << "\nEnter the name of your character: ";
    getline(std::cin, name);

    players = getPlayersFromFile("Players/players.bin");

    int indexOfPlayerWithSameName = findPlayerIndexByName(name);
    

    if(indexOfPlayerWithSameName == -1) {
        players.push_back(Player());
        indexOfActivePlayer = players.size() - 1;
        players[indexOfActivePlayer].initialize(name);
    }
    else {
        int number{};
        do {
            number = getNumber("\nCharacter with entered name is already exist. Do you want to exchange him?\n1 - Yes\n2 - No\nYour choice: ");
            
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
                Game::createNewPlayer();
            }
        } while(number < 1 || number > 2);
    }
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
    std::ofstream outFile("Players/players.bin", std::ios::binary);
   
    for(const auto &player : players) {
        player.serialize(outFile);
    }

    outFile.close();

    std::cout << "\nYour characters are saved" << std::endl;
}

void Game::loadPlayers() {
    players.clear();
    players = getPlayersFromFile("Players/players.bin");

    int choice{};
    do {
        displayAllPlayers();

        choice = getNumber("Which character you want to play: ");
        if(choice <= 0 || choice > players.size()) {
            std::cout << "\nCharacter with this number does not exist. Choose another number.\n";
        }
        else {
            indexOfActivePlayer = choice - 1;
        }
    } while(choice <= 0 || choice > players.size());
}

void Game::displayAllPlayers() const {
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << players[i].getName() << std::endl;
    }
}

std::vector<Player> Game::getPlayersFromFile(const std::string &filePath) {
    std::ifstream inFile(filePath, std::ios::binary);

    std::vector<Player> result;
    while(!inFile.eof()) {
        Player p;
        if(!p.deserialize(inFile))
            break;

        result.push_back(p);
    }

    inFile.close();

    return result;
}