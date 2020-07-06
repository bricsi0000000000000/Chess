#ifndef FIELD_H
#define FIELD_H

#include<memory>

#include "Position.h"
#include "Piece.h"

class Field
{
private:
  std::shared_ptr<Position> position;
  std::shared_ptr<Piece> piece;
  Color color;
public:
  Field(std::shared_ptr<Position> position, std::shared_ptr<Piece> piece, Color color);

  std::shared_ptr<Position> GetPosition();
  std::shared_ptr<Piece> GetPiece();
  Color GetColor();
};

#endif // FIELD_H
