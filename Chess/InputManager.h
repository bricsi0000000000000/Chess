#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h> 
#include <chrono>
#include <thread>

#include "GameManager.h"
#include "PieceManager.h"
#include "RuleManager.h"
#include "Grid.h"
#include "PieceType.h"
#include "Color.h"

using namespace std::this_thread;
using namespace std::chrono;

class InputManager
{
private:
	~InputManager();
	InputManager() {}
	static InputManager* instance;

	bool check = false;
	int check_mate_steps = 0;
	int bot_thinking = 0;
	bool bot_thinking_text_once = false;
	const int MAX_BOT_THINK = 25000;
	const int BOT_THINK_WRITE_BOT_THINK = 1000;
	const seconds BOT_WAIT_FOR_SEC = 1s;

	bool checkInput(int column, int row);
	bool isInPossibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece, std::shared_ptr<Position> position);
	int actPlayersPossibleStepsCount(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, GameManager* game_manager);
	bool checkCheckMate(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color, GameManager* game_manager);
	int getPieceValue(std::shared_ptr<Piece> piece);
	int exit();
	std::vector<std::shared_ptr<Position>> possibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece);
	void promotion(PieceManager* piece_manager, std::shared_ptr<Piece> piece, bool bot);
	void checkCheck(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color);
	void clearConsole();
	void play(GameManager* previous_game_manager = nullptr);
	void results();
	bool increaseBotThinking(GameManager* game_manager);
public:
	static InputManager* Instance();

	void Menu();
	void ReadCommand(PieceManager* piece_manager, Grid* grid, RuleManager* rule_manager, GameManager* game_manager);
};

#endif INPUT_MANAGER_H