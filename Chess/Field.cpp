#include "Field.h"

Field::Field(std::shared_ptr<Position> position, std::shared_ptr<Piece> piece, Color color)
	:position(position), piece(piece), color(color) {}

std::shared_ptr<Position> Field::GetPosition() {
	return position;
}
std::shared_ptr<Piece> Field::GetPiece() {
	return piece;
}
Color Field::GetColor() {
	return color;
}