#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>

#include "GameManager.h"
#include "PieceManager.h"
#include "RuleManager.h"
#include "Grid.h"
#include "PieceType.h"
#include "Color.h"

class InputManager
{
private:
	InputManager() {}
	static InputManager* instance;
	bool check = false;

	bool checkInput(int column, int row) {
		if ((column < 0 || column > 7) || (row < 0 || row > 7)) {
			std::cout << "Bad indexing.\n";
			if (column < 0 || column > 7) {
				std::cout << "Column index(" << char('a' + column) << ") must be between 'a' and 'h'\n";
			}
			if (row < 0 || row > 7) {
				std::cout << "Row index(" << row + 1 << ") must be between 1 and 8\n";
			}

			return false;
		}

		return true;
	}

	std::vector<std::shared_ptr<Position>> possible_steps;

	void makePossibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece){
		std::vector<std::shared_ptr<Position>> cells;

		if (piece->GetPieceType() == PieceType::Pawn) {
			if (piece->GetColor() == Color::White) {
				if (piece->GetPosition()->x == 6) {
					cells.push_back(std::shared_ptr<Position>(new Position(piece->GetPosition()->x - 2, piece->GetPosition()->y)));
				}
				cells.push_back(std::shared_ptr<Position>(new Position(piece->GetPosition()->x - 1, piece->GetPosition()->y)));
			}
			else if (piece->GetColor() == Color::Black) {
				if (piece->GetPosition()->x == 1) {
					cells.push_back(std::shared_ptr<Position>(new Position(piece->GetPosition()->x + 2, piece->GetPosition()->y)));
				}
				cells.push_back(std::shared_ptr<Position>(new Position(piece->GetPosition()->x + 1, piece->GetPosition()->y)));
			}
		}
		else {
			for (const auto& row : grid->GetGrid()) {
				for (const auto& cell : row) {
					if (rule_manager->CanStep(piece, cell->GetPosition(), piece_manager)) {
						cells.push_back(cell->GetPosition());
					}
				}
			}
		}

		possible_steps = cells;
	}

	bool isPositionInPossibleSteps(std::shared_ptr<Position> position) {
		for (const auto& possible_step : possible_steps) {
			if (position->x == possible_step->x && position->y == possible_step->y) {
				return true;
			}
		}

		return false;
	}

	void checkCheck(Grid* grid, std::shared_ptr<Piece> piece) {
		for (const auto& row : grid->GetGrid()) {
			for (const auto& cell : row) {
				if (isPositionInPossibleSteps(cell->GetPosition()) && cell->GetPiece()->GetPieceType() == PieceType::King) {
					check = true;
					return;
				}
			}
		}

		check = false;
	}

public:
	static InputManager* Instance() {
		if (!instance) {
			instance = new InputManager();
		}
		return instance;
	}

	void ReadCommand(PieceManager* piece_manager, Grid* grid, RuleManager* rule_manager, GameManager* game_manager) {
		//std::cout << "Hint: column row (a1)\n";
		if (check) {
			std::cout << "It's check! You have to protect your king!\n";
		}
		std::cout << "From: ";
		std::string from_input;
		std::cin >> from_input;

		int from_column = -1 * (char('a') - int(from_input[0]));
		int from_row = int(from_input[1]) - '0' - 1;

		if (!checkInput(from_column, from_row)) {
			return;
		}

		std::shared_ptr<Position> from_position(new Position(7 - from_row, from_column));
		std::shared_ptr<Piece> from_piece = piece_manager->GetPiece(from_position);

		if (from_piece != nullptr) {
			if (from_piece->GetColor() != game_manager->GetActPlayer()->GetColor()) {
				std::cout << "that isn't your piece\n";
				return;
			}
		}
		else {
			std::cout << "no piece is on position(" << from_position->x << ';' << from_position->y << ")\n";
			return;
		}

		makePossibleSteps(grid, piece_manager, rule_manager, from_piece);
		grid->DrawGrid(possible_steps);

		std::cout << "To: ";
		std::string to_input;
		std::cin >> to_input;

		int to_column = -1 * (char('a') - int(to_input[0]));
		int to_row = int(to_input[1]) - '0' - 1;

		if (!checkInput(to_column, to_row)) {
			return;
		}

		std::shared_ptr<Position> to_position(new Position(7 - to_row, to_column));
		std::shared_ptr<Piece> to_piece = piece_manager->GetPiece(to_position);

		bool can_step = false;

		if (to_piece == nullptr) {
			if (!piece_manager->CanMove(from_position, to_position)) {
				std::cout << "no piece is on position(" << from_position->x << ';' << from_position->y << ")\n";
			}
			else {
				if (rule_manager->CanStep(from_piece, to_position, piece_manager)) {
					if (from_piece->GetPieceType() == PieceType::Pawn) {
						if (from_position->y == to_position->y) {
							can_step = true;
						}
					}
					else {
						can_step = true;
					}
				}
				else {
					std::cout << "can't step to position(" << to_position->x << ';' << to_position->y << ")\n";
				}
			}
		}
		else {
			if (to_piece->GetColor() != from_piece->GetColor()) {
				if (from_piece->GetPieceType() == PieceType::Pawn) {
					if (from_position->y != to_position->y) {
						piece_manager->RemovePiece(to_position, game_manager);
						can_step = true;
					}
				}
				else {
					piece_manager->RemovePiece(to_position, game_manager);
					can_step = true;
				}
			}
			else {
				std::cout << "'" << to_piece->GetName() << "' is on position (" << to_position->x << ';' << to_position->y << ")\n";
			}
		}

		if (can_step) {
			if (!check) {
				piece_manager->MovePiece(from_position, to_position);
				game_manager->ChangePlayer();
				game_manager->PrintPlayerInfos();
				grid->DrawGrid();
			}
		}

		checkCheck(grid, from_piece);
		if (check) {
			std::cout << "It's check! You have to protect your king!\n";
		}
	}
};

#endif INPUT_MANAGER_H