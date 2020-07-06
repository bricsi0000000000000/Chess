#include "InputManager.h"

GameManager* GameManager::instance = 0;
RuleManager* RuleManager::instance = 0;
PieceManager* PieceManager::instance = 0;

InputManager::~InputManager() {
	delete this;
}

InputManager* InputManager::Instance() {
	if (!instance) {
		instance = new InputManager();
		srand(time(NULL));
	}
	return instance;
}

bool InputManager::checkInput(int column, int row) {
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

int InputManager::actPlayersPossibleStepsCount(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, GameManager* game_manager) {
	int possible_steps_count = 0;
	for (const auto& piece : piece_manager->GetPieces()) {
		if (piece->GetColor() == game_manager->GetActPlayer()->GetColor()) {
			possible_steps_count += possibleSteps(grid, piece_manager, rule_manager, piece).size();
		}
	}

	return possible_steps_count;
}

std::vector<std::shared_ptr<Position>> InputManager::possibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece) {
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

bool InputManager::isInPossibleSteps(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, std::shared_ptr<Piece> piece, std::shared_ptr<Position> position) {
	for (const auto& step : possibleSteps(grid, piece_manager, rule_manager, piece)) {
		if (step->x == position->x && step->y == position->y) {
			return true;
		}
	}

	return false;
}

bool InputManager::checkCheckMate(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color, GameManager* game_manager) {
	for (const auto& act_piece : piece_manager->GetPieces()) {
		if (act_piece->GetColor() == game_manager->GetActPlayer()->GetColor()) {
			for (const auto& step : possibleSteps(grid, piece_manager, rule_manager, act_piece)) {
				std::shared_ptr<Position> prev_position = act_piece->GetPosition();
				std::shared_ptr<Piece> to_piece = piece_manager->GetPiece(step);
				if (to_piece != nullptr) {
					piece_manager->RemovePiece(step, game_manager);
				}
				piece_manager->MovePiece(act_piece->GetPosition(), step);

				checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());

				piece_manager->MovePiece(step, prev_position);
				if (to_piece != nullptr) {
					piece_manager->RevivePiece(to_piece, game_manager);
				}

				if (!check) {
					return false;
				}
			}
		}
	}

	return true;
}

void InputManager::checkCheck(Grid* grid, PieceManager* piece_manager, RuleManager* rule_manager, Color color) {
	for (const auto& act_piece : piece_manager->GetPieces()) {
		if (act_piece->GetColor() != color) {
			if (act_piece->GetPieceType() == PieceType::Pawn) {
				if (act_piece->GetPosition()->y != piece_manager->GetKing(color)->GetPosition()->y) {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, act_piece, piece_manager->GetKing(color)->GetPosition())) {
						std::cout << act_piece->GetName() << '\n';
						for (auto a : possibleSteps(grid, piece_manager, rule_manager, act_piece)) {
							std::cout << a->x << ';' << a->y << '\n';
						}
						check = true;
						return;
					}
				}
			}
			else {
				if (isInPossibleSteps(grid, piece_manager, rule_manager, act_piece, piece_manager->GetKing(color)->GetPosition())) {
					std::cout << act_piece->GetName() << '\n';
					for (auto a : possibleSteps(grid, piece_manager, rule_manager, act_piece)) {
						std::cout << a->x << ';' << a->y << '\n';
					}
					check = true;
					return;
				}
			}
		}
	}

	check = false;
}

void InputManager::promotion(PieceManager* piece_manager, std::shared_ptr<Piece> piece, bool bot) {
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

int InputManager::getPieceValue(std::shared_ptr<Piece> piece) {
	if (piece == nullptr) {
		return 0;
	}
	switch (piece->GetPieceType())
	{
	case PieceType::Pawn:
		return 10;
		break;
	case PieceType::Knight:
		return 20;
		break;
	case PieceType::Bishop:
		return 30;
		break;
	case PieceType::Rook:
		return 40;
		break;
	case PieceType::Queen:
		return 50;
		break;
	case PieceType::King:
		return 60;
		break;
	default:
		return 0;
		break;
	}
}

void InputManager::ReadCommand(PieceManager* piece_manager, Grid* grid, RuleManager* rule_manager, GameManager* game_manager) {
	if (game_manager->GetActPlayer()->IsBot()) {
		sleep_until(system_clock::now() + BOT_WAIT_FOR_SEC);

		if (checkCheckMate(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor(), game_manager)) {
			std::cout << "Check mate\n";
			game_manager->GameOver(true);
			return;
		}
		if (piece_manager->GetPieceCount(game_manager->GetActPlayer()->GetColor()) == 1 && piece_manager->GetPieceCount(game_manager->GetOppositePlayer()->GetColor()) == 1) {
			std::cout << "Draw\n";
			game_manager->GameOver();
			return;
		}
	
		int can_move = 0;
		for (const auto& piece : piece_manager->GetPieces()) {
			if (piece->GetColor() == game_manager->GetActPlayer()->GetColor()) {
				if (possibleSteps(grid, piece_manager, rule_manager, piece).size() > 0) {
					can_move++;
				}
			}
		}
		if (can_move == 1) {
			game_manager->GiveUp();
			return;
		}

		std::shared_ptr<Position> from_position = nullptr;
		std::shared_ptr<Position> to_position = nullptr;
		std::shared_ptr<Piece> from_piece = nullptr;
		std::shared_ptr<Piece> to_piece = nullptr;
		int best_value = 0;
		int enemy_best_value = 0;

		std::vector<std::shared_ptr<Piece>> danger_zone;
		bool continue_without = false;
		checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());

		if (check) {
			check = false;
			std::shared_ptr<Piece> king = piece_manager->GetKing(game_manager->GetActPlayer()->GetColor());
			for (const auto& step : possibleSteps(grid, piece_manager, rule_manager, king)) {
				if (increaseBotThinking(game_manager)) { break; }

				std::shared_ptr<Position> prev_position = king->GetPosition();
				std::shared_ptr<Piece> to_piece = piece_manager->GetPiece(step);
				if (to_piece != nullptr) {
					piece_manager->RemovePiece(step, game_manager);
				}
				piece_manager->MovePiece(king->GetPosition(), step);

				checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());

				piece_manager->MovePiece(step, prev_position);
				if (to_piece != nullptr) {
					piece_manager->RevivePiece(to_piece, game_manager);
				}

				if (!check) {
					continue_without = true;
					from_piece = king;
					from_position = king->GetPosition();
					to_piece = piece_manager->GetPiece(step);
					to_position = step;
					break;
				}
			}
		}

		if (!continue_without) {
			for (const auto enemy_piece : piece_manager->GetPieces()) {
				if (enemy_piece->GetColor() == game_manager->GetOppositePlayer()->GetColor()) {
					for (const auto enemy_step : possibleSteps(grid, piece_manager, rule_manager, enemy_piece)) {
						if (increaseBotThinking(game_manager)) { break; }

						std::shared_ptr<Piece> enemy_from_piece = piece_manager->GetPiece(enemy_piece->GetPosition());
						std::shared_ptr<Piece> enemy_to_piece = piece_manager->GetPiece(enemy_step);
						bool enemy_can_step = false;
						bool enemy_remove_piece = false;

						int enemy_current_value = 0;

						if (enemy_to_piece == nullptr) {
							if (!piece_manager->CanMove(enemy_from_piece->GetPosition(), enemy_step)) {
								continue;
							}
							else {
								if (isInPossibleSteps(grid, piece_manager, rule_manager, enemy_from_piece, enemy_step)) {
									if (enemy_from_piece->GetPieceType() == PieceType::Pawn) {
										if (enemy_from_piece->GetPosition()->y == enemy_step->y) {
											enemy_can_step = true;
										}
										else {
											continue;
										}
									}
									else {
										enemy_can_step = true;
									}
								}
								else {
									continue;
								}
							}
						}
						else {
							if (enemy_to_piece->GetColor() != enemy_from_piece->GetColor()) {
								if (isInPossibleSteps(grid, piece_manager, rule_manager, enemy_from_piece, enemy_step)) {
									if (enemy_from_piece->GetPieceType() == PieceType::Pawn) {
										if (enemy_from_piece->GetPosition()->y != enemy_step->y) {
											enemy_remove_piece = true;
											enemy_can_step = true;
										}
										else {
											continue;
										}
									}
									else {
										enemy_remove_piece = true;
										enemy_can_step = true;
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

						if (enemy_can_step) {
							if (enemy_remove_piece) {
								enemy_current_value += getPieceValue(enemy_to_piece);
								danger_zone.push_back(enemy_to_piece);
							}
						}

						if (enemy_current_value > enemy_best_value) {
							enemy_best_value = enemy_current_value;
						}
					}
				}
			}

			from_position = nullptr;
			to_position = nullptr;

			for (const auto piece : piece_manager->GetPieces()) {
				if (piece->GetColor() == game_manager->GetActPlayer()->GetColor()) {
					for (const auto step : possibleSteps(grid, piece_manager, rule_manager, piece)) {
						if (increaseBotThinking(game_manager)) { break; }

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
							int to_piece_value = getPieceValue(to_piece);
							if (remove_piece) {
								current_value += to_piece_value;
								piece_manager->RemovePiece(step, game_manager);
							}
							std::shared_ptr<Position> prev_position = from_piece->GetPosition();
							piece_manager->MovePiece(from_piece->GetPosition(), step);

							for (const auto enemy_piece : piece_manager->GetPieces()) {
								if (enemy_piece->GetColor() == game_manager->GetOppositePlayer()->GetColor()) {
									for (const auto enemy_step : possibleSteps(grid, piece_manager, rule_manager, enemy_piece)) {
										if (increaseBotThinking(game_manager)) { break; }

										std::shared_ptr<Piece> enemy_from_piece = piece_manager->GetPiece(enemy_piece->GetPosition());
										std::shared_ptr<Piece> enemy_to_piece = piece_manager->GetPiece(enemy_step);
										bool enemy_can_step = false;
										bool enemy_remove_piece = false;

										if (enemy_to_piece == nullptr) {
											if (!piece_manager->CanMove(enemy_from_piece->GetPosition(), enemy_step)) {
												continue;
											}
											else {
												if (isInPossibleSteps(grid, piece_manager, rule_manager, enemy_from_piece, enemy_step)) {
													if (enemy_from_piece->GetPieceType() == PieceType::Pawn) {
														if (enemy_from_piece->GetPosition()->y == enemy_step->y) {
															enemy_can_step = true;
														}
														else {
															continue;
														}
													}
													else {
														enemy_can_step = true;
													}
												}
												else {
													continue;
												}
											}
										}
										else {
											if (enemy_to_piece->GetColor() != enemy_from_piece->GetColor()) {
												if (isInPossibleSteps(grid, piece_manager, rule_manager, enemy_from_piece, enemy_step)) {
													if (enemy_from_piece->GetPieceType() == PieceType::Pawn) {
														if (enemy_from_piece->GetPosition()->y != enemy_step->y) {
															enemy_remove_piece = true;
															enemy_can_step = true;
														}
														else {
															continue;
														}
													}
													else {
														enemy_remove_piece = true;
														enemy_can_step = true;
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

										if (enemy_can_step) {
											if (enemy_remove_piece) {
												int enemy_value = getPieceValue(enemy_to_piece);
												if (to_piece_value <= enemy_value) {
													current_value -= enemy_value;
												}
												danger_zone.push_back(enemy_to_piece);
											}
										}
									}
								}
							}

							piece_manager->MovePiece(step, prev_position);
							if (remove_piece) {
								piece_manager->RevivePiece(to_piece, game_manager);
							}
						}

						bool is_in_danger_zone = false;
						for (const auto& danger_piece : danger_zone) {
							if (danger_piece->GetName() == piece->GetName()) {
								is_in_danger_zone = true;
							}
						}
						if (is_in_danger_zone) {
							for (const auto danger_step : possibleSteps(grid, piece_manager, rule_manager, piece)) {
								if (increaseBotThinking(game_manager)) { break; }

								std::shared_ptr<Piece> danger_from_piece = piece;
								std::shared_ptr<Piece> danger_to_piece = piece_manager->GetPiece(danger_step);
								bool danger_can_step = false;
								bool danger_remove_piece = false;

								if (danger_to_piece == nullptr) {
									if (!piece_manager->CanMove(danger_from_piece->GetPosition(), danger_step)) {
										continue;
									}
									else {
										if (isInPossibleSteps(grid, piece_manager, rule_manager, danger_from_piece, danger_step)) {
											if (danger_from_piece->GetPieceType() == PieceType::Pawn) {
												if (danger_from_piece->GetPosition()->y == danger_step->y) {
													danger_can_step = true;
												}
												else {
													continue;
												}
											}
											else {
												danger_can_step = true;
											}
										}
										else {
											continue;
										}
									}
								}
								else {
									if (danger_to_piece->GetColor() != danger_from_piece->GetColor()) {
										if (isInPossibleSteps(grid, piece_manager, rule_manager, danger_from_piece, danger_step)) {
											if (danger_from_piece->GetPieceType() == PieceType::Pawn) {
												if (danger_from_piece->GetPosition()->y != danger_step->y) {
													danger_remove_piece = true;
													danger_can_step = true;
												}
												else {
													continue;
												}
											}
											else {
												danger_remove_piece = true;
												danger_can_step = true;
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

								if (danger_can_step) {
									if (danger_remove_piece) {
										int danger_value = getPieceValue(danger_to_piece);
										if (getPieceValue(danger_from_piece) < danger_value) {
											current_value += danger_value;
										}
									}

								}
							}
						}

						if (current_value > best_value) {
							if (best_value < enemy_best_value) {
								best_value = current_value;
								from_position = piece->GetPosition();
								to_position = step;
							}
						}
					}
				}
			}
			if (best_value <= 0) {
				bool step_is_good = false;
				while (!step_is_good) {
					from_piece = piece_manager->GetPieces()[rand() % piece_manager->GetPieces().size()];

					if (from_piece->GetColor() != game_manager->GetActPlayer()->GetColor()) {
						continue;
					}

					std::vector<std::shared_ptr<Position>> steps = possibleSteps(grid, piece_manager, rule_manager, from_piece);

					if (steps.size() <= 0) {
						continue;
					}
					else {
						step_is_good = true;
					}

					to_position = steps[rand() % steps.size()];
					to_piece = piece_manager->GetPiece(to_position);

					from_position = from_piece->GetPosition();
				}
			}
			else
			{
				from_piece = piece_manager->GetPiece(from_position);
				to_piece = piece_manager->GetPiece(to_position);
			}

		}

		bool can_step = false;
		bool remove_piece = false;
		if (!continue_without) {
			if (to_piece == nullptr) {
				if (!piece_manager->CanMove(from_piece->GetPosition(), to_position)) {
					if (increaseBotThinking(game_manager)) {}
				}
				else {
					if (isInPossibleSteps(grid, piece_manager, rule_manager, from_piece, to_position)) {
						if (from_piece->GetPieceType() == PieceType::Pawn) {
							if (from_piece->GetPosition()->y == to_position->y) {
								can_step = true;
							}
							else {
								if (increaseBotThinking(game_manager)) {}
							}
						}
						else {
							can_step = true;
						}
					}
					else {
						if (increaseBotThinking(game_manager)) {}
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
								increaseBotThinking(game_manager);
							}
						}
						else {
							remove_piece = true;
							can_step = true;
						}
					}
					else {
						increaseBotThinking(game_manager);
					}
				}
				else {
					increaseBotThinking(game_manager);
				}
			}
		}
		if (can_step || continue_without) {
			if (remove_piece) {
				piece_manager->RemovePiece(to_position, game_manager);
			}

			std::shared_ptr<Position> prev_position = from_piece->GetPosition();

			piece_manager->MovePiece(from_piece->GetPosition(), to_position);

			check = false;
			if (!continue_without) {
				checkCheck(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor());
			}
			if (check) {
				piece_manager->MovePiece(to_position, prev_position);
				if (remove_piece) {
					piece_manager->RevivePiece(to_piece, game_manager);
				}
				increaseBotThinking(game_manager);
				return;
			}
			else {
				checkCheck(grid, piece_manager, rule_manager, game_manager->GetOppositePlayer()->GetColor());

				std::stringstream step_from;
				step_from << (char(char('a') + (prev_position->y))) << ((prev_position->x - 8) * -1);

				std::stringstream step_to;
				step_to << (char(char('a') + (to_position->y))) << ((to_position->x - 8) * -1);

				game_manager->GetActPlayer()->SetStepFrom(step_from.str());
				game_manager->GetActPlayer()->SetStepTo(step_to.str());
				game_manager->GetActPlayer()->SetStepPiece(from_piece);

				game_manager->AddStepToAllSteps();

				bot_thinking = 0;
				bot_thinking_text_once = false;

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
		if (checkCheckMate(grid, piece_manager, rule_manager, game_manager->GetActPlayer()->GetColor(), game_manager)) {
			std::cout << "Check mate\n";
			game_manager->GameOver(true);
			return;
		}

		if (check) {
			std::cout << "It's check! Protect your king!\n";
		}

		std::cout << "Select piece: ";
		std::string from_input;
		std::cin >> from_input;

		if (from_input.compare("Restart") == 0 || from_input.compare("restart") == 0 || from_input.compare("R") == 0 || from_input.compare("r") == 0) {
			play(game_manager);
		}
		else if (from_input.compare("Menu") == 0 || from_input.compare("menu") == 0 || from_input.compare("M") == 0 || from_input.compare("m") == 0) {
			Menu();
		}
		else if (from_input.compare("Results") == 0 || from_input.compare("results") == 0 || from_input.compare("R") == 0 || from_input.compare("r") == 0) {
			results();
		}
		else if (from_input.compare("Exit") == 0 || from_input.compare("exit") == 0 || from_input.compare("E") == 0 || from_input.compare("e") == 0) {
			exit();
		}
		else if (from_input.compare("Give Up") == 0 || from_input.compare("give up") == 0 || from_input.compare("giveup") == 0 || from_input.compare("gu") == 0) {
			game_manager->GiveUp();
		}

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

				game_manager->GetActPlayer()->SetStepFrom(from_input);
				game_manager->GetActPlayer()->SetStepTo(to_input);
				game_manager->GetActPlayer()->SetStepPiece(from_piece);

				game_manager->AddStepToAllSteps();

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

void InputManager::clearConsole() {
#ifdef _WIN32
	std::system("cls");
#endif
#ifdef linux
	std::system("clear");
#endif
}

void InputManager::Menu() {
	clearConsole();

	std::cout << "    C H E S S\n\n";
	std::cout << "     |Menu|\n\n";
	std::cout << "      Play(p)\n";
	std::cout << "    Results(r)\n";
	std::cout << "      Exit(e)\n\n";
	std::cout << "Select: ";

	std::string menu_input;
	std::cin >> menu_input;

	if (menu_input.compare("Play") == 0 || menu_input.compare("play") == 0 || menu_input.compare("p") == 0 || menu_input.compare("P") == 0) {
		play();
	}
	else if (menu_input.compare("Results") == 0 || menu_input.compare("results") == 0 || menu_input.compare("r") == 0 || menu_input.compare("R") == 0) {
		results();
}
	else if (menu_input.compare("Exit") == 0 || menu_input.compare("exit") == 0 || menu_input.compare("e") == 0 || menu_input.compare("E") == 0) {
		exit();
	}
	else {
		Menu();
	}
}

void InputManager::play(GameManager* previous_game_manager) {
	while (true) {
		clearConsole();

		GameManager* game_manager = game_manager->Instance();

		if (previous_game_manager == nullptr) {
			std::cout << "White players name: ";
			std::string player_one_name_input;
			std::cin >> player_one_name_input;

			std::cout << "Is '" << player_one_name_input << "' a bot? (y/n) ";
			std::string player_one_is_bot_input;
			std::cin >> player_one_is_bot_input;
			bool player_one_is_bot = false;
			if (player_one_is_bot_input.compare("yes") == 0 || player_one_is_bot_input.compare("y") == 0) {
				player_one_is_bot = true;
			}

			std::string player_two_name_input;
			do {
				std::cout << "Black players name: ";
				std::cin >> player_two_name_input;
			} while (player_one_name_input.compare(player_two_name_input) == 0);

			std::cout << "Is '" << player_two_name_input << "' a bot? (y/n) ";
			std::string player_two_is_bot_input;
			std::cin >> player_two_is_bot_input;
			bool player_two_is_bot = false;
			if (player_two_is_bot_input.compare("yes") == 0 || player_two_is_bot_input.compare("y") == 0) {
				player_two_is_bot = true;
			}

			game_manager->StartGame(player_one_name_input, player_one_is_bot, player_two_name_input, player_two_is_bot);
		}
		else {
			game_manager = previous_game_manager;
			game_manager->ReStartGame();
		}

		RuleManager* rule_manager = rule_manager->Instance();

		PieceManager* piece_manager = piece_manager->Instance();
		piece_manager->InitPieces();

		Grid* grid = new Grid();
		grid->InitGrid(piece_manager);
		grid->DrawGrid(game_manager);

		InputManager* input_manager = input_manager->Instance();
		while (!game_manager->GetGameOver()) {
			input_manager->ReadCommand(piece_manager, grid, rule_manager, game_manager);
		}

		std::cout << "\nmenu(m) | play(p) | restart(r) | results(re) | exit(e): ";
		std::string input;
		std::cin >> input;
		if (input.compare("Menu") == 0 || input.compare("menu") == 0 || input.compare("m") == 0 || input.compare("M") == 0) {
			Menu();
		}
		else if (input.compare("Play") == 0 || input.compare("play") == 0 || input.compare("p") == 0 || input.compare("P") == 0) {
			play();
		}
		else if (input.compare("Restart") == 0 || input.compare("restart") == 0 || input.compare("r") == 0 || input.compare("R") == 0) {
			play(game_manager);
		}
		else if (input.compare("Results") == 0 || input.compare("results") == 0 || input.compare("re") == 0 || input.compare("Re") == 0) {
			results();
		}
		else if (input.compare("Exit") == 0 || input.compare("exit") == 0 || input.compare("e") == 0 || input.compare("E") == 0) {
			exit();
		}
		else {
			results();
		}
	}
}

void InputManager::results() {
	clearConsole();

	std::string line;
	std::ifstream results_file("results.csv");
	if (results_file.is_open()) {
		while (std::getline(results_file, line)) {
			std::vector<std::string> results;
			std::string act_result = "";
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ';') {
					results.push_back(act_result);
					act_result = "";
					continue;
				}
				else {
					act_result += line[i];
				}
			}
			results.push_back(act_result);

			std::cout << results[0] << " - " << results[1] << "\t" << results[2] << ":" << results[3] << '\n';
		}
	}

	std::cout << "\nmenu(m) | play(p) | exit(e): ";
	std::string input;
	std::cin >> input;
	if (input.compare("Menu") == 0 || input.compare("menu") == 0 || input.compare("m") == 0 || input.compare("M") == 0) {
		Menu();
	}
	else if (input.compare("Play") == 0 || input.compare("play") == 0 || input.compare("p") == 0 || input.compare("P") == 0) {
		play();
	}
	else if (input.compare("Exit") == 0 || input.compare("exit") == 0 || input.compare("e") == 0 || input.compare("E") == 0) {
		exit();
	}
	else {
		results();
	}
}

int InputManager::exit() {
	return 0;
}

bool InputManager::increaseBotThinking(GameManager* game_manager) {
	if (bot_thinking >= BOT_THINK_WRITE_BOT_THINK) {
		if (!bot_thinking_text_once) {
			std::cout << game_manager->GetActPlayer()->GetName() << " is thinking..\n";
		}
		bot_thinking_text_once = true;
	}
	if (bot_thinking++ >= MAX_BOT_THINK) {
		return true;
	}

	return false;
}