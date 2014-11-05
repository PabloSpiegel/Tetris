#include "tetrismap.h"
#include "timer.h"
#include "tetromino.h"
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
void pon(tetrismap& map){
	cout<<map;
}
void hacer(tetrismap& map,char c){
	switch(c){
		case 'a':
			map.left();
			break;
		case 's':
			map.down(false);
			break;
		case 'd':
			map.right();
			break;
		case 'k':
			map.rotateccw();
			break;
		case 'l':
			map.rotateccw();
			break;
		default:
			break;

	}
}
int main(){
	srand(time(NULL));
	tetrismap map;
	cout<<map;
	char c='o';
	while(c!='9'){
		hacer(map,c=cin.get());
		cout<<map;
	}


}