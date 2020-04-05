#ifndef RULE_MANAGER_H
#define RULE_MANAGER_H

#include <iostream>

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
		switch (piece->GetPieceType())
		{
		case PieceType::Pawn:
			if (piece->GetColor() == Color::Black) {
				if (piece->GetPosition()->y + 1 == position->y) {
					return true;
				}
			}
			break;
		default:
			break;
		}

		return false;
	}
};

#endif RULE_MANAGER_H