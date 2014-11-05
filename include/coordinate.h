#ifndef COORDINATE_H
#define COORDINATE_H

struct coordinate{
	int x;
	int y;
	coordinate(int i=0,int j=0):x(i),y(j){}
	bool operator ==(coordinate &c){
		return x==c.x&&y==c.y;
	}
	bool operator !=(coordinate &c){
		return x!=c.x|| y!=c.y;
	}
};
#include <iostream>
std::ostream & operator <<(std::ostream& os, const coordinate& c);



std::istream & operator >>(std::istream& is, coordinate & c);

#endif
