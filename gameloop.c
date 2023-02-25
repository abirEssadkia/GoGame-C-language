#include "game.c"

int main(){
    while(TRUE){
        short choice;
        print_menu();
        choice = get_choice();
        switch(choice){
            case 1: ;
                Player* arr;
                arr = init_player();
                player_vs_player(&arr[0],&arr[1]);
                break;
            case 2:
                player_vs_ia();
                break;
            case 3:
                return 0;
            default:
                printf("please enter a choice between 1 and 3!\n");
                sleep(1);
                clear_screen();
        }
    }
}