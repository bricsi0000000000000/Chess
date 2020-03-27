#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(std::string, std::shared_ptr<Position> position, Color color);
};

#endif ROOK_H