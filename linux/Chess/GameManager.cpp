#include "GameManager.h"

GameManager::~GameManager() {
  delete this;
}

void GameManager::saveResults() {
  std::ofstream results_file("results.csv", std::ios::app);
  if (results_file.is_open()) {
    results_file << GetActPlayer()->GetName() << ";" << GetOppositePlayer()->GetName() << ";" << GetActPlayer()->GetPoints() << ";" << GetOppositePlayer()->GetPoints() << '\n';
    results_file.close();
  }
  else {
    std::cout << "Something is wrong with the results.\n";
  }
}

GameManager* GameManager::Instance() {
  if (!instance) {
    instance = new GameManager();
  }
  return instance;
}

void GameManager::ReStartGame() {
  game_over = false;
  act_player = 1;
  all_steps.clear();
  GetPlayerOne()->ClearOffPieces();
  GetPlayerTwo()->ClearOffPieces();
}

void GameManager::StartGame(std::string player_one_name, bool player_one_is_bot, std::string player_two_name, bool player_two_is_bot) {
  game_over = false;
  act_player = 1;
  all_steps.clear();
  player_one = new Player(player_one_name, Color::White, player_one_is_bot);
  player_two = new Player(player_two_name, Color::Black, player_two_is_bot);
  GetPlayerOne()->ClearOffPieces();
  GetPlayerTwo()->ClearOffPieces();
}

bool GameManager::GetGameOver() {
  return game_over;
}
void GameManager::GameOver(bool opposite_player) {
  game_over = true;
  if (opposite_player) {
    std::cout << GetOppositePlayer()->GetName() << " won\n";
  }
  else {
    std::cout << GetActPlayer()->GetName() << " won\n";
  }
  GetActPlayer()->AddPoints(1);
  saveResults();
  saveAllSteps();
}

void GameManager::GiveUp() {
  game_over = true;
  std::cout << GetActPlayer()->GetName() << " gave up, so " << GetOppositePlayer()->GetName() << " won\n";
  GetOppositePlayer()->AddPoints(1);
  saveResults();
  saveAllSteps();
}

Player* GameManager::GetPlayerOne() {
  return player_one;
}

Player* GameManager::GetPlayerTwo() {
  return player_two;
}

Player* GameManager::GetActPlayer() {
  return act_player == 1 ? player_one : player_two;
}

int GameManager::GetActPlayerNumber() {
  return act_player;
}

Player* GameManager::GetOppositePlayer() {
  return act_player == 2 ? player_one : player_two;
}

void GameManager::ChangePlayer() {
  act_player = act_player == 1 ? 2 : 1;
}

void GameManager::AddStepToAllSteps() {
  all_steps << GetActPlayer()->GetName() << " stepped with " << GetActPlayer()->GetStepPiece()->GetName() << " from " << GetActPlayer()->GetStepFrom() << " to " << GetActPlayer()->GetStepTo() << '\n';
}

void GameManager::saveAllSteps() {
  std::stringstream file_name;
  file_name << GetPlayerOne()->GetName() << "-" << GetPlayerTwo()->GetName() << "_" << GetPlayerOne()->GetPoints() << "-" << GetPlayerTwo()->GetPoints() << "_all_steps.txt";
  std::ofstream file(file_name.str(), std::ios::app);
  if (file.is_open()) {
    file << all_steps.str();
    file.close();
  }
  else {
    std::cout << "Something is wrong with the all steps file.\n";
  }
}
