#include <iostream>
#include <string>

#include "Grid.h"
#include "PieceManager.h"
#include "InputManager.h"
#include "RuleManager.h"

PieceManager* PieceManager::instance = 0;
InputManager* InputManager::instance = 0;
GameManager* GameManager::instance = 0;
RuleManager* RuleManager::instance = 0;

int main()
{
	//std::cout << "\033[1;31mbold red text\033[0m\n";
	GameManager* game_manager = game_manager->Instance();
	game_manager->StartGame("Jani", "Pista", 0);

	RuleManager* rule_manager = rule_manager->Instance();

	PieceManager* piece_manager = piece_manager->Instance();
	piece_manager->InitPieces();

	Grid* grid = new Grid();
	grid->InitGrid(piece_manager);
	grid->DrawGrid(game_manager);

	InputManager* input_manager = input_manager->Instance();
	//input_manager->InitAllStepsCount(Color::Black, grid, piece_manager, rule_manager);
	while (!game_manager->GetGameOver()) {
		input_manager->ReadCommand(piece_manager, grid, rule_manager, game_manager);
	}
	/*std::cout << std::endl;
	std::shared_ptr<Piece> piece = piece_manager->GetPiece(std::shared_ptr<Position>(new Position(0, 0)));
	piece_manager->MovePiece(std::shared_ptr<Position>(new Position(0, 0)), std::shared_ptr<Position>(new Position(3, 3)));
	std::cout << piece->GetPosition()->x << ' ' << piece->GetPosition()->y;
	std::cout << std::endl;
	grid->DrawGrid();*/

}



