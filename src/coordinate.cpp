#include "coordinate.h"
std::ostream & operator <<(std::ostream& os, const coordinate& c){
	os<<"("<<c.x<<","<<c.y<<")";
	return os;
}
std::istream & operator >>(std::istream& is, coordinate & c){
	char a;
	coordinate aux;
	is>>a;
	if(a!='('){
		is.setstate(std::ios::failbit);
		return is;
	}
	is>>aux.x>>a;
	if(a!=','){
		is.setstate(std::ios::failbit);
		return is;
	}
	is>>aux.y>>a;
	if(a!=')'){
		is.setstate(std::ios::failbit);
	}
	if(!is.fail()){
		c=aux;
	}
	return is;
}