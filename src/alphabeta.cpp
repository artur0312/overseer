#include "../include/alphabeta.h"

int alphabeta(int depth,int alpha,int beta,int player,std::string &move){
  Chessboard board;
  std::string list=board.valid_moves();
  if(depth==0 || list.size()==0){
    return rating(list.size(),depth)*player;
  }
  
  if(player==1){
    int value=INT_MIN;
    for(int i=0;i<list.size()/5;i++){
      board.make_move(list.substr(5*i,5));
      board.flipboard();
      value=std::max(value,alphabeta(depth-1,alpha,beta,-player,move));
      board.flipboard();
      board.undo_move(list.substr(5*i,5));
      if(value>=beta){
        break;
      }
      alpha=std::max(alpha,value);
      if(depth==4 && value==alpha){
        move=list.substr(5*i,5);
      }
    }
    return value;
  }
  else{
    int value=INT_MAX;
    for(int i=0;i<list.size()/5;i++){
      board.make_move(list.substr(5*i,5));
      board.flipboard();
      value=std::min(value,alphabeta(depth-1,alpha,beta,-player,move));
      board.flipboard();
      board.undo_move(list.substr(5*i,5));
      if(value<=alpha){
        break;
      }
    }
    return value;
  }
}
