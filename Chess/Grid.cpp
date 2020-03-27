#include<memory>

#include "Grid.h"

void Grid::InitGrid() {
	grid.clear();

	std::vector<std::shared_ptr<Field>> first_row_black;

	for (short row_index = 0; row_index < SIZE; row_index++) {
		std::vector<std::shared_ptr<Field>> row;
		for (short column_index = 0; column_index < SIZE; column_index++) {
			row.push_back(std::shared_ptr<Field>(new Field(new Position(1, 2), new Piece(), Color::Black)));
		}
		grid.push_back(row);
	}
}

std::vector<std::vector<std::shared_ptr<Field>>> Grid::GetGrid() {
	return grid;
}