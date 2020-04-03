#include "Piece.h"

Piece::Piece(std::string name, std::shared_ptr<Position> position, Color color, PieceType piece_type) :
	name(name),
	position(position),
	color(color),
	piece_type(piece_type)
{}
Piece::Piece() :name(" "), position(new Position(-1,-1)), color(Color::Nothing), piece_type(PieceType::Nothing) {}
std::string  Piece::GetName() {
	return name;
}
std::shared_ptr<Position> Piece::GetPosition() {
	return position;
}
void Piece::SetPosition(std::shared_ptr<Position> to_position) {
	position = to_position;
}
Color Piece::GetColor() {
	return color;
}
PieceType Piece::GetPieceType() {
	return piece_type;
}