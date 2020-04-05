#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>

#include "GameManager.h"
#include "PieceManager.h"
#include "RuleManager.h"
#include "Grid.h"

class InputManager
{
private:
	InputManager() {}
	static InputManager* instance;
public:
	static InputManager* Instance() {
		if (!instance) {
			instance = new InputManager();
		}
		return instance;
	}

	void ReadCommand(PieceManager* piece_manager, Grid* grid, RuleManager* rule_manager) {
		GameManager* game_manager = game_manager->Instance();

		while (!game_manager->GetGameOver()) {
			std::cout << "From: ";
			std::string from_input;
			std::cin >> from_input;

			int from_column = -1 * (char('a') - int(from_input[0]));
			int from_row = int(from_input[1]) - '0' - 1;

			if (!checkInput(from_column, from_row)) {
				continue;
			}

			std::cout << "To: ";
			std::string to_input;
			std::cin >> to_input;

			int to_column = -1 * (char('a') - int(to_input[0]));
			int to_row = int(to_input[1]) - '0' - 1;

			if (!checkInput(to_column, to_row)) {
				continue;
			}

			std::shared_ptr<Position> from_position(new Position(7 - from_row, from_column));
			std::shared_ptr<Position> to_position(new Position(7 - to_row, to_column));

			std::shared_ptr<Piece> from_piece = piece_manager->GetPiece(from_position);
			std::shared_ptr<Piece> to_piece = piece_manager->GetPiece(to_position);
			
			if (to_piece == nullptr) {
				if (!piece_manager->MovePiece(from_position, to_position)) {
					std::cout << "no piece is on position(" << 7 - from_position->x << ';' << from_position->y << ")\n";
				}
				else {
					if (rule_manager->CanStep(from_piece, to_position, piece_manager)) {
						grid->DrawGrid();
					}
					else {
						std::cout << "can't step to position(" << 7 - to_position->x << ';' << to_position->y << ")\n";
					}
				}
			}
			else {
				std::cout << "'" << to_piece->GetName() << "' is on position (" << 7 - to_position->x << ';' << to_position->y << ")\n";
			}
		}
	}

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
};

#endif INPUT_MANAGER_H