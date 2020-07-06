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
	std::string step_from;
	std::string step_to;
	std::shared_ptr<Piece> step_piece;
public:
	Player(std::string name, Color color, bool is_bot);
	std::string GetName();
	int GetPoints();
	void AddPoints(int points);
	Color GetColor();
	std::vector<std::shared_ptr<Piece>> GetOffPieces();
	void AddOffPiece(std::shared_ptr<Piece> piece);
	void RemoveOffPiece(std::shared_ptr<Piece> piece);
	void ClearOffPieces();
	bool IsBot();
	std::string GetStepFrom();
	std::string GetStepTo();
	void SetStepFrom(std::string position);
	void SetStepTo(std::string position);
	std::shared_ptr<Piece> GetStepPiece();
	void SetStepPiece(std::shared_ptr<Piece> piece);
};

#endif PLAYER_H