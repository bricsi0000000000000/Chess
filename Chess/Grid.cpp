#include <memory>
#include <Windows.h>

#include "Grid.h"
#include "PieceManager.h"

void Grid::InitGrid(PieceManager* piece_manager) {
	this->piece_manager = piece_manager;
	grid.clear();

	std::vector<std::shared_ptr<Field>> first_row_black;

	const int SIZE = 8;
	for (short row_index = 0; row_index < SIZE; row_index++) {
		std::vector<std::shared_ptr<Field>> row;
		for (short column_index = 0; column_index < SIZE; column_index++) {
			std::shared_ptr<Position> position(new Position(row_index, column_index));
			std::shared_ptr<Piece> piece = piece_manager->GetPiece(position);
			if (piece == nullptr) {
				piece = std::shared_ptr<Piece>(new Piece());
			}
			Color color = Color::White;
			if (row_index % 2 == 0) {
				if (column_index % 2 == 0) {
					color = Color::Black;
				}
			}
			else {
				if (column_index % 2 != 0) {
					color = Color::Black;
				}
			}
			row.push_back(std::shared_ptr<Field>(new Field(position, piece, color)));
		}
		grid.push_back(row);
	}
}

void Grid::DrawGrid(std::vector<std::shared_ptr<Position>> highlight_cells) {
	const char horizontal_line = (char)196;
	const char cross_line = (char)197;
	const char vertical_line = (char)179;

	const char top_right_edge = (char)191;
	const char top_left_edge = (char)218;
	const char bottom_left_edge = (char)192;
	const char bottom_right_edge = (char)217;

	const char bottom_mid = (char)193;
	const char top_mid = (char)194;
	const char right_mid = (char)180;
	const char left_mid = (char)195;

	const int SIZE = 33;
	int row_draw_index = 2;
	int i_index = 0;
	int numbers_index = 8;
	int letter_index = 0;

	for (int row_index = 0; row_index < SIZE + 1; row_index++) {
		SetConsoleTextAttribute(coloring, border_color);

		int col_draw_index = 2;
		int j_index = 0;

		for (int col_index = -3; col_index < SIZE; col_index++) {
			SetConsoleTextAttribute(coloring, border_color);

			if (col_index == -2 && row_index == row_draw_index) {
				std::cout << numbers_index--;
			}
			else if (row_index == 0 && col_index == 0) {
				std::cout << top_left_edge;
			}
			else if (row_index == 0 && col_index == SIZE - 1) {
				std::cout << top_right_edge;
			}
			else if (row_index == SIZE - 1 && col_index == 0) {
				std::cout << bottom_left_edge;
			}
			else if (row_index == SIZE - 1 && col_index == SIZE - 1) {
				std::cout << bottom_right_edge;
			}
			else if (row_index % 4 == 0) {
				if (col_index % 4 == 0) {
					if (row_index == 0) {
						std::cout << top_mid;
					}
					else if (row_index == SIZE - 1) {
						std::cout << bottom_mid;
					}
					else if (col_index == 0) {
						std::cout << left_mid;
					}
					else if (col_index == SIZE - 1) {
						std::cout << right_mid;
					}
					else {
						std::cout << cross_line;
					}
				}
				else {
					if (col_index > 0) {
						std::cout << horizontal_line;
					}
					else {
						std::cout << ' ';
					}
				}
			}
			else {
				if (col_index % 4 == 0) {
					if (row_index < SIZE) {
						std::cout << vertical_line;
					}
				}
				else {
					if (row_index == row_draw_index && col_index == col_draw_index) {
						std::shared_ptr<Piece> piece = piece_manager->GetPiece(std::shared_ptr<Position>(new Position(i_index, j_index++)));
						if (piece != nullptr) {
							if (piece->GetColor() == Color::Black) {
								SetConsoleTextAttribute(coloring, black_piece_color);
							}
							else {
								SetConsoleTextAttribute(coloring, white_piece_color);
							}

							switch (piece->GetPieceType())
							{
							case PieceType::Pawn:
								std::cout << "P";
								break;
							case PieceType::Rook:
								std::cout << "R";
								break;
							case PieceType::Bishop:
								std::cout << "B";
								break;
							case PieceType::Knight:
								std::cout << "k";
								break;
							case PieceType::Queen:
								std::cout << "Q";
								break;
							case PieceType::King:
								std::cout << "K";
								break;
							default:
								std::cout << ' ';
								break;
							}
						}
						else {
							bool highlight_cell = false;
							for (const auto& cell : highlight_cells) {
								if (cell->x == i_index && cell->y == j_index - 1) {
									SetConsoleTextAttribute(coloring, pink_color);
									std::cout << 'x';
									highlight_cell = true;
								}
							}
							if (!highlight_cell) {
								std::cout << ' ';
							}
						}

						col_draw_index += 4;
					}
					else {
						if (row_index == SIZE) {
							if (col_index >= 0 && col_draw_index == col_index) {
								std::cout << ' ' << char('a' + letter_index++);
								col_draw_index += 4;
							}
							else {
								std::cout << ' ';
							}
						}
						else {
							std::cout << ' ';
						}
					}
				}
			}
		}

		if (row_index == row_draw_index) {
			row_draw_index += 4;
			i_index++;
		}

		std::cout << '\n';
	}


	/*int grid_i_index = 0;
	for (int row = 0; row < SIZE; row++) {
		SetConsoleTextAttribute(coloring, border_color);
		int grid_j_index = 0;
		if (row % 2 == 0) {
			for (int row_index = 0; row_index < SIZE; row_index++) {
				if (row_index == 0) {
					std::cout << ' ';
					continue;
				}
				std::cout << char(196);
			}
		}
		else {
			for (int column = 0; column < SIZE * 2 + 1; column++) {
				if (column == 0) {
					std::cout << (SIZE)-(row / 2);
				}

				SetConsoleTextAttribute(coloring, border_color);
				if (column % 2 == 0) {
					std::cout << char(179);
					continue;
				}
				std::shared_ptr<Piece> piece = piece_manager->GetPiece(std::shared_ptr<Position>(new Position(grid_i_index, grid_j_index)));
				if (piece != nullptr) {
					if (piece->GetColor() == Color::Black) {
						SetConsoleTextAttribute(coloring, black_piece_color);
					}
					else {
						SetConsoleTextAttribute(coloring, white_piece_color);
					}
				}
				else{
					if (grid[grid_i_index][grid_j_index]->GetColor() == Color::Black) {
						SetConsoleTextAttribute(coloring, black_piece_color);
					}
					else {
						SetConsoleTextAttribute(coloring, white_piece_color);
					}
				}

				if (piece != nullptr) {
					switch (piece->GetPieceType())
					{
					case PieceType::Pawn:
						std::cout << "P";
						break;
					case PieceType::Rook:
						std::cout << "R";
						break;
					case PieceType::Bishop:
						std::cout << "B";
						break;
					case PieceType::Knight:
						std::cout << "k";
						break;
					case PieceType::Queen:
						std::cout << "Q";
						break;
					case PieceType::King:
						std::cout << "K";
						break;
					default:
						std::cout << " ";
						break;
					}
				}
				else {
					std::cout << " ";
				}
				grid_j_index++;
			}
			grid_i_index++;
		}
		std::cout << '\n';
	}*/

	SetConsoleTextAttribute(coloring, black_white);

	/*for (int row_index = 0; row_index < SIZE * 2 + 1; row_index++) {
		if (row_index == 0) {
			std::cout << ' ';
			continue;
		}
		if (row_index % 2 == 0) {
			std::cout << char('a' + ((row_index - 1) / 2));
		}
		else {
			std::cout << ' ';
		}
	}*/

	SetConsoleTextAttribute(coloring, black_white);

	std::cout << '\n';
}

std::vector<std::vector<std::shared_ptr<Field>>> Grid::GetGrid() {
	return grid;
}
