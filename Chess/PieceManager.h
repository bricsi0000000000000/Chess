#ifndef PIECE_MANAGER_H
#define PIECE_MANAGER_H

#include<vector>
#include<memory>

#include"Piece.h"

class PieceManager {
private:
	std::vector<std::shared_ptr<Piece>> black_pieces;
	std::vector<std::shared_ptr<Piece>> white_pieces;

	PieceManager() {}
	static PieceManager* instance;
public:
	static PieceManager* Instance() {
		if (!instance) {
			instance = new PieceManager();
		}
		return instance;
	}

	void InitPieces() {
		for (int i = 0; i < 8; i++) {
			black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("pawn_black_" + std::to_string(i + 1), std::shared_ptr<Position>(new Position(7, i)), Color::Black)));
		}

		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("rook_black_1", std::shared_ptr<Position>(new Position(6, 0)), Color::Black)));
		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("rook_black_2", std::shared_ptr<Position>(new Position(6, 7)), Color::Black)));

		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("knight_black_1", std::shared_ptr<Position>(new Position(6, 1)), Color::Black)));
		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("knight_black_2", std::shared_ptr<Position>(new Position(6, 6)), Color::Black)));

		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("bishop_black_1", std::shared_ptr<Position>(new Position(6, 2)), Color::Black)));
		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("bishop_black_2", std::shared_ptr<Position>(new Position(6, 5)), Color::Black)));

		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("queen_black", std::shared_ptr<Position>(new Position(6, 3)), Color::Black)));
		black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("king_black", std::shared_ptr<Position>(new Position(6, 4)), Color::Black)));

		for (int i = 0; i < 8; i++) {
			black_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("pawn_white_" + std::to_string(i + 1), std::shared_ptr<Position>(new Position(1, i)), Color::White)));
		}

		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("rook_white_1", std::shared_ptr<Position>(new Position(0, 0)), Color::White)));
		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("rook_white_2", std::shared_ptr<Position>(new Position(0, 7)), Color::White)));

		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("knight_white_1", std::shared_ptr<Position>(new Position(0, 1)), Color::White)));
		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("knight_white_2", std::shared_ptr<Position>(new Position(0, 6)), Color::White)));

		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("bishop_white_1", std::shared_ptr<Position>(new Position(0, 2)), Color::White)));
		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("bishop_white_2", std::shared_ptr<Position>(new Position(0, 5)), Color::White)));

		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("queen_white", std::shared_ptr<Position>(new Position(0, 3)), Color::White)));
		white_pieces.push_back(std::shared_ptr<Pawn>(new Pawn("king_white", std::shared_ptr<Position>(new Position(0, 4)), Color::White)));
	}
	
	std::vector<std::shared_ptr<Piece>> GetBlackPieces() {
		return black_pieces;
	}
	std::vector<std::shared_ptr<Piece>> GetWhitePieces() {
		return white_pieces;
	}
};

#endif PIECE_MANAGER_H