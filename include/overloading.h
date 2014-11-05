#ifndef OVERLOADING_H
#define OVERLOADING_H

#include <vector>
#include <iostream>


template <class T> 
std::ostream & operator << (std::ostream & os,const std::vector<T>& v){
    os<<'{';
    if(v.size()==0){
    	os<<"{}";
    	return os;
    }
    for(unsigned int i=0; i<v.size()-1;i++)
        os<<v[i]<<",";
    os<<v[v.size()-1]<<'}'<<std::endl;
    return os;
}

template <class T>
std::istream & operator >>(std::istream &is,std::vector<T>& v){
	T t;
	std::vector<T> aux;
	char c;
	is>>c;
	while(c!='}'){
		is>>t>>c;
		aux.push_back(t);
	}
	if(!is.fail())
		v=aux;
	return is;
}
#endif
