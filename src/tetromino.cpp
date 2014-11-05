#include "tetromino.h"
#include "overloading.h"
#include <iostream>
#include <fstream>
#include <vector>

std::vector<TTR> inttoTTRf(){
	std::vector<TTR> aux(TTRsize);
	aux[0]=TTRO;
	aux[1]=TTRS;
	aux[2]=TTRZ;
	aux[3]=TTRT;
	aux[4]=TTRJ;
	aux[5]=TTRL;
	aux[6]=TTRI;
	return aux;
}
std::vector<TTR> inttoTTRv=inttoTTRf();
TTR inttoTTR(int n){
	return inttoTTRv[n];
}

std::vector<tetromino> setinitials(const char * name){
	std::ifstream fi(name);
	std::vector<tetromino> aux(TTRsize);
	for(int i=0; i<TTRsize;i++){
		fi>>aux[i];
		aux[i].ID=inttoTTRv[i];
	}
	return aux;

}
std::vector<tetromino> initials=setinitials("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/initials");
std::ostream & operator <<(std::ostream & os, tetromino & t){
	os<<t.m;
	return os;
}
std::istream & operator >>(std::istream & is, tetromino & t){
	std::vector<std::vector<bool> > tmp;
	is>>tmp;
	int actsize=tmp.at(0).size();
	for(int i=1; i<tmp.size();i++){
		if(tmp[i].size()!=actsize){
			is.setstate(std::ios::failbit);
			return is;
		}
	}
	t.m=tmp;
	return is;
}



void tetromino::change(const TTR &t){
	*this=initials[t];
}
void tu(){
	std::cout<<"tutu";
}
void tetromino::rotateccw(){
	std::vector<std::vector<bool> > aux(m);
	if(m.size()==0)
		return;
	if(m.size()!=m[0].size())
		return;
	for(int i=0; i<m.size();i++){
		for(int j=0; j<m[i].size();j++){
			m[i][j]=aux[j][m[i].size()-i-1];
		}
	}
}
void tetromino::rotatecw(){
	std::vector<std::vector<bool> > aux(m);
	if(m.size()==0)
		return;
	if(m.size()!=m[0].size())
		return;
	for(int i=0; i<m.size();i++){
		for(int j=0; j<m[i].size();j++){
			m[i][j]=aux[m[i].size()-j-1][i];
		}
	}
}
tetromino tetromino::getcw(){
	tetromino aux=*this;
	aux.rotatecw();
	return aux;
}

void tetromino::left(){
	cbegin.y--;
}
void tetromino::right(){
	cbegin.y++;
}
void tetromino::down(){
	cbegin.x++;
}
tetromino tetromino::getleft(){
	tetromino aux=*this;
	aux.cbegin.y--;
	return aux;
}
tetromino tetromino::getright(){
	tetromino aux=*this;
	aux.cbegin.y++;
	return aux;
}
tetromino tetromino::getdown(){
	tetromino aux=*this;
	aux.cbegin.x++;
	return aux;
}
tetromino tetromino::getccw(){
	tetromino aux=*this;
	aux.rotateccw();
	return aux;
}
void tetromino::place(unsigned int length){
	cbegin.y=length/2-2;
	cbegin.x=0;
	for(int i=0;i<m.size();i++){
		for(int j=0; j<m[i].size();j++){
			if(m[i][j]){
				cbegin.x-=i;
				return;
			}
		}
	}
	
}

