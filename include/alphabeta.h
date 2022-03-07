#pragma once
#include<string>
#include<algorithm>
#include<iostream>
#include<climits>
#include "./rating.h"
#include "chessboard.h"

int alphabeta(int depth,int alpha,int beta,int player,std::string &move);
