#include "../include/rating.h"

int rating(int movements,int depth){
  Chessboard board;
  int result=0;
  result+=rate_attack();
  int material=rate_material();
  std::cout<<material<<"\n";
  result+=material;
  result+=rate_moveability();
  result+=rate_positional();
  board.flipboard();
  result-=rate_attack();
  material=rate_material();
  std::cout<<material<<"\n";
  board.show();
  result-=material;
  result-=rate_moveability();
  result-=rate_positional();
  board.flipboard();
  return (result+depth*50);
}

int rate_attack(){
  return 0;
}
int rate_material(){
  Chessboard chessboard;
  int result=0;
  int bishop_count=0;
  for(int i=0;i<64;i++){
    char piece=chessboard.board[i/8][i%8];
    switch(piece){
    case 'P':
      result+=100;
      break;
    case 'R':
      result+=500;
      break;
    case 'N':
      result+=300;
      break;
    case 'B':
      bishop_count++;
      break;
    case 'Q':
      result+=900;
      break;
    }
  }
  //Balue of the bishop pair
  if(bishop_count>=2){
    result+=300*bishop_count;
  }
  else{
    result+=250*bishop_count;
  }
  return result;
}
int rate_moveability(){
  return 0;
}
int rate_positional(){
  return 0;
}
