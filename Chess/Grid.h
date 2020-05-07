#ifndef CRID_H
#define CRID_H

#include<vector>

#include "Field.h"
#include "Position.h"
#include "PieceManager.h"

class Grid
{
private:
	std::vector<std::vector<std::shared_ptr<Field>>> grid;
	PieceManager* piece_manager;

#pragma region CONSOLE_COLORS
	HANDLE coloring = GetStdHandle(STD_OUTPUT_HANDLE);
	int black_white = 7;
	int border_color = 8;
	int white_piece_color = 15;
	int black_piece_color = 14;
	int pink_color = 13;
#pragma endregion
public:
	void InitGrid(PieceManager* piece_manager);
	void DrawGrid(std::vector<std::shared_ptr<Position>> highlight_cells = {});
	std::vector<std::vector<std::shared_ptr<Field>>> GetGrid();
};

#endif CRID_H