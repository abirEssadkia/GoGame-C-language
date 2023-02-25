#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define BOARD_SIZE 9
#define MAX_INPUT 255

#ifndef __GAME_H__
#define __GAME_H__

   
int board[BOARD_SIZE][BOARD_SIZE];

// piece color
typedef enum Color{
    WHITE,
    BLACK
}Color;
//piece structer has coordinate x and y and a color
typedef struct{
    int x;
    int y;
    Color piece_color;
}Piece;

typedef struct {
    char name[MAX_INPUT];
    Piece * pieces;
    short numberOfPieces;
    unsigned short isReady;
}Player;

void print_menu();
short get_choice();
Player * init_player();
void free_player_pieces(Piece *array , short size);
void free_player(Player* player);
void fill_pieces(Piece* pieces , short size,Color color);
void player_vs_player(Player *player1,Player *player2);
void player_vs_ia();
void print_board();
void init_board();

#endif