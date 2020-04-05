#include<memory>
#include <Windows.h>

#include "Grid.h"
#include "PieceManager.h"

#pragma region CONSOLE_COLORS
HANDLE coloring = GetStdHandle(STD_OUTPUT_HANDLE);
int black_white = 7;
int border_color = 8;
int white_piece_color = 15;
int black_piece_color = 14;
#pragma endregion

void Grid::InitGrid(PieceManager* piece_manager) {
	this->piece_manager = piece_manager;
	grid.clear();

	std::vector<std::shared_ptr<Field>> first_row_black;

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

void Grid::DrawGrid() {
	std::system("cls");

	int i = 0;
	for (int row = 0; row < SIZE * 2 + 1; row++) {
		SetConsoleTextAttribute(coloring, border_color);
		int j = 0;
		if (row % 2 == 0) {
			for (int row_index = 0; row_index < SIZE * 2 + 1; row_index++) {
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
				std::shared_ptr<Piece> piece = piece_manager->GetPiece(std::shared_ptr<Position>(new Position(i, j)));
				if (grid[i][j]->GetColor() == Color::Black) {
					SetConsoleTextAttribute(coloring, black_piece_color);
				}
				else {
					SetConsoleTextAttribute(coloring, white_piece_color);
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
				j++;
			}
			i++;
		}
		std::cout << '\n';
	}

	SetConsoleTextAttribute(coloring, black_white);

	for (int row_index = 0; row_index < SIZE * 2 + 1; row_index++) {
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
	}

	SetConsoleTextAttribute(coloring, black_white);

	std::cout << '\n';
}

std::vector<std::vector<std::shared_ptr<Field>>> Grid::GetGrid() {
	return grid;
}