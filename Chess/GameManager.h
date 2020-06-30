#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Player.h"

class GameManager {
private:
	GameManager() {}
	static GameManager* instance;

	bool game_over = false;

	Player* player_one;
	Player* player_two;

	int act_player = 1;

public:
	static GameManager* Instance() {
		if (!instance) {
			instance = new GameManager();
		}
		return instance;
	}

	void StartGame(std::string player_one_name, std::string player_two_name, int start_player = 0) {
		player_one = new Player(player_one_name, start_player == 0 ? Color::White : Color::Black);
		player_two = new Player(player_two_name, start_player == 0 ? Color::Black : Color::White);
	}

	bool GetGameOver() {
		return game_over;
	}
	void GameOver() {
		game_over = true;
		std::cout << GetActPlayer()->GetName() << " won\n";
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
