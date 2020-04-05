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
			white_pieces.push_back(std::shared_ptr<Piece>(new Piece("white pawn " + std::to_string(i + 1), std::shared_ptr<Position>(new Position(6, i)), Color::White, PieceType::Pawn)));
		}

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("left white rook", std::shared_ptr<Position>(new Position(7, 0)), Color::White, PieceType::Rook)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("right white rook", std::shared_ptr<Position>(new Position(7, 7)), Color::White, PieceType::Rook)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("left white knight", std::shared_ptr<Position>(new Position(7, 1)), Color::White, PieceType::Knight)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("right white knight", std::shared_ptr<Position>(new Position(7, 6)), Color::White, PieceType::Knight)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("left white bishop", std::shared_ptr<Position>(new Position(7, 2)), Color::White, PieceType::Bishop)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("right white bishop", std::shared_ptr<Position>(new Position(7, 5)), Color::White, PieceType::Bishop)));

		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("white queen", std::shared_ptr<Position>(new Position(7, 3)), Color::White, PieceType::Queen)));
		white_pieces.push_back(std::shared_ptr<Piece>(new Piece("white king", std::shared_ptr<Position>(new Position(7, 4)), Color::White, PieceType::King)));

		for (int i = 0; i < 8; i++) {
			black_pieces.push_back(std::shared_ptr<Piece>(new Piece("black pawn " + std::to_string(i + 1), std::shared_ptr<Position>(new Position(1, i)), Color::Black, PieceType::Pawn)));
		}

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("left black rook", std::shared_ptr<Position>(new Position(0, 0)), Color::Black, PieceType::Rook)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("right black rook", std::shared_ptr<Position>(new Position(0, 7)), Color::Black, PieceType::Rook)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("left black knight", std::shared_ptr<Position>(new Position(0, 1)), Color::Black, PieceType::Knight)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("right black knight", std::shared_ptr<Position>(new Position(0, 6)), Color::Black, PieceType::Knight)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("left black bishop", std::shared_ptr<Position>(new Position(0, 2)), Color::Black, PieceType::Bishop)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("right black bishop", std::shared_ptr<Position>(new Position(0, 5)), Color::Black, PieceType::Bishop)));

		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("black queen", std::shared_ptr<Position>(new Position(0, 3)), Color::Black, PieceType::Queen)));
		black_pieces.push_back(std::shared_ptr<Piece>(new Piece("black king", std::shared_ptr<Position>(new Position(0, 4)), Color::Black, PieceType::King)));

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