#ifndef CRID_H
#define CRID_H

#include<vector>

#include"Field.h"

class Grid
{
private:
	std::vector<std::vector<std::shared_ptr<Field>>> grid;
	const int SIZE = 8;
public:
	void InitGrid();
	std::vector<std::vector<std::shared_ptr<Field>>> GetGrid();
};

#endif CRID_H