#ifndef GRID_H
#define GRID_H

#include<vector>

#include "Field.h"
#include "Position.h"
#include "PieceManager.h"


#ifdef _WIN32
#include <Windows.h>
#endif

class Grid
{
private:
  std::vector<std::vector<std::shared_ptr<Field>>> grid;
  PieceManager* piece_manager;

#pragma GRID_CHARACTERS
#ifdef _WIN32
  const char horizontal_line = (char)196;
#endif
#ifdef linux
  const char horizontal_line = '-';
#endif
#ifdef _WIN32
  const char cross_line = (char)197;
#endif
#ifdef linux
  const char cross_line = '+';
#endif
#ifdef _WIN32
  const char vertical_line = (char)179;
#endif
#ifdef linux
  const char vertical_line = '|';
#endif
#ifdef _WIN32
  const char top_right_edge = (char)191;
#endif
#ifdef linux
  const char top_right_edge = '-';
#endif
#ifdef _WIN32
  const char top_left_edge = (char)218;
#endif
#ifdef linux
  const char top_left_edge = '-';
#endif
#ifdef _WIN32
  const char bottom_left_edge = (char)192;
#endif
#ifdef linux
  const char bottom_left_edge = '-';
#endif
#ifdef _WIN32
  const char bottom_right_edge = (char)217;
#endif
#ifdef linux
  const char bottom_right_edge = '-';
#endif
#ifdef _WIN32
  const char bottom_mid = (char)193;
#endif
#ifdef linux
  const char bottom_mid = '-';
#endif
#ifdef _WIN32
  const char top_mid = (char)194;
#endif
#ifdef linux
  const char top_mid = '-';
#endif
#ifdef _WIN32
  const char right_mid = (char)180;
#endif
#ifdef linux
  const char right_mid = '|';
#endif
#ifdef _WIN32
  const char left_mid = (char)195;
#endif
#ifdef linux
  const char left_mid = '|';
#endif
#pragma endregion

#ifdef _WIN32
#pragma region CONSOLE_COLORS
  HANDLE coloring = GetStdHandle(STD_OUTPUT_HANDLE);
  int black_white = 7;
  int border_color = 8;
  int white_piece_color = 15;
  int black_piece_color = 14;
  int pink_color = 13;
#pragma endregion
#endif

  void setConsoleColor(std::string color_name);
  void clearConsole();
  void writePieceNameInitials(std::shared_ptr<Piece> piece);
public:
  void InitGrid(PieceManager* piece_manager);
  void DrawGrid(GameManager* game_manager, std::vector<std::shared_ptr<Position>> highlight_cells = {});
  std::vector<std::vector<std::shared_ptr<Field>>> GetGrid();
};

#endif // GRID_H
