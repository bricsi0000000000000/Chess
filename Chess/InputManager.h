#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>

#include "GameManager.h"
#include "PieceManager.h"
#include "Grid.h"

GameManager* GameManager::instance = 0;

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

	void ReadCommand(PieceManager* piece_manager, Grid* grid) {

		GameManager* game_manager = game_manager->Instance();

		while (!game_manager->GetGameOver()) {
			std::cout << "\nFrom: ";
			std::string from_input;
			std::cin >> from_input;

			int column = -1 * (char('a') - int(from_input[0]));
			int row = int(from_input[1]) - '0' - 1;

			if ((column < 0 || column > 7) || (row < 0 || row > 7)) {
				std::cout << "Bad indexing.\n";
				if (column < 0 || column > 7) {
					std::cout << "Column index(" << char('a' + column) << ") must be between 'a' and 'h'\n";
				}
				if (row < 0 || row > 7) {
					std::cout << "Row index(" << row + 1 << ") must be between 1 and 8\n";
				}
				continue;
			}

			std::shared_ptr<Position> from_position(new Position(column, row));
			std::shared_ptr<Position> to_position(new Position(5, 5));
			piece_manager->GetPiece(from_position)->SetPosition(to_position);
			std::cout << column << row;

			grid->DrawGrid();
		}
	}
};

#endif INPUT_MANAGER_H