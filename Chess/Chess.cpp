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
	RuleManager* rule_manager = rule_manager->Instance();

	PieceManager* piece_manager = piece_manager->Instance();
	piece_manager->InitPieces();

	Grid* grid = new Grid();
	grid->InitGrid(piece_manager);
	grid->DrawGrid();

	InputManager* input_manager = input_manager->Instance();
	input_manager->ReadCommand(piece_manager, grid, rule_manager);
	/*std::cout << std::endl;
	std::shared_ptr<Piece> piece = piece_manager->GetPiece(std::shared_ptr<Position>(new Position(0, 0)));
	piece_manager->MovePiece(std::shared_ptr<Position>(new Position(0, 0)), std::shared_ptr<Position>(new Position(3, 3)));
	std::cout << piece->GetPosition()->x << ' ' << piece->GetPosition()->y;
	std::cout << std::endl;
	grid->DrawGrid();*/

}



