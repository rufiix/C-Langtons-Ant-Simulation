#ifndef _BOARD_H
#define _BOARD_H

int**create_board(int m,int n);
void destroy_board(int**board,int m);
void save_board(int**board,int m,int n,Ant*ant, int k);

#endif
