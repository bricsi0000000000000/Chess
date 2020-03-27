#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(std::string, std::shared_ptr<Position> position, Color color);
};

#endif PAWN_H