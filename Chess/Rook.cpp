#include "Rook.h"

Rook::Rook(std::string name, std::shared_ptr<Position> position, Color color) :
	Piece(name, position, color) {}