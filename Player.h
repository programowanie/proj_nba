#pragma once

#include <vector>
#include <string>
using namespace std;


class Player
{
	string _name;
	int _position; // 1-5, not text values
	int _2p_rate, _2p_perc, _2pm, _2pa;
	int _3p_rate, _3p_perc, _3pm, _3pa;
	int _versFactor;
	int _offFactor, _defFactor; 
	int _points;

	static void initData();

public:
	Player();
	int whichShot();
	string getName() {return _name;}
	int position() {return _position;}
	int getScore();
	int makeTwo(), makeThree();
	string description();
	int matchupFactor();
	string acc_2pt() {
		return to_string(_2pm) + "/" + to_string(_2pa);
	}
	string acc_3pt() {
		return to_string(_3pm) + "/" + to_string(_3pa);
	}
	void affectByMatchup(int arg);
};