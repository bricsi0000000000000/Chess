#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <string>
#include <vector>

#include "Grid.h"
#include "PieceManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "RuleManager.h"

PieceManager* PieceManager::instance = 0;
InputManager* InputManager::instance = 0;
GameManager* GameManager::instance = 0;
RuleManager* RuleManager::instance = 0;

class MenuManager {
private:
	MenuManager() {}
	static MenuManager* instance;

	void clearConsole() {
#ifdef _WIN32
		std::system("cls");
#endif
#ifdef linux
		std::system("clear");
#endif
	}
public:
	static MenuManager* Instance() {
		if (!instance) {
			instance = new MenuManager();
		}
		return instance;
	}

	void Menu() {
		clearConsole();

		std::cout << "    C H E S S\n\n";
		std::cout << "     |Menu|\n\n";
		std::cout << "      Play\n";
		std::cout << "    Results\n";
		std::cout << "      Exit\n\n";
		std::cout << "Select: ";

		std::string menu_input;
		std::cin >> menu_input;

		if (menu_input.compare("Play") == 0 || menu_input.compare("play") == 0 || menu_input.compare("p") == 0 || menu_input.compare("P") == 0) {
			Play();
		}
		else if (menu_input.compare("Results") == 0 || menu_input.compare("results") == 0 || menu_input.compare("r") == 0 || menu_input.compare("R") == 0) {
			Results();
		}
		else if (menu_input.compare("Exit") == 0 || menu_input.compare("exit") == 0 || menu_input.compare("e") == 0 || menu_input.compare("E") == 0) {
			Exit();
		}
		else {
			Menu();
		}
	}

	void Play() {
		clearConsole();

		std::cout << "White players name: ";
		std::string player_one_name_input;
		std::cin >> player_one_name_input;

		std::cout << "Is " << player_one_name_input << " a bot? ";
		std::string player_one_is_bot_input;
		std::cin >> player_one_is_bot_input;
		bool player_one_is_bot = false;
		if(player_one_is_bot_input.compare("yes") == 0){
			player_one_is_bot = true;
		}

		std::cout << "Black players name: ";
		std::string player_two_name_input;
		std::cin >> player_two_name_input;

		std::cout << "Is " << player_two_name_input << " a bot? ";
		std::string player_two_is_bot_input;
		std::cin >> player_two_is_bot_input;
		bool player_two_is_bot = false;
		if (player_two_is_bot_input.compare("yes") == 0) {
			player_two_is_bot = true;
		}

		GameManager* game_manager = game_manager->Instance();
		game_manager->StartGame(player_one_name_input, player_one_is_bot, player_two_name_input, player_two_is_bot);

		RuleManager* rule_manager = rule_manager->Instance();

		PieceManager* piece_manager = piece_manager->Instance();
		piece_manager->InitPieces();

		Grid* grid = new Grid();
		grid->InitGrid(piece_manager);
		grid->DrawGrid(game_manager);

		InputManager* input_manager = input_manager->Instance();
		while (!game_manager->GetGameOver()) {
			input_manager->ReadCommand(piece_manager, grid, rule_manager, game_manager);
		}
	}

	void Results() {
		clearConsole();

		std::string line;
		std::ifstream results_file("results.csv");
		if (results_file.is_open()) {
			while (std::getline(results_file, line)) {
				std::vector<std::string> results;
				std::string act_result = "";
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == ';') {
						results.push_back(act_result);
						act_result = "";
						continue;
					}
					else{
						act_result += line[i];
					}
				}
				results.push_back(act_result);

				std::cout << results[0] << " - " << results[1] << "\t" << results[2] << ":" << results[3] << '\n';
			}
		}
	}

	int Exit() {
		return 0;
	}
};

#endif MENU_MANAGER_H