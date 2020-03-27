#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(std::string, std::shared_ptr<Position> position, Color color);
};

#endif QUEEN_H