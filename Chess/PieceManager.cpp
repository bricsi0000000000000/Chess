#include "PieceManager.h"

PieceManager::~PieceManager()
{
	delete this;
}

PieceManager* PieceManager::Instance() {
	if (!instance) {
		instance = new PieceManager();
	}
	return instance;
}

void PieceManager::InitPieces() {
	pieces.clear();

	for (int i = 0; i < 8; i++) {
		pieces.push_back(std::shared_ptr<Piece>(new Piece("white pawn " + std::to_string(i + 1), std::shared_ptr<Position>(new Position(6, i)), Color::White, PieceType::Pawn)));
	}

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left white rook", std::shared_ptr<Position>(new Position(7, 0)), Color::White, PieceType::Rook)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right white rook", std::shared_ptr<Position>(new Position(7, 7)), Color::White, PieceType::Rook)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left white knight", std::shared_ptr<Position>(new Position(7, 1)), Color::White, PieceType::Knight)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right white knight", std::shared_ptr<Position>(new Position(7, 6)), Color::White, PieceType::Knight)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left white bishop", std::shared_ptr<Position>(new Position(7, 2)), Color::White, PieceType::Bishop)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right white bishop", std::shared_ptr<Position>(new Position(7, 5)), Color::White, PieceType::Bishop)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("white queen", std::shared_ptr<Position>(new Position(7, 3)), Color::White, PieceType::Queen)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("white king", std::shared_ptr<Position>(new Position(7, 4)), Color::White, PieceType::King)));

	for (int i = 0; i < 8; i++) {
		pieces.push_back(std::shared_ptr<Piece>(new Piece("black pawn " + std::to_string(i + 1), std::shared_ptr<Position>(new Position(1, i)), Color::Black, PieceType::Pawn)));
	}

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left black rook", std::shared_ptr<Position>(new Position(0, 0)), Color::Black, PieceType::Rook)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right black rook", std::shared_ptr<Position>(new Position(0, 7)), Color::Black, PieceType::Rook)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left black knight", std::shared_ptr<Position>(new Position(0, 1)), Color::Black, PieceType::Knight)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right black knight", std::shared_ptr<Position>(new Position(0, 6)), Color::Black, PieceType::Knight)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("left black bishop", std::shared_ptr<Position>(new Position(0, 2)), Color::Black, PieceType::Bishop)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("right black bishop", std::shared_ptr<Position>(new Position(0, 5)), Color::Black, PieceType::Bishop)));

	pieces.push_back(std::shared_ptr<Piece>(new Piece("black queen", std::shared_ptr<Position>(new Position(0, 3)), Color::Black, PieceType::Queen)));
	pieces.push_back(std::shared_ptr<Piece>(new Piece("black king", std::shared_ptr<Position>(new Position(0, 4)), Color::Black, PieceType::King)));
}

std::shared_ptr<Piece> PieceManager::GetKing(Color color) {
	for (const auto& piece : pieces) {
		if (piece->GetColor() == color) {
			if (piece->GetPieceType() == PieceType::King) {
				return piece;
			}
		}
	}
}

int PieceManager::GetPieceCount(Color color) {
	int count = 0;

	for (const auto& piece : pieces) {
		if (piece->GetColor() == color) {
			count++;
		}
	}

	return count;
}

int PieceManager::GetPieceCount(PieceType piece_type, Color color) {
	int count = 0;

	for (const auto& piece : pieces) {
		if (piece->GetPieceType() == piece_type && piece->GetColor() == color) {
			count++;
		}
	}

	return count;
}

std::shared_ptr<Piece> PieceManager::GetPiece(std::shared_ptr<Position> position) {
	for (const auto& piece : pieces) {
		if (piece->GetPosition()->x == position->x && piece->GetPosition()->y == position->y) {
			return piece;
		}
	}
	return nullptr;
}

bool PieceManager::CanMove(std::shared_ptr<Position> from_position, std::shared_ptr<Position> to_position) {
	std::shared_ptr<Piece> piece(GetPiece(from_position));
	if (piece == nullptr) {
		return false;
	}

	return true;
}

void PieceManager::MovePiece(std::shared_ptr<Position> from_position, std::shared_ptr<Position> to_position) {
	std::shared_ptr<Piece> piece(GetPiece(from_position));
	piece->SetPosition(to_position);
}

void PieceManager::RemovePiece(std::shared_ptr<Position> position, GameManager* game_manager) {
	for (unsigned int i = 0; i < pieces.size(); i++) {
		if (pieces[i]->GetPosition()->x == position->x && pieces[i]->GetPosition()->y == position->y) {
			if (pieces[i]->GetPieceType() != PieceType::King) {
				game_manager->GetOppositePlayer()->AddOffPiece(pieces[i]);
				pieces.erase(pieces.begin() + i);
			}
		}
	}
}

void PieceManager::RevivePiece(std::shared_ptr<Piece> piece, GameManager* game_manager) {
	pieces.push_back(piece);
	game_manager->GetOppositePlayer()->RemoveOffPiece(piece);
}

void PieceManager::ChangePiece(std::shared_ptr<Piece> old_piece, std::string name, PieceType piece_type) {
	for (const auto& piece : pieces) {
		if (piece->GetName() == old_piece->GetName()) {
			piece->SetName(name);
			piece->SetPieceType(piece_type);
		}
	}
}

std::vector<std::shared_ptr<Piece>> PieceManager::GetPieces() {
	return pieces;
}