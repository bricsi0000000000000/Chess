#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include<vector>
#include<memory>

#include "Piece.h"
#include "PieceType.h"
#include "GameManager.h"
#include "Color.h"

class PieceManager {
private:
  std::vector<std::shared_ptr<Piece>> pieces;

  ~PieceManager();
  PieceManager() {}
  static PieceManager* instance;
public:
  static PieceManager* Instance();
  void InitPieces();
  std::shared_ptr<Piece> GetKing(Color color);
  int GetPieceCount(Color color);
  int GetPieceCount(PieceType piece_type, Color color);
  std::shared_ptr<Piece> GetPiece(std::shared_ptr<Position> position);
  bool CanMove(std::shared_ptr<Position> from_position, std::shared_ptr<Position> to_position);
  void MovePiece(std::shared_ptr<Position> from_position, std::shared_ptr<Position> to_position);
  void RemovePiece(std::shared_ptr<Position> position, GameManager* game_manager);
  void RevivePiece(std::shared_ptr<Piece> piece, GameManager* game_manager);
  void ChangePiece(std::shared_ptr<Piece> old_piece, std::string name, PieceType piece_type);
  std::vector<std::shared_ptr<Piece>> GetPieces();
};

#endif // PIECEMANAGER_H
