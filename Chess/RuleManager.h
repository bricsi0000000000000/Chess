#ifndef RULE_MANAGER_H
#define RULE_MANAGER_H

#include <iostream>
#include <cmath>

#include "Piece.h"
#include "Position.h"
#include "PieceManager.h"

class RuleManager {
private:
	~RuleManager();
	RuleManager() {}
	static RuleManager* instance;
public:
	static RuleManager* Instance();
	static bool CanStep(std::shared_ptr<Piece> piece, std::shared_ptr<Position> position, PieceManager* piece_manager);
};

#endif RULE_MANAGER_H