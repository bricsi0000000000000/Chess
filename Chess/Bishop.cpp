#include "Bishop.h"

Bishop::Bishop(std::string name, std::shared_ptr<Position> position, Color color) :
	Piece(name, position, color) {}