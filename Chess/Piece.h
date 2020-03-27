#ifndef PIECE_H
#define PIECE_H

#include<string>

#include "Position.h"
#include "Color.h"

class Piece
{
private:
	std::string name;
	std::shared_ptr<Position> position;
	Color color;
public:
	Piece();
	Piece(std::string name, std::shared_ptr<Position> position, Color color);
	std::string GetName();
	std::shared_ptr<Position> GetPosition();
	Color GetColor();
};

#endif PIECE_H