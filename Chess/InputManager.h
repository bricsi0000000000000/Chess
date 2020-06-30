#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 

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
	int check_check_mate_steps = 0;

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

	int actPlayersPossibleStepsCount(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, GameManager* game_manager) {
		int possible_steps_count = 0;
		for (const auto& piece : piece_manager->GetPieces()) {
			if (piece->GetColor() == game_manager->GetActPlayer()->GetColor()) {
				possible_steps_count += possibleSteps(grid, piece_manager, rule_manager, piece).size();
			}
		}

		return possible_steps_count;
	}

	std::vector<std::shared_ptr<Position>> possibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece) {
		std::vector<std::shared_ptr<Position>> cells;

		if (piece->GetPieceType() == PieceType::Pawn) {
			if (piece->GetColor() == Color::White) {
				bool add = true;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x - 1) {
							add = false;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x - 1, piece->GetPosition()->y));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::White) {
						cells.push_back(add_position);
					}
				}
				add = false;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y - 1) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x - 1) {
							add = true;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x - 1, piece->GetPosition()->y - 1));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::White) {
						cells.push_back(add_position);
					}
				}
				add = false;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y + 1) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x - 1) {
							add = true;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x - 1, piece->GetPosition()->y + 1));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::White) {
						cells.push_back(add_position);
					}
				}

				if (piece->GetPosition()->x == 6) {
					bool add = true;
					for (const auto& act_piece : piece_manager->GetPieces()) {
						if (act_piece->GetPosition()->y == piece->GetPosition()->y) {
							if (act_piece->GetPosition()->x == piece->GetPosition()->x - 2) {
								add = false;
							}
						}
					}
					if (add) {
						std::shared_ptr<Position> check_position(new Position(piece->GetPosition()->x - 1, piece->GetPosition()->y));
						if (piece_manager->GetPiece(check_position) == nullptr) {
							std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x - 2, piece->GetPosition()->y));
							if (piece_manager->GetPiece(add_position) == nullptr) {
								cells.push_back(add_position);
							}
							else if (piece_manager->GetPiece(add_position)->GetColor() != Color::White) {
								cells.push_back(add_position);
							}
						}
					}
				}
			}
			else if (piece->GetColor() == Color::Black) {
				bool add = true;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x + 1) {
							add = false;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x + 1, piece->GetPosition()->y));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::Black) {
						cells.push_back(add_position);
					}
				}
				add = false;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y - 1) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x + 1) {
							add = true;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x + 1, piece->GetPosition()->y - 1));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::Black) {
						cells.push_back(add_position);
					}
				}
				add = false;
				for (const auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == piece->GetPosition()->y + 1) {
						if (act_piece->GetPosition()->x == piece->GetPosition()->x + 1) {
							add = true;
						}
					}
				}
				if (add) {
					std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x + 1, piece->GetPosition()->y + 1));
					if (piece_manager->GetPiece(add_position) == nullptr) {
						cells.push_back(add_position);
					}
					else if (piece_manager->GetPiece(add_position)->GetColor() != Color::Black) {
						cells.push_back(add_position);
					}
				}


				if (piece->GetPosition()->x == 1) {
					bool add = true;
					for (const auto& act_piece : piece_manager->GetPieces()) {
						if (act_piece->GetPosition()->y == piece->GetPosition()->y) {
							if (act_piece->GetPosition()->x == piece->GetPosition()->x + 2) {
								add = false;
							}
						}
					}
					if (add) {
						std::shared_ptr<Position> check_position(new Position(piece->GetPosition()->x + 1, piece->GetPosition()->y));
						if (piece_manager->GetPiece(check_position) == nullptr) {
							std::shared_ptr<Position> add_position(new Position(piece->GetPosition()->x + 2, piece->GetPosition()->y));
							if (piece_manager->GetPiece(add_position) == nullptr) {
								cells.push_back(add_position);
							}
							else if (piece_manager->GetPiece(add_position)->GetColor() != Color::Black) {
								cells.push_back(add_position);
							}
						}
					}
				}
			}
		}
		else {
			for (const auto& row : grid->GetGrid()) {
				for (const auto& cell : row) {
					std::shared_ptr<Piece> act_piece = piece_manager->GetPiece(cell->GetPosition());
					if (act_piece == nullptr) {
						if (rule_manager->CanStep(piece, cell->GetPosition(), piece_manager)) {
							cells.push_back(cell->GetPosition());
						}
					}
					else {
						if (act_piece->GetColor() != piece->GetColor()) {
							if (rule_manager->CanStep(piece, cell->GetPosition(), piece_manager)) {
								cells.push_back(cell->GetPosition());
							}
						}
					}
				}
			}
		}

		return cells;
	}

	bool isInPossibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece, std::shared_ptr<Position> position) {
		for (const auto& step : possibleSteps(grid, piece_manager, rule_manager, piece)) {
			if (step->x == position->x && step->y == position->y) {
				return true;
			}
		}

		return false;
	}

	int checkCheckMate(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color, GameManager* game_manager) {
		int all_possible_step = 0;

		for (const auto& piece : piece_manager->GetPieces()) {
			if (piece->GetColor() == color) {
				bool is_alive = true;
				for (const auto& off_piece : game_manager->GetPlayerTwo()->GetOffPieces()) {
					if (piece->GetName() == off_piece->GetName()) {
						is_alive = false;
					}
				}
				if (is_alive) {
					all_possible_step += possibleSteps(grid, piece_manager, rule_manager, piece).size();
				}
			}
		}

		return all_possible_step;
	}

	void checkCheck(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color) {
		for (const auto& act_piece : piece_manager->GetPieces()) {
			if (act_piece->GetColor() != color) {
				if (act_piece->GetPieceType() == PieceType::Pawn) {
					if (act_piece->GetPosition()->y != piece_manager->GetKing(color)->GetPosition()->y) {
						if (isInPossibleSteps(grid, piece_manager, rule_manager, act_piece, piece_manager->GetKing(color)->GetPosition())) {
							check = true;
							return;
						}
					}
				}
				else {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, act_piece, piece_manager->GetKing(color)->GetPosition())) {
						check = true;
						return;
					}
				}
			}
		}

		check = false;
	}

	void promotion(PieceManager* piece_manager, std::shared_ptr<Piece> piece, bool bot) {
		if (bot) {
			piece_manager->ChangePiece(piece, "queen promoted " + std::to_string(piece_manager->GetPieceCount(PieceType::Queen, piece->GetColor())), PieceType::Queen);
		}
		else {
			std::cout << "\nYou have a chance to promote your pawn.\nWhat do you want to replace it with? (Q), (B), (k), (R), (P)\n";
			std::string input = "";
			std::cin >> input;

			std::string new_name = "";
			PieceType new_type = PieceType::Nothing;
			if (input.compare("Q") == 0) {
				new_type = PieceType::Queen;
				new_name = "queen promoted " + std::to_string(piece_manager->GetPieceCount(new_type, piece->GetColor()));
			}
			else if (input.compare("B") == 0) {
				new_type = PieceType::Bishop;
				new_name = "bishop promoted " + std::to_string(piece_manager->GetPieceCount(new_type, piece->GetColor()));
			}
			else if (input.compare("k") == 0) {
				new_type = PieceType::Knight;
				new_name = "knight promoted " + std::to_string(piece_manager->GetPieceCount(new_type, piece->GetColor()));
			}
			else if (input.compare("R") == 0) {
				new_type = PieceType::Rook;
				new_name = "rook promoted " + std::to_string(piece_manager->GetPieceCount(new_type, piece->GetColor()));
			}
			else if (input.compare("P") == 0) {
				new_type = PieceType::Pawn;
				new_name = "pawn promoted " + std::to_string(piece_manager->GetPieceCount(new_type, piece->GetColor()));
			}
			else {
				promotion(piece_manager, piece, bot);
			}

			piece_manager->ChangePiece(piece, new_name, new_type);
		}
	}

public:
	static InputManager* Instance() {
		if (!instance) {
			instance = new InputManager();
			srand(time(NULL));
		}
		return instance;
	}

	int getPieceValue(std::shared_ptr<Piece> piece) {
		switch (piece->GetPieceType())
		{
		case PieceType::Pawn:
			return 1;
			break;
		case PieceType::Knight:
			return 2;
			break;
		case PieceType::Bishop:
			return 3;
			break;
		case PieceType::Rook:
			return 4;
			break;
		case PieceType::Queen:
			return 5;
			break;
		case PieceType::King:
			return 6;
			break;
		default:
			return 0;
			break;
		}
	}

	void ReadCommand(PieceManager* piece_manager, Grid* grid, RuleManager* rule_manager, GameManager* game_manager) {
		//std::cout << "Hint: column row (a1)\n";
		if (game_manager->GetActPlayer()->GetColor() == Color::Black) {

			if (check_check_mate_steps > checkCheckMate(grid, piece_manager, rule_manager, Color::Black, game_manager)) {
				std::cout << "Check mate\n";
				game_manager->GameOver();
			}

			std::shared_ptr<Position> from_position = nullptr;
			std::shared_ptr<Position> to_position = nullptr;
			std::shared_ptr<Piece> from_piece = nullptr;
			std::shared_ptr<Piece> to_piece = nullptr;
			int best_value = -1;

			for (const auto piece : piece_manager->GetPieces()) {
				if (piece->GetColor() == Color::Black) {
					for (const auto step : possibleSteps(grid, piece_manager, rule_manager, piece)) {
						int current_value = 0;

						from_piece = piece_manager->GetPiece(piece->GetPosition());
						to_piece = piece_manager->GetPiece(step);

						bool can_step = false;
						bool remove_piece = false;
						if (to_piece == nullptr) {
							if (!piece_manager->CanMove(from_piece->GetPosition(), step)) {
								continue;
							}
							else {
								if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, step)) {
									if (from_piece->GetPieceType() == PieceType::Pawn) {
										if (from_piece->GetPosition()->y == step->y) {
											can_step = true;
										}
										else {
											continue;
										}
									}
									else {
										can_step = true;
									}
								}
								else {
									continue;
								}
							}
						}
						else {
							if (to_piece->GetColor() != from_piece->GetColor()) {
								if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, step)) {
									if (from_piece->GetPieceType() == PieceType::Pawn) {
										if (from_piece->GetPosition()->y != step->y) {
											remove_piece = true;
											can_step = true;
										}
										else {
											continue;
										}
									}
									else {
										remove_piece = true;
										can_step = true;
									}
								}
								else {
									continue;
								}
							}
							else {
								continue;
							}
						}

						if (can_step) {
							if (remove_piece) {
								current_value += getPieceValue(to_piece);
							}
						}

						if (current_value > best_value) {
							best_value = current_value;
							from_position = piece->GetPosition();
							to_position = step;
						}
					}
				}
			}

			if (best_value == 0) {
				from_piece = piece_manager->GetPieces()[rand() % piece_manager->GetPieces().size()];

				if (from_piece->GetColor() != Color::Black) {
					return;
				}

				std::vector<std::shared_ptr<Position>> steps = possibleSteps(grid, piece_manager, rule_manager, from_piece);

				if (steps.size() <= 0) {
					return;
				}

				to_position = steps[rand() % steps.size()];
				to_piece = piece_manager->GetPiece(to_position);
			}
			else
			{
				from_piece = piece_manager->GetPiece(from_position);
				to_piece = piece_manager->GetPiece(to_position);
			}
		
			bool can_step = false;
			bool remove_piece = false;
			if (to_piece == nullptr) {
				if (!piece_manager->CanMove(from_piece->GetPosition(), to_position)) {
					return;
				}
				else {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, to_position)) {
						if (from_piece->GetPieceType() == PieceType::Pawn) {
							if (from_piece->GetPosition()->y == to_position->y) {
								can_step = true;
							}
							else {
								return;
							}
						}
						else {
							can_step = true;
						}
					}
					else {
						return;
					}
				}
			}
			else {
				if (to_piece->GetColor() != from_piece->GetColor()) {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, to_position)) {
						if (from_piece->GetPieceType() == PieceType::Pawn) {
							if (from_piece->GetPosition()->y != to_position->y) {
								remove_piece = true;
								can_step = true;
							}
							else {
								return;
							}
						}
						else {
							remove_piece = true;
							can_step = true;
						}
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}

			if (can_step) {
				if (remove_piece) {
					piece_manager->RemovePiece(to_position, game_manager);
				}
				std::shared_ptr<Position> prev_position = from_piece->GetPosition();
				piece_manager->MovePiece(from_piece->GetPosition(), to_position);
				check = false;
				checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());
				if (check) {
					piece_manager->MovePiece(to_position, prev_position);
					if (remove_piece) {
						piece_manager->RevivePiece(to_piece, game_manager);
					}
					//std::cout << "Can't step, because you are in check!\n";
					check_check_mate_steps++;
					return;
				}
				else {
					checkCheck(grid, piece_manager, rule_manager, game_manager->GetOppositePlayer()->GetColor());
					std::cout << "Bot step: |" << from_piece->GetName() << "| (" << prev_position->x << ';' << prev_position->y << ") -> (" << to_position->x << ';' << to_position->y << ")\n";

					check_check_mate_steps = 0;

					game_manager->ChangePlayer();
				}
			}


			if (from_piece->GetPieceType() == PieceType::Pawn) {
				if (from_piece->GetColor() == Color::White) {
					if (from_piece->GetPosition()->x == 0) {
						promotion(piece_manager, from_piece, true);
					}
				}
				else if (from_piece->GetColor() == Color::Black) {
					if (from_piece->GetPosition()->x == 7) {
						promotion(piece_manager, from_piece, true);
					}
				}
			}
		}
		else {
			if (check) {
				std::cout << "It's check! Protect your king!\n";
			}

			std::cout << "Select piece: ";
			std::string from_input;
			std::cin >> from_input;

			int from_column = -1 * (char('a') - int(from_input[0]));
			int from_row = int(from_input[1]) - '0' - 1;

			if (!checkInput(from_column, from_row)) {
				grid->DrawGrid(game_manager);
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

			grid->DrawGrid(game_manager, possibleSteps(grid, piece_manager, rule_manager, from_piece));

			std::cout << "Step: ";
			std::string to_input;
			std::cin >> to_input;

			int to_column = -1 * (char('a') - int(to_input[0]));
			int to_row = int(to_input[1]) - '0' - 1;

			if (!checkInput(to_column, to_row)) {
				grid->DrawGrid(game_manager);
				return;
			}

			std::shared_ptr<Position> to_position(new Position(7 - to_row, to_column));
			std::shared_ptr<Piece> to_piece = piece_manager->GetPiece(to_position);

			bool can_step = false;
			bool remove_piece = false;
			if (to_piece == nullptr) {
				if (!piece_manager->CanMove(from_position, to_position)) {
					std::cout << "no piece is on position(" << from_position->x << ';' << from_position->y << ")\n";
				}
				else {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, to_position)) {
						if (from_piece->GetPieceType() == PieceType::Pawn) {
							if (from_position->y == to_position->y) {
								can_step = true;
							}
							else {
								std::cout << "You can't step to position (" << to_position->x << ';' << to_position->y << ")\n";
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
					if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, to_position)) {
						if (from_piece->GetPieceType() == PieceType::Pawn) {
							if (from_position->y != to_position->y) {
								remove_piece = true;
								can_step = true;
							}
							else {
								std::cout << "You can't step to position (" << to_position->x << ';' << to_position->y << ")\n";
							}
						}
						else {
							remove_piece = true;
							can_step = true;
						}
					}
					else {
						std::cout << "You can't step to position (" << to_position->x << ';' << to_position->y << ")\n";
					}
				}
				else {
					std::cout << "'" << to_piece->GetName() << "' is on position (" << to_position->x << ';' << to_position->y << ")\n";
				}
			}

			if (can_step) {
				if (remove_piece) {
					piece_manager->RemovePiece(to_position, game_manager);
				}
				piece_manager->MovePiece(from_position, to_position);
				check = false;
				checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());
				if (check) {
					piece_manager->MovePiece(to_position, from_position);
					if (remove_piece) {
						piece_manager->RevivePiece(to_piece, game_manager);
					}
					std::cout << "Can't step, because you are in check!\n";
				}
				else {
					checkCheck(grid, piece_manager, rule_manager, game_manager->GetOppositePlayer()->GetColor());
					game_manager->ChangePlayer();
				}
			}

			if (from_piece->GetPieceType() == PieceType::Pawn) {
				if (from_piece->GetColor() == Color::White) {
					if (from_piece->GetPosition()->x == 0) {
						promotion(piece_manager, from_piece, false);
					}
				}
				else if (from_piece->GetColor() == Color::Black) {
					if (from_piece->GetPosition()->x == 7) {
						promotion(piece_manager, from_piece, false);
					}
				}
			}
		}
		grid->DrawGrid(game_manager);
	}
};

#endif INPUT_MANAGER_H