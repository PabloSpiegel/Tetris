#ifndef TETRISMAP_H
#define TETRISMAP_H
#include <vector>
#include <iostream>
#include "tetromino.h"
#include "timer.h"
#define mododios 0
enum tetris_action{ACT_LEFT,ACT_RIGHT,ACT_DOWN,ACT_CW,ACT_CCW,ACT_SIZE};
const tetris_action & inttoaction(int n);
class tetrismap{
	public:
		std::vector<std::vector<TTR> >m;
		tetromino t;
		tetrismap(unsigned int i=20, unsigned int j=10, bool mon=false);
		TTR randomTTR();
		void put(const tetromino& t);
		void unput(const tetromino& t);
		bool inrank(const tetromino& t);
		bool canput(const tetromino& t);
		void change(TTR ID);

		Timer candown;
		Timer canmove;
		Timer canrotate;
		Timer gravitytimer;

		//Score
		unsigned int lines;
		unsigned int score;
		unsigned int level;


		//Monkey variables
		bool ismonkey;
		bool monkeyactive;
		int droppedtoactivate;
		int ttrdropped;
		Timer monkeytimer;
		bool activatemonkey();

		void dothemonkey();

		bool active;
		void left();
		void right();
		void down(bool gravity);
		void rotatecw();
		void rotateccw();
		bool fullline(int n);
		void makeaction(tetris_action t);
		void monkeyinit(){}
	//public:
		void sendaction(tetris_action t);
		unsigned int colsize()const{
			return m[0].size();
		}
		unsigned int rowsize()const{
			return m.size();
		}
		const TTR & operator()(unsigned int i, unsigned int j)const{
			return m[i][j];
		}
		friend std::ostream & operator <<(std::ostream & os, tetrismap & map);
		void start();
		void stop();
		const bool & getactive(){
			return active;
		}
		const unsigned int & getscore(){
			return score;
		}
};
	std::ostream & operator <<(std::ostream & os, tetrismap & map);

#endif