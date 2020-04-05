#ifndef CRID_H
#define CRID_H

#include<vector>

#include"Field.h"
#include "PieceManager.h"

class Grid
{
private:
	std::vector<std::vector<std::shared_ptr<Field>>> grid;
	const int SIZE = 8;
	PieceManager* piece_manager;
public:
	void InitGrid(PieceManager* piece_manager);
	void DrawGrid();
	std::vector<std::vector<std::shared_ptr<Field>>> GetGrid();
};

#endif CRID_H