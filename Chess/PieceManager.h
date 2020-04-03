#ifndef PIECE_MANAGER_H
#define PIECE_MANAGER_H

#include<vector>
#include<memory>

#include "Piece.h"
#include "PieceType.h"

class PieceManager {
private:
	std::vector<std::shared_ptr<Piece>> black_pieces;
	std::vector<std::shared_ptr<Piece>> white_pieces;
	std::vector<std::shared_ptr<Piece>> pieces;

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
			black_pieces.push_back(std::shared_ptr<Piece>(new Piece("pawn_black_" + std::to_string(i + 1), std::shared_ptr<Position>(new Position(6, i)), Color::Black, PieceType::Pawn)));
		}

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("rook_black_1", std::shared_ptr<Position>(new Position(7, 0)), Color::Black, PieceType::Rook)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("rook_black_2", std::shared_ptr<Position>(new Position(7, 7)), Color::Black, PieceType::Rook)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("knight_black_1", std::shared_ptr<Position>(new Position(7, 1)), Color::Black, PieceType::Knight)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("knight_black_2", std::shared_ptr<Position>(new Position(7, 6)), Color::Black, PieceType::Knight)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("bishop_black_1", std::shared_ptr<Position>(new Position(7, 2)), Color::Black, PieceType::Bishop)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("bishop_black_2", std::shared_ptr<Position>(new Position(7, 5)), Color::Black, PieceType::Bishop)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("queen_black", std::shared_ptr<Position>(new Position(7, 3)), Color::Black, PieceType::Queen)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("king_black", std::shared_ptr<Position>(new Position(7, 4)), Color::Black, PieceType::King)));

		for (int i = 0; i < 8; i++) {
			white_pieces.push_back(std::shared_ptr<Piece>(new Piece("pawn_white_" + std::to_string(i + 1), std::shared_ptr<Position>(new Position(1, i)), Color::White, PieceType::Pawn)));
		}

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("rook_white_1", std::shared_ptr<Position>(new Position(0, 0)), Color::White, PieceType::Rook)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("rook_white_2", std::shared_ptr<Position>(new Position(0, 7)), Color::White, PieceType::Rook)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("knight_white_1", std::shared_ptr<Position>(new Position(0, 1)), Color::White, PieceType::Knight)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("knight_white_2", std::shared_ptr<Position>(new Position(0, 6)), Color::White, PieceType::Knight)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("bishop_white_1", std::shared_ptr<Position>(new Position(0, 2)), Color::White, PieceType::Bishop)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("bishop_white_2", std::shared_ptr<Position>(new Position(0, 5)), Color::White, PieceType::Bishop)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("queen_white", std::shared_ptr<Position>(new Position(0, 3)), Color::White, PieceType::Queen)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("king_white", std::shared_ptr<Position>(new Position(0, 4)), Color::White, PieceType::King)));

		for (const auto& piece : white_pieces) {
			pieces.push_back(piece);
		}
		for (const auto& piece : black_pieces) {
			pieces.push_back(piece);
		}
	}

	std::shared_ptr<Piece> GetPiece(std::shared_ptr<Position> position) {
		for (const auto& piece : pieces) {
			if (piece->GetPosition()->x == position->x && piece->GetPosition() ->y == position->y) {
				return piece;
			}
		}
		return nullptr;
	}
	
	bool MovePiece(std::shared_ptr<Position> from_position, std::shared_ptr<Position> to_position) {
		if (GetPiece(from_position) == nullptr) {
			return false;
		}

		GetPiece(from_position)->SetPosition(to_position);
	}

	std::vector<std::shared_ptr<Piece>> GetBlackPieces() {
		return black_pieces;
	}
	std::vector<std::shared_ptr<Piece>> GetWhitePieces() {
		return white_pieces;
	}
	std::vector<std::shared_ptr<Piece>> GetPieces() {
		return pieces;
	}
};

#endif PIECE_MANAGER_H