#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(std::string, std::shared_ptr<Position> position, Color color);
};

#endif BISHOP_H