/*
 * struct.c
 *
 *  Created on: Jan 15, 2016
 *      Author: Dario
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#define maxRow 12
#define maxCol 12


char labyrinth[maxRow][maxCol] =    	  { {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
						       	   	   	    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
										    {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
										    {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '#', '#'},
										    {'#', '.', '.', '.', '.', '#', '.', '#', '.', '#', '.', 'c'},
										    {'#', '.', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
										    {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
									   	    {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
										    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
							   	   	   	    {'#', '.', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#'},
										    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
										    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} };



typedef struct location{
	int i;
	int j;
	int entr;
} t_location ;

t_location entrance_location(t_location*);
t_location first_move(t_location*);
void find_entrance();
void find_entrance_updown();
void print_maze();
int finding_point(int, int, int);
t_location move_up (t_location* current);
t_location move_down(t_location*);
t_location move_left(t_location*);
t_location move_right(t_location*);
t_location evaluate_situation(t_location*);


int main(void)
{

	t_location current;
	print_maze();
	find_entrance();
	entrance_location(&current);
	printf("SIGNAL ENTRATA: %d, %d, %d\n", current.entr, current.i, current.j);
	first_move(&current);
	printf("SIGNAL PRIMA MOSSA: %d, %d, %d\n", current.entr, current.i, current.j);
	int i = current.i;
	int j = current.j;
	do {
		evaluate_situation(&current);
	}
	while (labyrinth[i][j] != 'c');



return 0;
}

void print_maze()
{
	int i, j;
	for(i = 0; i < maxRow; i++){
		for(j = 0; j < maxCol; j++){
			printf("%c  ", labyrinth[i][j]);
		}
		printf("\n\n");
	}

}

void find_entrance ()
{
	int i, j;
	int flag = 0;
	for(j = 0; j < maxCol; j+=maxCol - 1){
		for(i = 0; i < maxRow; i++){
			finding_point(flag, i, j);

		}
	}
	if(flag == 0) {
		find_entrance_updown();
	}
}

void find_entrance_updown (int flag) // still to implement case in which there's no entrance
{                                    // just need to make findentranceupdown output flag0 and create an if(no entrance)
	int i, j;
	for(i = 0; i < maxRow; i+=11){
			for(j = 0; j < maxCol; j++){
				finding_point(flag, i, j);
		}
	}

}

int finding_point (int flag, int i, int j)
{

	if(labyrinth[i][j] == '.') {
						printf("Found the entrance\n");
						labyrinth[i][j] = 'X';
						flag++;
						print_maze();
				}
return flag;
}

t_location first_move(t_location* current)
{

	printf("%d %d %d\n", current->i, current->j, current->entr);

	if(current->entr == 1){
		move_down(current);
	}
	else if(current->entr == 2){
		move_up(current);
	}
	else if(current->entr == 3){
		move_right(current);
	}
	else if(current->entr == 4){
		move_left(current);
	}
	return *current;
}






t_location entrance_location (t_location *current)
{

	int i, j;
	for( i = 0; i < maxRow; i++) {
		for( j = 0; j < maxCol; j++){
			if(labyrinth[i][j] == 'X'){
				current->i = i;
				current->j = j;
				//questo printf mi assicura che current è up to date: printf("%d, %d, %d", current.i, current.j, current.entr);
				printf("Entrance coord:%d, %d\n", current->i ,current->j);
				if(labyrinth[0][j] == 'X'){ //sopra
					current->entr = 1;
				}
				else if (labyrinth[11][j] == 'X'){ //sotto
					current->entr = 2;
				}
				else if( labyrinth[i][0] == 'X'){ //sinistra
					current->entr = 3;
				}
				else if(labyrinth[i][11] == 'X'){  //destra
					current->entr = 4;
				}
			}
		}
	}
return *current;
}


t_location move_up(t_location* current)  //devo ricordarmi di settare gli indici all'entrata prima di lanciare move_up
{
		int i = current->i;
		int j = current->j;
		if(labyrinth[i - 1][j] == '.'){
			labyrinth[i - 1][j] = 'X';
			print_maze();
			current->i = i - 1;
		}
	return *current;
}

t_location move_down(t_location* current)  //devo ricordarmi di settare gli indici all'entrata prima di lanciare move_up
{
	int i = current->i;
	int j = current->j;
	if(labyrinth[i + 1][j] == '.'){
		labyrinth[i + 1][j] = 'X';
		print_maze();
		current->i = i + 1;
	}
	return *current;
}

t_location move_right(t_location* current)  //devo ricordarmi di settare gli indici all'entrata prima di lanciare move_up
{
	int i = current->i;
	int j = current->j;
	if(labyrinth[i][j + 1] == '.'){
		labyrinth[i][j + 1] = 'X';
		print_maze();
		current->j = j + 1;
		printf("SIGNAL MOVE RIGHT: %d, %d, %d\n", current->entr, current->i, current->j);
	} //adesso deve controllare che sia possibile il movimento a destra
	return *current;
}

t_location move_left(t_location* current)  //devo ricordarmi di settare gli indici all'entrata prima di lanciare move_up
{
	int i = current->i;
	int j = current->j;
	if(labyrinth[i][j - 1] == '.'){
		labyrinth[i][j - 1] = 'X';
		print_maze();
		current->j = j - 1;
	} //adesso deve controllare che sia possibile il movimento a destra
	return *current;
}



t_location evaluate_situation(t_location* current)
{
	int i = current->i;
	int j = current->j;

	if(labyrinth[i][j] == 'c') {
		printf("Exit Found\n");
	}
	else {
		if(labyrinth[i][j - 1] == 'X' ){ //DA SX VERSO DX
			if(labyrinth[i + 1][j] == '#'){
				if(labyrinth[i][j + 1] == '#'){
					move_up(current);
					//evaluate_situation(current);
				}
				else {
					move_right(current);
					//evaluate_situation(current);
				}
			}
			else {
				move_down(current);
				//evaluate_situation(current);
			}
		}

		else if(labyrinth[i][j + 1] == 'X'){ //DA DX VERSO SX
			if(labyrinth[i - 1][j] == '#'){
				if(labyrinth[i][j - 1] == '#'){
					move_down(current);
					//evaluate_situation(current);
				}
				else {
					move_left(current);
					//evaluate_situation(current);
				}
			}
			else {
				move_up(current);
				//evaluate_situation(current);
			}
		}
		else if(labyrinth[i - 1][j] == 'X'){
			if(labyrinth[i][j - 1] == '#'){
				if(labyrinth[i + 1][j] == '#'){
					move_right(current);
					//evaluate_situation(current);
				}
				else {
					move_down(current);
					//evaluate_situation(current);
				}
			}
			else {
				move_left(current);
				//evaluate_situation(current);
			}
		}
		else if(labyrinth[i + 1][j] == 'X'){
			if(labyrinth[i][j + 1] == '#'){
				if(labyrinth[i - 1][j] == '#'){
					move_left(current);
					//evaluate_situation(current);
				}
				else {
					move_up(current);
					//evaluate_situation(current);
				}
			}
			else {
				move_right(current);
				//evaluate_situation(current);
			}
		}
		//else if(){
		//}
		//}
	}
return *current;
}









	/*if((labyrinth[i+1][j] == 'X') && (labyrinth[i-1][j] == '.') && (labyrinth[i-1][j+1] == '.')){ //ricordati il caso in cui trova C
			move_up(current);
			move_right(current);
	}
	else if((labyrinth[i+1][j] == 'X') && (labyrinth[i-1][j] == '.') && ( labyrinth[i-1][j-1] == '.') && (labyrinth[i-1][j+1] != '.')){
			move_up(current);
			move_left(current);
	}
	else if((labyrinth[i+1][j] == 'X') && (labyrinth[i-1][j-1] == '#') && ( labyrinth[i-1][j+1] == '#')){
			move_up(current);
	}
	//down movements
	else if((labyrinth[i-1][j] == 'X') && (labyrinth[i+1][j] == '.') && (labyrinth[i+1][j-1] == '.')){
			move_down(current);
			move_left(current);
	}
	else if((labyrinth[i-1][j] == 'X') && (labyrinth[i+1][j] == '.') && ( labyrinth[i+1][j+1] == '.') && (labyrinth[i+1][j-1] != '.')){
			move_down(current);
			move_right(current);
	}
	else if((labyrinth[i-1][j] == 'X') && (labyrinth[i+1][j-1] == '#') && ( labyrinth[i+1][j+1] == '#')){
			move_down(current);
	}
	//right movements
	else if((labyrinth[i][j-1] == 'X') && (labyrinth[i][j+1] == '.') && (labyrinth[i+1][j+1] == '.')){
			move_right(current);
			move_down(current);
	}
	else if((labyrinth[i][j-1] == 'X') && (labyrinth[i][j+1] == '.') && ( labyrinth[i-1][j+1] == '.') && (labyrinth[i+1][j+1] == '#')){
			move_right(current);
			move_up(current);
	}
	else if((labyrinth[i][j-1] == 'X') && (labyrinth[i-1][j+1] == '#') && ( labyrinth[i+1][j+1] == '#')){
			move_right(current);
	}
	//left movements
	else if((labyrinth[i][j+1] == 'X') && (labyrinth[i][j-1] == '.') && (labyrinth[i-1][j-1] == '.')){
			move_left(current);
			move_up(current);
	}
	else if((labyrinth[i][j+1] == 'X') && (labyrinth[i][j-1] == '.') && (labyrinth[i+1][j-1] == '.') && (labyrinth[i-1][j-1] == '#')){
			move_left(current);
			move_down(current);
	}
	else if((labyrinth[i][j+1] == 'X') && (labyrinth[i-1][j-1] == '#') && (labyrinth[i+1][j-1] == '#')){
			move_left(current);
	}

	else {(printf("ERRORE\n"));} //NON LO STAMPA QUINDI NON ARRIVA A QUESTO
return current;
}
*/







