#include <memory>

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

void Grid::setConsoleColor(std::string color_name) {
	if (color_name.compare("black_white") == 0) {
#ifdef _WIN32
		SetConsoleTextAttribute(coloring, black_white);
#endif
#ifdef linux
		std::cout << "\033[0;37m";
#endif
	}
	else if (color_name.compare("border_color") == 0) {
#ifdef _WIN32
		SetConsoleTextAttribute(coloring, border_color);
#endif
#ifdef linux
		std::cout << "\033[0;30m";
#endif
	}
	else if (color_name.compare("white_piece_color") == 0) {
#ifdef _WIN32
		SetConsoleTextAttribute(coloring, white_piece_color);
#endif
#ifdef linux
		std::cout << "\033[0;37m";
#endif
	}
	else if (color_name.compare("black_piece_color") == 0) {
#ifdef _WIN32
		SetConsoleTextAttribute(coloring, black_piece_color);
#endif
#ifdef linux
		std::cout << "\033[0;33m";
#endif
	}
	else if (color_name.compare("pink_color") == 0) {
#ifdef _WIN32
		SetConsoleTextAttribute(coloring, pink_color);
#endif
#ifdef linux
		std::cout << "\033[0;35m";
#endif
	}
}

void Grid::clearConsole() {
#ifdef _WIN32
	std::system("cls");
#endif
#ifdef linux
	std::system("clear");
#endif
}

void Grid::DrawGrid(GameManager* game_manager, std::vector<std::shared_ptr<Position>> highlight_cells) {
	//clearConsole();
	setConsoleColor("black_white");

	const int SIZE = 33;
	int row_draw_index = 2;
	int i_index = 0;
	int numbers_index = 8;
	int letter_index = 0;

	for (int row_index = 0; row_index < SIZE + 1; row_index++) {
		setConsoleColor("border_color");

		int col_draw_index = 2;
		int j_index = 0;

		for (int col_index = -3; col_index < SIZE; col_index++) {
			setConsoleColor("border_color");

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

						bool already_highlighted = false;
						if (piece != nullptr) {
							if (piece->GetColor() == Color::Black) {
								setConsoleColor("black_piece_color");
							}
							else {
								setConsoleColor("white_piece_color");
							}

							for (const auto& cell : highlight_cells) {
								if (cell->x == i_index && cell->y == j_index - 1) {
									setConsoleColor("pink_color");

									already_highlighted = true;
								}
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
							if (!already_highlighted) {
								for (const auto& cell : highlight_cells) {
									if (cell->x == i_index && cell->y == j_index - 1) {
										setConsoleColor("pink_color");
										std::cout << 'x';
										highlight_cell = true;
									}
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

#ifdef linux
			std::cout << "\033[0m";
#endif

		}

		if (row_index == row_draw_index) {
			row_draw_index += 4;
			i_index++;
		}

		if (row_index == 1) {
			setConsoleColor("white_piece_color");
			std::cout << (game_manager->GetActPlayerNumber() == 1 ? '*' : ' ') << game_manager->GetPlayerOne()->GetName() << "\tPoints: " << game_manager->GetPlayerOne()->GetPoints();
		}
		if (row_index == 2) {
			setConsoleColor("white_piece_color");
			std::cout << "\t\tKnocked pieces: ";
			for (int i = 0; i < game_manager->GetPlayerOne()->GetOffPieces().size(); i++) {
				writePieceNameInitials(game_manager->GetPlayerOne()->GetOffPieces()[i]);
			}
		}


		if (row_index == 3) {
			setConsoleColor("black_piece_color");
			std::cout << (game_manager->GetActPlayerNumber() == 2 ? '*' : ' ') << game_manager->GetPlayerTwo()->GetName() << "\tPoints: " << game_manager->GetPlayerTwo()->GetPoints();
		}
		if (row_index == 4) {
			setConsoleColor("black_piece_color");
			std::cout << "\t\tKnocked pieces: ";
			for (int i = 0; i < game_manager->GetPlayerTwo()->GetOffPieces().size(); i++) {
				writePieceNameInitials(game_manager->GetPlayerTwo()->GetOffPieces()[i]);
			}
		}

		if (row_index == 5) {
			if (game_manager->GetPlayerOne()->GetStepPiece() != nullptr) {
				setConsoleColor("white_piece_color");
				std::cout << game_manager->GetPlayerOne()->GetName() << " stepped with ";
				writePieceNameInitials(game_manager->GetPlayerOne()->GetStepPiece());
				std::cout << " from " << game_manager->GetPlayerOne()->GetStepFrom() << " to " << game_manager->GetPlayerOne()->GetStepTo();
			}
		}
		if (row_index == 6) {
			if (game_manager->GetPlayerTwo()->GetStepPiece() != nullptr) {
				setConsoleColor("black_piece_color");
				std::cout << game_manager->GetPlayerTwo()->GetName() << " stepped with ";
				writePieceNameInitials(game_manager->GetPlayerTwo()->GetStepPiece());
				std::cout << " from " << game_manager->GetPlayerTwo()->GetStepFrom() << " to " << game_manager->GetPlayerTwo()->GetStepTo();
			}
		}

		std::cout << '\n';
	}

	setConsoleColor("black_white");

	std::cout << '\n';
}

std::vector<std::vector<std::shared_ptr<Field>>> Grid::GetGrid() {
	return grid;
}

void Grid::writePieceNameInitials(std::shared_ptr<Piece> piece) {
	switch (piece->GetPieceType())
	{
	case PieceType::Pawn:
		std::cout << "P";
		break;
	case PieceType::Bishop:
		std::cout << "B";
		break;
	case PieceType::King:
		std::cout << "K";
		break;
	case PieceType::Knight:
		std::cout << "k";
		break;
	case PieceType::Queen:
		std::cout << "Q";
		break;
	case PieceType::Rook:
		std::cout << "R";
		break;
	default:
		break;
	}
}

