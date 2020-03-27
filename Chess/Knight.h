#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(std::string, std::shared_ptr<Position> position, Color color);
};

#endif KNIGHT_H