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
	Field(std::shared_ptr<Position> position, std::shared_ptr<Piece> piece, Color color)
		:position(position), piece(piece), color(color) {}

	std::shared_ptr<Position> GetPosition() {
		return position;
	}
	std::shared_ptr<Piece> GetPiece() {
		return piece;
	}
	Color GetColor() {
		return color;
	}
};

#endif FIELD_H