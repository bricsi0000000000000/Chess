#include "Player.h"

Player::Player(std::string name, Color color, bool is_bot) : name(name), points(0), color(color), is_bot(is_bot) {}

std::string Player::GetName() {
  return name;
}

int Player::GetPoints() {
  return points;
}

void Player::AddPoints(int point) {
  points += point;
}

Color Player::GetColor() {
  return color;
}

std::vector<std::shared_ptr<Piece>> Player::GetOffPieces() {
  return off_pieces;
}

void Player::AddOffPiece(std::shared_ptr<Piece> piece) {
  off_pieces.push_back(piece);
}

void Player::RemoveOffPiece(std::shared_ptr<Piece> piece) {
  for (int i = 0; i < off_pieces.size(); i++) {
    if (off_pieces[i]->GetPosition()->x == piece->GetPosition()->x && off_pieces[i]->GetPosition()->y == piece->GetPosition()->y) {
      off_pieces.erase(off_pieces.begin() + i);
    }
  }
}

void Player::ClearOffPieces() {
  off_pieces.clear();
}

bool Player::IsBot() {
  return is_bot;
}

std::string Player::GetStepFrom() {
  return step_from;
}

std::string Player::GetStepTo() {
  return step_to;
}

void Player::SetStepFrom(std::string position) {
  step_from = position;
}

void Player::SetStepTo(std::string position) {
  step_to = position;
}

std::shared_ptr<Piece> Player::GetStepPiece() {
  return step_piece;
}

void Player::SetStepPiece(std::shared_ptr<Piece> piece) {
  step_piece = piece;
}
