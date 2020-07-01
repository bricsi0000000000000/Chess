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
	bool is_bot;
public:
	Player(std::string name, Color color, bool is_bot);
	std::string GetName();
	int GetPoints();
	Color GetColor();
	std::vector<std::shared_ptr<Piece>> GetOffPieces();
	void AddOffPiece(std::shared_ptr<Piece> piece);
	void RemoveOffPiece(std::shared_ptr<Piece> piece);
	bool IsBot();
};

#endif PLAYER_H