#include "../include/chessboard.h"

char Chessboard::board[8][8]=
  {{'r','n','b','q','k','b','n','r'},
   {'p','p','p','p','p','p','p','p'},
   {' ',' ',' ',' ',' ',' ',' ',' '},
   {' ',' ',' ',' ',' ',' ',' ',' '},
   {' ',' ',' ',' ',' ',' ',' ',' '},
   {' ',' ',' ',' ',' ',' ',' ',' '},
   {'P','P','P','P','P','P','P','P'},
   {'R','N','B','Q','K','B','N','R'}};

void Chessboard::show(){
  for(int i=0;i<8;i++){
    std::cout<<"[";
    for(int j=0;j<8;j++){
      std::cout<<board[i][j];
      if(j!=7)
        std::cout<<", ";
    }
    std::cout<<"]\n";
  }
};

//Move format: r1 c1 r2 c2 captured piece
std::string Chessboard::valid_moves(){
  std::string result;
  for(int i=0;i<64;i++){
    switch(board[i/8][i%8]){
    case 'P':
      result+=moves_pawn(i);
      break;
    case 'R':
      result+=moves_rook(i);
      break;
    case 'N':
      result+=moves_knight(i);
      break;
    case 'B':
      result+=moves_bishop(i);
      break;
    case 'Q':
      result+=moves_queen(i);
      break;
    case 'K':
      result+=moves_king(i);
      break;
    }
  }
  return result;
}
std::string Chessboard::moves_pawn(int position){
  int row=position/8,column=position%8;
  std::string result="";
  //Normal movement
  if(row>1 && board[row-1][column]==' '){
    board[row-1][column]='P';
    board[row][column]=' ';
    if(king_safe()){
      result=result+std::to_string(row)+std::to_string(column)+std::to_string(row-1)+std::to_string(column)+' ';
    }
    board[row][column]='P';
    board[row-1][column]=' ';
  }
  //Move two times
  if(row==6 && board[row-1][column]==' ' && board[row-2][column]==' '){
    board[row-2][column]='P';
    board[row][column]=' ';
    if(king_safe()){
      result=result+std::to_string(row)+std::to_string(column)+std::to_string(row-2)+std::to_string(column)+' ';
    }
    board[row][column]='P';
    board[row-2][column]=' ';
  }
  //Capture without en passant and promotion
  for(int i=-1;i<=1;i+=2){
    if(row>1 && is_inside(row-1,column+i) && islower(board[row-1][column+i])){
      char captured=board[row-1][column+i];
      board[row-1][column+i]='P';
      board[row][column]=' ';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row-1)+std::to_string(column+i)+captured;
      }
      board[row][column]='P';
      board[row-1][column+i]=captured;
    }
  }
  //Promotion without capture
  //Format:c1,c2,transformed piece,captured piece,P
  if(row==1 && board[row-1][column]==' '){
    board[row][column]=' ';
    char pieces[]={'R','B','N','Q'};
    for(char c:pieces){
      board[row-1][column]=c;
      if(king_safe()){
        result=result+std::to_string(column)+std::to_string(column)+c+' '+'P';
      }
      board[row][column]='P';
      board[row-1][column]=' ';
    }
  }
  //Promotion with capture
  for(int i=-1;i<=1;i+=2){
    if(row==1 && is_inside(row-1,column+i) && islower(board[row-1][column+i])){
      char captured=board[row-1][column+i];
      board[row][column]=' ';
      char pieces[]={'R','B','N','Q'};
      for(char c:pieces){
        board[row-1][column+i]=c;
        if(king_safe()){
          result=result+std::to_string(column)+std::to_string(column+i)+c+captured+'P';
        }
        board[row][column]='P';
        board[row-1][column+i]=captured;
      }
    }
  }
  //TODO: en passant
  return result;
}

std::string Chessboard::moves_rook(int position){
  std::string result="";
  int row=position/8,column=position%8;
  for(int i=-1;i<=1;i++){
    int temp=1;
    //Vertical movement
    while(is_inside(row+temp*i,column) && board[row+temp*i][column]==' '){
      board[row][column]=' ';
      board[row+temp*i][column]='R';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column)+' ';
      }
      board[row][column]='R';
      board[row+temp*i][column]=' ';
      temp++;
    }
    if(is_inside(row+temp*i,column) && islower(board[row+temp*i][column])){
      char captured=board[row+temp*i][column];
      board[row][column]=' ';
      board[row+temp*i][column]='R';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column)+captured;
      }
      board[row][column]='R';
      board[row+temp*i][column]=captured;
    }

    //Horizontal movement
    temp=1;
    while(is_inside(row,column+temp*i) && board[row][column+temp*i]==' '){
      board[row][column]=' ';
      board[row][column+temp*i]='R';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row)+std::to_string(column+temp*i)+' ';
      }
      board[row][column]='R';
      board[row][column+temp*i]=' ';
      temp++;
    }
    if(is_inside(row,column+temp*i) && islower(board[row][column+temp*i])){
      char captured=board[row][column+temp*i];
      board[row][column]=' ';
      board[row+temp*i][column]='R';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row)+std::to_string(column+temp*i)+captured;
      }
      board[row][column]='R';
      board[row][column+temp*i]=captured;
    }
  }
  return result;
}
std::string Chessboard::moves_knight(int position){
  int row=position/8,column=position%8;
  std::string result="";
  for(int i=-1;i<=1;i+=2){
    for(int j=-1;j<=1;j+=2){
      if(is_inside(row+i,column+2*j) && !isupper(board[row+i][column+2*j])){
        char captured=board[row+i][column+2*j];
        board[row][column]=' ';
        board[row+i][column+2*j]='N';
        if(king_safe()){
          result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+i)+std::to_string(column+2*j)+captured;
        }
        board[row][column]='N';
        board[row+i][column+2*j]=captured;
      }
      if(is_inside(row+2*i,column+j) && !isupper(board[row+2*i][column+j])){
        char captured=board[row+2*i][column+j];
        board[row][column]=' ';
        board[row+2*i][column+j]='N';
        if(king_safe()){
          result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+2*i)+std::to_string(column+j)+captured;
        }
        board[row][column]='N';
        board[row+2*i][column+j]=captured;
      }
    }
  }
  return result;
}

std::string Chessboard::moves_bishop(int position){
  std::string result="";
  int row=position/8,column=position%8;
  for(int i=-1;i<=1;i++){
    int temp=1;
    //top left to bottom right diagonal
    while(is_inside(row+temp*i,column+temp*i) && board[row+temp*i][column+temp*i]==' '){
      board[row][column]=' ';
      board[row+temp*i][column+temp*i]='B';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column+temp*i)+' ';
      }
      board[row][column]='B';
      board[row+temp*i][column+temp*i]=' ';
      temp++;
    }
    if(is_inside(row+temp*i,column+temp*i) && islower(board[row+temp*i][column+temp*i])){
      char captured=board[row+temp*i][column+temp*i];
      board[row][column]=' ';
      board[row+temp*i][column+temp*i]='B';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column+temp*i)+captured;
      }
      board[row][column]='B';
      board[row+temp*i][column+temp*i]=captured;
    }

    //bottom left to bottom right diagona
    temp=1;
    while(is_inside(row-temp*i,column+temp*i) && board[row-temp*i][column+temp*i]==' '){
      board[row-temp*i][column]=' ';
      board[row-temp*i][column+temp*i]='B';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row-temp*i)+std::to_string(column+temp*i)+' ';
      }
      board[row][column]='B';
      board[row-temp*i][column+temp*i]=' ';
      temp++;
    }
    if(is_inside(row-temp*i,column+temp*i) && islower(board[row-temp*i][column+temp*i])){
      char captured=board[row-temp*i][column+temp*i];
      board[row][column]=' ';
      board[row-temp*i][column+temp*i]='B';
      if(king_safe()){
        result=result+std::to_string(row)+std::to_string(column)+std::to_string(row-temp*i)+std::to_string(column+temp*i)+captured;
      }
      board[row][column]='B';
      board[row-temp*i][column+temp*i]=captured;
    }
  }
  return result;
}

std::string Chessboard::moves_queen(int position){
  std::string result="";
  int row=position/8,column=position%8;
  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
      if(i==0 && j==0){
        continue;
      }
      int temp=1;
      while(is_inside(row+temp*i,column+temp*j) && board[row+temp*i][column+temp*j]==' '){
        board[row+temp*i][column+temp*j]='Q';
        board[row][column]=' ';
        if(king_safe()){
          result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column+temp*j)+' ';
        }
        board[row+temp*i][column+temp*j]=' ';
        board[row][column]='Q';
        temp++;
      }
      if(is_inside(row+temp*i,column+temp*j) && islower(board[row+temp*i][column+temp*j])){
        char captured=board[row+temp*i][column+temp*j];
        board[row+temp*i][column+temp*j]='Q';
        board[row][column]=' ';
        if(king_safe()){
          result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+temp*i)+std::to_string(column+temp*j)+captured;
        }
        board[row+temp*i][column+temp*j]=captured;
        board[row][column]='Q';
      }
    }
  }
  return result;
}
std::string Chessboard::moves_king(int position){
  int row=position/8,column=position%8;
  std::string result="";
  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
      if(is_inside(row+i,column+j) &&!isupper(board[row+i][column+j])){
        char captured=board[row+i][column+j];
        board[row+i][column+j]='K';
        board[row][column]=' ';
        if(king_safe()){
          result=result+std::to_string(row)+std::to_string(column)+std::to_string(row+i)+std::to_string(column+j)+captured;
        }
        board[row+i][column+j]=captured;
        board[row][column]='K';
      }
    }
  }
  return result;
}


bool Chessboard::king_safe(){
  int row=kingPosition/8,column=kingPosition%8;
  //Bishop or queen on the diagonal
  for(int i=-1;i<=1;i+=2){
    int temp=1;
    //Upper left to lower  right diagonal
    while(is_inside(row+temp*i,column+temp*i) && board[row+temp*i][column+temp*i]==' '){
      temp++;
    }
    if(is_inside(row+temp*i,column+temp*i) && (board[row+temp*i][column+temp*i]=='q' || board[row+temp*i][column+temp*i]=='b')){
      return false;
    }
    temp=1;
    //Upper right to lower left diagonal
    while(is_inside(row+temp*i,column-temp*i) && board[row+temp*i][column-temp*i]==' '){
      temp++;
    }
    if(is_inside(row+temp*i,column-temp*i) && (board[row+temp*i][column-temp*i]=='q' || board[row+temp*i][column-temp*i]=='b')){
      return false;
    }
  }

  //Rook or queen in straight lines
  for(int i=-1;i<=1;i+=2){
    int temp=1;
    //Vertical movement
    while(is_inside(row+temp*i,column) && board[row+temp*i][column]==' '){
      temp++;
    }
    if(is_inside(row+temp*i,column) && (board[row+temp*i][column]=='q' || board[row+temp*i][column]=='r')){
      return false;
    }
    temp=1;
    //Horizontal movement
    while(is_inside(row,column+temp*i) && board[row][column+temp*i]==' '){
      temp++;
    }
    if(is_inside(row,column+temp*i) && (board[row][column+temp*i]=='q' || board[row][column+temp*i]=='r')){
      return false;
    }
  }

  //knight
  for(int i=-1;i<=1;i+=2){
    for(int j=-1;j<=1;j+=2){
      if(is_inside(row+i,column+2*j) && board[row+i][column+2*j]=='n'){
        return false;
      }
      if(is_inside(row+2*i,column+j) && board[row+2*i][column+j]=='n'){
        return false;
      }
    }
  }

  //Pawn
  if(is_inside(row-1,column+1) && board[row-1][column+1]=='p'){
    return false;
  }
  if(is_inside(row-1,column-1) && board[row-1][column-1]=='p'){
    return false;
  }

  //The other king
  for(int i=-1;i<1;i++){
    for(int j=-1;j<1;j++){
      if(is_inside(row+i,column+j) && board[row+i][column+j]=='k'){
        return false;
      }
    }
  }

  return true;
}


bool Chessboard::is_inside(int row, int column){
  return row>=0 && row<=7 && column>=0 && column<=7; 
}

void Chessboard::make_move(std::string move){
  //promotion
  if(move[4]=='P'){
    int c1=move[0]-'0';
    int c2=move[1]-'0';
    board[1][c1]=' ';
    board[0][c2]=move[2];
  }
  //Regular movement
  else{
    int r1=move[0]-'0';
    int c1=move[1]-'0';
    int r2=move[2]-'0';
    int c2=move[3]-'0';
    board[r2][c2]=board[r1][c1];
    board[r1][c1]=' ';
  }
}


void Chessboard::undo_move(std::string move){
  //promotion
  if(move[4]=='P'){
    int c1=move[0]-'0';
    int c2=move[1]-'0';
    board[1][c1]='P';
    board[0][c2]=move[3];
  }
  else{
    int r1=move[0]-'0';
    int c1=move[1]-'0';
    int r2=move[2]-'0';
    int c2=move[3]-'0';
    board[r1][c1]=board[r2][c2];
    board[r2][c2]=move[4];
  }
}

void Chessboard::flipboard(){
  for(int i=0;i<32;i++){
    char temp=board[i/8][i%8];
    board[i/8][i%8]=board[(63-i)/8][(63-i)%8];
    board[(63-i)/8][(63-i)%8]=temp;
  }
  for(int i=0;i<64;i++){
    if(board[i/8][i%8]>='A' and board[i/8][i%8]<='Z')
      board[i/8][i%8]=tolower(board[i/8][i%8]);
    else
      board[i/8][i%8]=toupper(board[i/8][i%8]);
      
  }
}
