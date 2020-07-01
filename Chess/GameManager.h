#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <fstream>

#include "Player.h"

class GameManager {
private:
	GameManager() {}
	static GameManager* instance;

	bool game_over = false;

	Player* player_one;
	Player* player_two;

	int act_player = 1;

	void saveResults() {
		std::ofstream results_file("results.csv", std::ios::app);
		if (results_file.is_open()) {
			results_file << GetActPlayer()->GetName() << ";" << GetOppositePlayer()->GetName() << ";" << GetActPlayer()->GetPoints() << ";" << GetOppositePlayer()->GetPoints() << '\n';
			results_file.close();
		}
		else {
			std::cout << "Something is wrong with the results.\n";
		}
	}

public:
	static GameManager* Instance() {
		if (!instance) {
			instance = new GameManager();
		}
		return instance;
	}

	void StartGame(std::string player_one_name, bool player_one_is_bot, std::string player_two_name, bool player_two_is_bot) {
		player_one = new Player(player_one_name, Color::White, player_one_is_bot);
		player_two = new Player(player_two_name, Color::Black, player_two_is_bot);
	}

	bool GetGameOver() {
		return game_over;
	}
	void GameOver() {
		game_over = true;
		std::cout << GetActPlayer()->GetName() << " won\n";
		saveResults();
	}

	Player* GetPlayerOne() {
		return player_one;
	}

	Player* GetPlayerTwo() {
		return player_two;
	}

	Player* GetActPlayer() {
		return act_player == 1 ? player_one : player_two;
	}

	int GetActPlayerNumber() {
		return act_player;
	}

	Player* GetOppositePlayer() {
		return act_player == 2 ? player_one : player_two;
	}

	void ChangePlayer() {
		act_player = act_player == 1 ? 2 : 1;
	}
};

#endif GAME_MANAGER_H
