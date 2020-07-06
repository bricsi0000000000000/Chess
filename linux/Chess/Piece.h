#ifndef PIECE_H
#define PIECE_H

#include<string>
#include <memory>

#include "Position.h"
#include "Color.h"
#include "PieceType.h"

class Piece
{
private:
  std::string name;
  std::shared_ptr<Position> position;
  Color color;
  PieceType piece_type;
public:
  Piece();
  Piece(std::string name, std::shared_ptr<Position> position, Color color, PieceType piece_type);
  std::string GetName();
  void SetName(std::string name);
  std::shared_ptr<Position> GetPosition();
  void SetPosition(std::shared_ptr<Position> to_position);
  Color GetColor();
  PieceType GetPieceType();
  void SetPieceType(PieceType piece_type);
};

#endif // PIECE_H
