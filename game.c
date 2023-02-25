#include "game.h"

void print_menu(){
    printf("------------------GO GAME------------------\n");
    printf("1-Player vs Player.\n");
    printf("2-Player vs IA.\n");
    printf("3-Quit.\n");
}

short get_choice(){
    char choice[MAX_INPUT];
    short integer_input;
    while(TRUE){
        printf("please enter your choice: ");
        scanf("%s",&choice);
        integer_input= atoi(choice);
        if(integer_input==0){
            printf("Invalid input!\n");
        }else{
            break;
        }
    }
    return integer_input;
}

void fill_pieces(Piece *pieces , short size,Color color){
    int i=0;
    for(i=0;i<size;i++){
        pieces[i].piece_color=color;
        pieces[i].x=-1;
        pieces[i].y=-1;
    }
}

//clearing memory
// void free_player(Player* player){
//     free(player);
// }
// void free_player_pieces(Piece *array , short size){
//    free(array);
// }

Player * init_player(){
    srand(time(NULL));
    clean_stdin();
    //reserving an array of 2 players
    Player * players =(Player*)malloc(sizeof(Player)*2);
    //each player has a name
    printf("First player enter your name: ");
    gets(players[0].name); 
    printf("Second player enter your name: ");
    gets(players[1].name); 
    //reserving an array of 40 of pieces for each player
    players[0].pieces = (Piece*)malloc(sizeof(Piece)*40);
    players[1].pieces = (Piece*)malloc(sizeof(Piece)*40);
    players[0].numberOfPieces=40;
    players[1].numberOfPieces=40;
    //generating the color between white or black (white plays first)
    short random = rand()%2;
    if(random ==1){
        printf("%s gets white\n",players[0].name);
        players[0].isReady=TRUE;
        players[1].isReady=FALSE;
        players[0].pieces= (Piece*)malloc(sizeof(Piece)*40);
        players[1].pieces= (Piece*)malloc(sizeof(Piece)*40);
        fill_pieces(players[0].pieces,40,WHITE);
        fill_pieces(players[1].pieces,40,BLACK);

    }else{
        printf("%s gets white\n",players[1].name);
        players[1].isReady=TRUE;
        players[0].isReady=FALSE;
        players[0].pieces= (Piece*)malloc(sizeof(Piece)*40);
        players[1].pieces= (Piece*)malloc(sizeof(Piece)*40);
        fill_pieces(players[0].pieces,40,BLACK);
        fill_pieces(players[1].pieces,40,WHITE);
    }
    clean_stdin();
    return players;
}

void init_board(){
    int i,j=0;
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            board[i][j]=0;
        }
    }
}


int if_occupied(int x,int y){
    if(board[x][y]==1 || board[x][y]==2 || board[x][y]==3){
        return TRUE;
    }else{
        return FALSE;
    }
}
void checkCapturedPieces(int gb[9][9]) 
{ 
    int i=0,j=0;
   // check for white pieces and their edges if its black then the piece is captured
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(gb[i][j]==1){
                if(gb[i+1][j]==2 || gb[i-1][j]==2 || gb[i][j+1]==2 || gb[i][j-1]==2){
                    gb[i][j]=3;
                }
            }
        }
    }
    // check for black pieces and their edges if its white then the piece is captured
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(gb[i][j]==2){
                if(gb[i+1][j]==1 || gb[i-1][j]==1 || gb[i][j+1]==1 || gb[i][j-1]==1){
                    gb[i][j]=3;
                }
            }
        }
    }
   
    
}

void place_piece(Player * player,int pos){
    if(player->pieces>0){
        while(TRUE){
            int x,y;
            printf("enter the x and y: ");
            scanf("%d %d",&x,&y);
            if((x>=0 && x<=9 )&&( y>=0 &&y<=9)){
                if(!if_occupied(x,y)){
                    if(x==9){
                        board[8][y]=pos;
                    }
                    else if(y==9){
                        board[x][8]=pos;
                    }
                    else if(x==9 && y==9){
                        board[8][8]=pos;
                    }
                    else if(x==1){
                        board[0][y]=pos;
                    }
                    else if(y==1){
                        board[x][0]=pos;
                    }
                    else if(x==1 && y==1){
                        board[0][0]=pos;
                    }
                    else if(x==1 && y==9){
                        board[0][8]=pos;
                    }
                    else if(x==9 && y==1){
                        board[8][0]=pos;
                    }
                    else{
                        board[x][y]=pos;
                    }   
                    player->numberOfPieces--;
                    return;
                }else{
                    printf("this position is occupied!\n");
                }
                continue;
            }else{
                printf("please enter valid position!\n");
            }
        }
    }
}
//1 for white and 2 for black
void player_vs_player(Player* first ,Player* second){
    int isOver=FALSE;
    while(!isOver){
        if(first->isReady){
            printf("%s's turn\n",first->name);
            place_piece(first,1);
            first->isReady=FALSE;
            second->isReady=TRUE;
            print_board();
        }else{
            printf("%s's turn\n",second->name);
            place_piece(second,2);
            second->isReady=FALSE;
            first->isReady=TRUE;
            print_board();
        }
        checkCapturedPieces(board);
        isOver = is_board_full();
        
    }
    clear_screen();
    int winner = count_pieces();
    if(winner==1){
        printf("%s wins!\n",first->name);
    }else if(winner==2){
        printf("%s wins!\n",second->name);
    }else{ 
        printf("it's a tie!\n");
    }

}
//clearing the stdin
void clean_stdin()
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//count the number of white and black pieces on the board and return the winner
int count_pieces(){
    int i,j=0;
    int white=0;
    int black=0;
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            if(board[i][j]==1){
                white++;
            }else if(board[i][j]==2){
                black++;
            }
        }
    }
    if(white>black){
        return 1;
    }else if(black>white){
        return 2;
    }else{
        return 0;
    }
}
//player vs ia
void player_vs_ia(){
    clean_stdin();
    Player* player = (Player*)malloc(sizeof(Player));
    Player* ia = (Player*)malloc(sizeof(Player));
    printf("enter your name: ");
    gets(player->name);
    clean_stdin();
    strcpy(ia->name,"Computer");
    player->isReady=TRUE;
    ia->isReady=FALSE;
    player->pieces = (Piece*)malloc(sizeof(Piece)*40);
    ia->pieces = (Piece*)malloc(sizeof(Piece)*40);
    player->numberOfPieces=40;
    ia->numberOfPieces=40;
    fill_pieces(player->pieces,40,WHITE);
    fill_pieces(ia->pieces,40,BLACK);
    int isOver=FALSE;
    while(!isOver){
        if(player->isReady){
            printf("%s's turn \n",player->name);
            place_piece(player,1);
            player->isReady=FALSE;
            ia->isReady=TRUE;
            print_board();
        }else{
            printf("%s's turn \n",ia->name);
            ia_turn(ia);
            ia->isReady=FALSE;
            player->isReady=TRUE;
            print_board();
        }
        checkCapturedPieces(board);
        isOver = is_board_full();
        
    }
    clear_screen();
    int winner = count_pieces();
    if(winner==1){
        printf("%s wins!\n",player->name);
    }else if(winner==2){
        printf("%s wins!\n",ia->name);
    }else{
        printf("it's a tie!\n");
    }
}
//ia turn
void ia_turn(Player* ia){
    srand(time(NULL));
    int x,y;
    while(TRUE){
        x = rand()%9;
        y = rand()%9;
        if(!if_occupied(x,y)){
            board[x][y]=2;
            ia->numberOfPieces--;
            return;
        }
    }
}

//check if the board is full and returns true if it is
int is_board_full(){
    int i,j=0;
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            if(board[i][j] == -1 || board[i][j] == 0 ){
                return FALSE;
            }
        }
    }
    return TRUE;
}



//print the array with borders
void print_board(){
    int i=0,j=0,k=0,l=0;
    printf("+");
    for (k = 0; k < BOARD_SIZE; k++) {
        printf("---+");
    }
    printf("\n");
    for(i=0;i<BOARD_SIZE;i++){
        printf("| ");
        for(j=0;j<BOARD_SIZE;j++){
            if(board[i][j]==-1){
                printf(" | ");
            }else if(board[i][j]==0){
                printf(" | ");
            }else if(board[i][j]==1){
                printf("W | ");
            }else if(board[i][j]==2){
                printf("B | ");
            }else if(board[i][j]==3){
                printf("X | ");
            } 
        }
        printf("\n");
        printf("+");   
        for (l = 0; l < BOARD_SIZE; l++) {
            printf("---+");
        }
        printf("\n");
    }
}
void clear_screen(){
    system("clear"); 
}