#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
	King(std::string, std::shared_ptr<Position> position, Color color);
};

#endif KING_H