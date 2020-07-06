#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <fstream>
#include <sstream>

#include "Player.h"

class GameManager {
private:
	~GameManager();
	GameManager() {}
	static GameManager* instance;

	bool game_over = false;

	Player* player_one;
	Player* player_two;

	int act_player = 1;

	std::stringstream all_steps;

	void saveResults();
	void saveAllSteps();
public:
	static GameManager* Instance();

	void ReStartGame();
	void StartGame(std::string player_one_name, bool player_one_is_bot, std::string player_two_name, bool player_two_is_bot);
	bool GetGameOver();
	void GameOver(bool opposite_player = false);
	void GiveUp();
	Player* GetPlayerOne();
	Player* GetPlayerTwo();
	Player* GetActPlayer();
	int GetActPlayerNumber();
	Player* GetOppositePlayer();
	void ChangePlayer();
	void AddStepToAllSteps();
};

#endif GAME_MANAGER_H
