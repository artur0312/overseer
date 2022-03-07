#pragma once
#include<iostream>
#include<string>

class Chessboard{
  int kingPosition=60;
public:
  static char board[8][8];
  void show();
  std::string valid_moves();
  std::string moves_pawn(int position);
  std::string moves_rook(int position);
  std::string moves_knight(int position);
  std::string moves_bishop(int position);
  std::string moves_queen(int position);
  std::string moves_king(int position);
  bool king_safe();
  bool is_inside(int row, int column);
  void make_move(std::string move);
  void undo_move(std::string move);
  void flipboard();
};
