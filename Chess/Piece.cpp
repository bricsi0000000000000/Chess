#include "Piece.h"

Piece::Piece(std::string name, std::shared_ptr<Position> position, Color color) :
	name(name),
	position(position),
	color(color)
{}
Piece::Piece() :name(""), position(new Position(-1,-1)), color(Color::Black) {}
std::string  Piece::GetName() {
	return name;
}
std::shared_ptr<Position> Piece::GetPosition() {
	return position;
}
Color Piece::GetColor() {
	return color;
}