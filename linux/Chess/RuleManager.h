#ifndef RULEMANAGER_H
#define RULEMANAGER_H

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

#endif // RULEMANAGER_H
