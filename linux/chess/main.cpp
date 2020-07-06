#include <iostream>
#include <string>

#include "Grid.h"
#include "PieceManager.h"
#include "InputManager.h"
#include "RuleManager.h"

PieceManager* PieceManager::instance = 0;
InputManager* InputManager::instance = 0;
GameManager* GameManager::instance = 0;
RuleManager* RuleManager::instance = 0;

int main()
{
  GameManager* game_manager = game_manager->Instance();
  game_manager->StartGame("Jani", "Pista", 0);

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
}


