#ifndef RULE_MANAGER_H
#define RULE_MANAGER_H

#include <iostream>
#include <cmath>

#include "Piece.h"
#include "Position.h"
#include "PieceManager.h"

class RuleManager {
private:
	RuleManager() {}
	static RuleManager* instance;
public:
	static RuleManager* Instance() {
		if (!instance) {
			instance = new RuleManager();
		}
		return instance;
	}

	static bool CanStep(std::shared_ptr<Piece> piece, std::shared_ptr<Position> position, PieceManager* piece_manager) {
		bool is_piece_between = false;

		switch (piece->GetPieceType())
		{
		case PieceType::Pawn:
			if (piece->GetColor() == Color::White) {
				if (piece->GetPosition()->y == position->y) {
					if (piece->GetPosition()->x == 6) {
						if (piece->GetPosition()->x - 2 == position->x) {
							return true;
						}
					}

					if (piece->GetPosition()->x - 1 == position->x) {
						return true;
					}
				}
			}
			else if (piece->GetColor() == Color::Black) {
				if (piece->GetPosition()->y == position->y) {
					if (piece->GetPosition()->x == 1) {
						if (piece->GetPosition()->x + 2 == position->x) {
							return true;
						}
					}

					if (piece->GetPosition()->x + 1 == position->x) {
						return true;
					}
				}
			}
			break;
		case PieceType::Rook:
			if (piece->GetPosition()->y != position->y && piece->GetPosition()->x != position->x) {
				return false;
			}

			if (piece->GetPosition()->y == position->y) {
				// from down to up
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == position->y) {
						if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x) {
							return false;
						}
					}
				}

				// from up to down
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == position->y) {
						if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x) {
							return false;
						}
					}
				}
			}

			if (piece->GetPosition()->x == position->x) {
				// from left to right
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->x == position->x) {
						if (act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
							return false;
						}
					}
				}

				// from right to left
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->x == position->x) {
						if (act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
							return false;
						}
					}
				}
			}

			return true;
			break;
		case PieceType::Knight:
			if ((piece->GetPosition()->x - 2 == position->x && piece->GetPosition()->y - 1 == position->y) || // top-left
				(piece->GetPosition()->x - 2 == position->x && piece->GetPosition()->y + 1 == position->y) || // top-right
				(piece->GetPosition()->x - 1 == position->x && piece->GetPosition()->y + 2 == position->y) || // right-top
				(piece->GetPosition()->x + 1 == position->x && piece->GetPosition()->y + 2 == position->y) || // right-bottom
				(piece->GetPosition()->x + 2 == position->x && piece->GetPosition()->y + 1 == position->y) || // bottom-right
				(piece->GetPosition()->x + 2 == position->x && piece->GetPosition()->y - 1 == position->y) || // bottom-left
				(piece->GetPosition()->x + 1 == position->x && piece->GetPosition()->y - 2 == position->y) || // left-bottom
				(piece->GetPosition()->x - 1 == position->x && piece->GetPosition()->y - 2 == position->y)    // left-top
				)
			{
				return true;
			}

			return false;
			break;
		case PieceType::Bishop:
			if (std::abs(piece->GetPosition()->x - position->x) != std::abs(piece->GetPosition()->y - position->y)) {
				return false;
			}

			// left-up
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x &&
						act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
						return false;
					}
				}
			}
			// right-up
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x &&
						act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
						return false;
					}
				}
			}

			// right-bottom
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x &&
						act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
						return false;
					}
				}
			}

			// left-bottom
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x &&
						act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
						return false;
					}
				}
			}
			return true;
			break;
		case PieceType::Queen:
			if (std::abs(piece->GetPosition()->x - position->x) != std::abs(piece->GetPosition()->y - position->y)) {
				if (piece->GetPosition()->y != position->y && piece->GetPosition()->x != position->x) {
					return false;
				}
			}

			// left-up
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x &&
						act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
						return false;
					}
				}
			}
			// right-up
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x &&
						act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
						return false;
					}
				}
			}

			// right-bottom
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x &&
						act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
						return false;
					}
				}
			}

			// left-bottom
			for (auto& act_piece : piece_manager->GetPieces()) {
				if (std::abs(act_piece->GetPosition()->x - position->x) == std::abs(act_piece->GetPosition()->y - position->y)) {
					if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x &&
						act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
						return false;
					}
				}
			}

			if (piece->GetPosition()->y == position->y) {
				// from down to up
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == position->y) {
						if (act_piece->GetPosition()->x > position->x && act_piece->GetPosition()->x < piece->GetPosition()->x) {
							return false;
						}
					}
				}

				// from up to down
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->y == position->y) {
						if (act_piece->GetPosition()->x < position->x && act_piece->GetPosition()->x > piece->GetPosition()->x) {
							return false;
						}
					}
				}
			}

			if (piece->GetPosition()->x == position->x) {
				// from left to right
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->x == position->x) {
						if (act_piece->GetPosition()->y < position->y && act_piece->GetPosition()->y > piece->GetPosition()->y) {
							return false;
						}
					}
				}

				// from right to left
				for (auto& act_piece : piece_manager->GetPieces()) {
					if (act_piece->GetPosition()->x == position->x) {
						if (act_piece->GetPosition()->y > position->y && act_piece->GetPosition()->y < piece->GetPosition()->y) {
							return false;
						}
					}
				}
			}

			return true;
			break;
		case PieceType::King:
			// left-up
			if (piece->GetPosition()->x - 1 == position->x && piece->GetPosition()->y - 1 == position->y) {
				return true;
			}
			// up
			if (piece->GetPosition()->x - 1 == position->x && piece->GetPosition()->y == position->y) {
				return true;
			}
			// right-up
			if (piece->GetPosition()->x - 1 == position->x && piece->GetPosition()->y + 1 == position->y) {
				return true;
			}
			// right
			if (piece->GetPosition()->x == position->x && piece->GetPosition()->y + 1 == position->y) {
				return true;
			}
			// right-bottom
			if (piece->GetPosition()->x + 1 == position->x && piece->GetPosition()->y + 1 == position->y) {
				return true;
			}
			// bottom
			if (piece->GetPosition()->x + 1 == position->x && piece->GetPosition()->y == position->y) {
				return true;
			}
			// bottom-left
			if (piece->GetPosition()->x + 1 == position->x && piece->GetPosition()->y - 1 == position->y) {
				return true;
			}
			// left
			if (piece->GetPosition()->x == position->x && piece->GetPosition()->y - 1 == position->y) {
				return true;
			}

			return false;
			break;
		default:
			break;
		}

		return false;
	}
};

#endif RULE_MANAGER_H