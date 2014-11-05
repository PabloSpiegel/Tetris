#include "tetrismap.h"
#include "overloading.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <ctime>



std::ostream & operator <<(std::ostream & os, tetrismap & map){
	os<<map.m;
	return os;
}
void tetrismap::put(const tetromino& t){
	for(int i=0; i<t.matrix().size();i++){
		for(int j=0; j<t.matrix()[i].size();j++){
			if(t.matrix()[i][j] && i+t.getbegin().x>-1)
				m[i+t.getbegin().x][j+t.getbegin().y]=t.getID();
		}
	}
}
void tetrismap::unput(const tetromino& t){
	for(int i=0; i<t.matrix().size();i++){
		for(int j=0; j<t.matrix()[i].size();j++){
			if(t.matrix()[i][j] && i+t.getbegin().x>-1)
				m[i+t.getbegin().x][j+t.getbegin().y]=TTRsize;
		}
	}
}
bool tetrismap::inrank(const tetromino& t){
	for(int i=0; i<t.matrix().size();i++){
		for(int j=0; j<t.matrix()[i].size();j++){
			if(t.matrix()[i][j] && (j+t.getbegin().y<0||j+t.getbegin().y>m[0].size()-1||i+t.getbegin().x>(int)m.size()-1))
				return false;
		}
	}
	return true;
}
bool tetrismap::canput(const tetromino& t){
	if(!inrank(t))
		return false;
	int initvalue=(t.getbegin().x<0?-t.getbegin().x:0);
	for(int i=initvalue; i<t.matrix().size();i++){
		for(int j=0; j<t.matrix()[i].size();j++){
			if(t.matrix()[i][j]&& m[t.getbegin().x+i][t.getbegin().y+j]!=TTRsize)
				return false;
		}
	}
	return true;
}
tetrismap::tetrismap(unsigned int i, unsigned int j,bool mon):m(i,std::vector<TTR>(j,TTRsize)),active(true),
candown(100),canmove(100),canrotate(300),gravitytimer(300),lines(0),score(0),level(1),
ismonkey(mon), monkeyactive(false),ttrdropped(0),monkeytimer(150),droppedtoactivate(rand()%5+10){
			assert(i!=0);
			assert(j!=0);
		}
void tetrismap::change(TTR ID){
	t.change(ID);
	t.place(m[0].size());
	if(!canput(t)){
		active=false;
		return;
	}
	put(t);
	
}
void tetrismap::left(){
	if(!canmove.Probe())
		return;
	unput(t);
	if(canput(t.getleft())){
		t.left();
	}
	put(t);
}
void tetrismap::right(){
	if(!canmove.Probe())
		return;
	unput(t);
	if(canput(t.getright())){
		t.right();
	}
	put(t);
}
void tetrismap::rotatecw(){
	if(!canrotate.Probe())
		return;
	unput(t);
	if(canput(t.getcw())){
		t.rotatecw();
	}
	put(t);
}
void tetrismap::rotateccw(){
	if(!canrotate.Probe())
		return;
	unput(t);
	if(canput(t.getccw())){
		t.rotateccw();
	}
	put(t);
}
int pointsperlines[]={0,100,300,500,800};
//Note: the program will break up if more than 4 lines are cleared.
void tetrismap::down(bool gravity){
	if(!gravity){
		if(!candown.Probe())
			return;
	}	
	unput(t);
	if(canput(t.getdown())){
		t.down();
		put(t);
		return;
	}
		ttrdropped++;
		if(activatemonkey()){
			monkeyactive=true;
			monkeytimer.Start();
		}
		put(t);
		int linescleared=0;
		for(int i=t.getbegin().x;i<m.size();i++){
			if(fullline(i)){
				linescleared++;
				for(int j=i;j>0;j--){
					std::vector<TTR>aux=m[i];
					m[j]=m[j-1];
				}
				m[0]=std::vector<TTR>(m[0].size(),TTRsize);
			}
		}
		if(linescleared>0){
			score+=pointsperlines[linescleared]*level;
		}
		change(randomTTR());
}

std::vector<TTR> bag=inttoTTRf();
TTR tetrismap::randomTTR(){
	#if mododios==0
	TTR retvalue;
	int position=rand()%bag.size();
	retvalue=bag[position];
	bag.erase(bag.begin() + position, bag.begin() + position+1);
	if(bag.size()==0){
		bag=inttoTTRf();
	}
	return retvalue;
	#else
	int n;
	std::cin>>n;
	return inttoTTR(n);
	#endif

}
bool tetrismap::fullline(int n){
	for(int i=0; i<m[n].size();i++){
		if(m[n][i]==TTRsize){
			return false;
		}
	}
	return true;
}
void tetrismap::makeaction(tetris_action t){
	switch(t){
		case ACT_DOWN:
			down(false);
			break;
		case ACT_LEFT:
			left();
			break;
		case ACT_RIGHT:
			right();
			break;
		case ACT_CW:
			rotatecw();
			break;
		case ACT_CCW:
			rotateccw();
			break;
	}
}
void tetrismap::sendaction(tetris_action t){
	if(monkeyactive){
		monkeytimer.Probe();
		dothemonkey();
	}
	else makeaction(t);
	if(gravitytimer.Probe()){
		down(true);
	}
}
std::vector<tetris_action> inttoactionf(){
	std::vector<tetris_action> aux(ACT_SIZE);
	aux[0]=ACT_LEFT;
	aux[1]=ACT_RIGHT;
	aux[2]=ACT_DOWN;
	aux[3]=ACT_CW;
	aux[4]=ACT_CCW;
	return aux;
}
bool tetrismap::activatemonkey(){
	return droppedtoactivate-ttrdropped==0&&ismonkey;
}
std::vector<tetris_action> inttoactionv=inttoactionf();
void tetrismap::dothemonkey(){
	makeaction(inttoactionv[rand()%ACT_SIZE]);
	if(ttrdropped-droppedtoactivate>1){
		monkeyactive=false;
	}
}
const tetris_action & inttoaction(int n){
	return inttoactionv[n];
}
void tetrismap::start(){
	change(randomTTR());
	canrotate.Start();
	canmove.Start();
	candown.Start();
	gravitytimer.Start();
}
void tetrismap::stop(){
	canrotate.Stop();
	canmove.Stop();
	candown.Stop();
	gravitytimer.Stop();
}