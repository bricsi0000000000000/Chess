#include <iostream>
#include <string>

#include "Grid.h"
#include "PieceManager.h"
#include "InputManager.h"

PieceManager* PieceManager::instance = 0;
InputManager* InputManager::instance = 0;

int main()
{
	PieceManager* piece_manager = piece_manager->Instance();
	piece_manager->InitPieces();

	Grid* grid = new Grid();
	grid->InitGrid(piece_manager);
	grid->DrawGrid();

	InputManager* input_manager = input_manager->Instance();
	input_manager->ReadCommand(piece_manager, grid);
}



