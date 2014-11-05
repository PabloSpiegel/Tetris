#ifndef TETROMINO_H
#define TETROMINO_H

#include "coordinate.h"
#include "overloading.h"
#include <vector>
#include <iostream>
enum TTR{TTRO,TTRS,TTRZ,TTRT,TTRJ,TTRL,TTRI,TTRsize};
std::vector<TTR> inttoTTRf();
class tetromino{
	public:
	TTR ID;
	coordinate cbegin;
	std::vector<std::vector<bool> > m;
	tetromino():ID(TTRsize){}
	friend std::istream & operator >>(std::istream & is, tetromino & t);
	friend std::ostream & operator <<(std::ostream & os, tetromino & t);
	friend std::vector<tetromino> setinitials(const char * name);
	const TTR & getID() const{
		return ID;
	}
	const std::vector<std::vector<bool> > & matrix()const{
		return m;
	}
	void change(const TTR &t);
	
	void place(unsigned int length);

	void left();
	void right();
	void down();

	void rotatecw();
	void rotateccw();
	tetromino getccw();
	tetromino getcw();
	tetromino getleft();
	tetromino getright();
	tetromino getdown();
	const coordinate &getbegin()const{
		return cbegin;
	}


};
std::istream & operator >>(std::istream & is, tetromino & t);
std::ostream & operator <<(std::ostream & os, tetromino & t);
TTR inttoTTR(int n);

#endif
