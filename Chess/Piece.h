#ifndef PIECE_H
#define PIECE_H

#include<string>

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
	std::shared_ptr<Position> GetPosition();
	void SetPosition(std::shared_ptr<Position> to_position);
	Color GetColor();
	PieceType GetPieceType();
};

#endif PIECE_H