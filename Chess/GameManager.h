#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <Windows.h>

#include "Player.h"

class GameManager {
private:

#pragma region CONSOLE_COLORS
	HANDLE coloring = GetStdHandle(STD_OUTPUT_HANDLE);
	int white_piece_color = 15;
	int black_piece_color = 14;
	int black_white = 7;
#pragma endregion

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

		PrintPlayerInfos();
	}

	bool GetGameOver() {
		return game_over;
	}
	void GameOver() {
		game_over = true;
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

	Player* GetOppositePlayer() {
		return act_player == 2 ? player_one : player_two;
	}

	void ChangePlayer() {
		act_player = act_player == 1 ? 2 : 1;
	}

	void PrintPlayerInfos() {
		//std::system("cls");

		SetConsoleTextAttribute(coloring, player_one->GetColor() == Color::White ? white_piece_color : black_piece_color);
		std::cout << (act_player == 1 ? '*' : ' ') << player_one->GetName() << "\tPoints: " << player_one->GetPoints() << "\tOff pieces: ";
		for (int i = 0; i < player_one->GetOffPieces().size(); i++) {
			std::cout << player_one->GetOffPieces()[i]->GetName() << (i + 1 >= player_one->GetOffPieces().size() ? "" : ", ");
		}
		std::cout << '\n';

		SetConsoleTextAttribute(coloring, player_two->GetColor() == Color::White ? white_piece_color : black_piece_color);
		std::cout << (act_player == 2 ? '*' : ' ') << player_two->GetName() << "\tPoints: " << player_two->GetPoints() << "\tOff pieces: ";
		for (int i = 0; i < player_two->GetOffPieces().size(); i++) {
			std::cout << player_two->GetOffPieces()[i]->GetName() << (i + 1 >= player_two->GetOffPieces().size() ? "" : ", ");
		}
		std::cout << '\n';

		SetConsoleTextAttribute(coloring, black_white);
	}
};

#endif GAME_MANAGER_H
