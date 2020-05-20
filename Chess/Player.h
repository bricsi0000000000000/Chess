#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Color.h"
#include "Piece.h"

class Player
{
private:
	std::string name;
	int points;
	Color color;
	std::vector<std::shared_ptr<Piece>> off_pieces;
public:
	Player(std::string name, Color color);
	std::string GetName();
	int GetPoints();
	Color GetColor();
	std::vector<std::shared_ptr<Piece>> GetOffPieces();
	void AddOffPiece(std::shared_ptr<Piece> piece);
	void RemoveOffPiece(std::shared_ptr<Piece> piece);
};

#endif PLAYER_H