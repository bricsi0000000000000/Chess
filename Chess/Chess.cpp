#include <iostream>
#include <string>

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Grid.h"
#include "PieceManager.h"

PieceManager* PieceManager::instance = 0;

int main()
{
	PieceManager* piece_manager = piece_manager->Instance();
	piece_manager->InitPieces();

	Grid* grid = new Grid();
	grid->InitGrid();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << grid->GetGrid()[i][j].get()->GetPiece().get()->GetName() << ' ';
		}
		std::cout << '\n';
	}
}



