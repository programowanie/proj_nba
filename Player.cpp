// Class definition.
#include "Player.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

vector <string> players;

using namespace std;

void Player::initData() {
	string row;
	ifstream file("names.csv");
	while(getline(file, row)) {
		players.push_back(row);
	}
}

int randomValue() {
	return rand() % 60 + 20;
}

//Constructor

Player::Player() {

	static int amountOfPlayers = (initData(), players.size());
	_name = players[rand() % amountOfPlayers + 1];
	_points = 0; // Initial value;
	_3pm = 0;
	_3pa = 0;
	_2pa = 0;
	_2pm = 0;
	_versFactor = randomValue();
	_position = rand() % 5 + 1;
	_offFactor = randomValue();
	_defFactor = randomValue();
	_3p_perc = randomValue();
	_3p_rate = randomValue();
	_2p_perc = randomValue();
	_2p_rate = 100 - _3p_rate;

}

string Player::description() {
	return _name + "\nPosition: " + to_string(_position) + "\nVersatility: " + to_string(_versFactor) + " OFF: " + to_string(_offFactor) +
	" DEF: " + to_string(_defFactor) + " 3P%: " + to_string(_3p_perc) + " 3PR: " + to_string(_3p_rate) +
	" 2P%: " + to_string(_2p_perc) + " 2PR: " + to_string(_2p_rate);
}

int Player::whichShot() {
	if(randomValue() < _3p_rate) {
		makeThree();
	}
	else {
		makeTwo();
	}
}

int Player::makeThree() {
	_3pa +=1;
	if(randomValue() < (_3p_perc+_offFactor+_versFactor)/3) {
		cout << _name << " probuje rzutu za 3... Trafia!" << endl;
		_points += 3;
		cout << _name << " zapisuje kolejne punkty, jest ich juz " << _points << endl;
		_3pm +=1;
	}
	else
	{
		cout << _name << " rzuca z dystansu! Nieudana proba za 3." << endl;
	}
}

int Player::makeTwo() {
	_2pa +=1;
	if(randomValue() < (_2p_perc+_offFactor+_versFactor)/3) {
		cout << _name << " rzuca z blizszej odleglosci. Trafia za 2!" << endl;
		_points += 2;
		cout << "Ma juz " << _points << " punktow na swoim koncie." << endl;
		_2pm +=1;
	}
	else
	{
		cout << _name << " oddaje rzut z bliska. Niestety, pudlo!" << endl;
	}
}

int Player::getScore() {
	return _points;
}

int Player::matchupFactor() {
	return (((_offFactor+_defFactor)/2)*(_versFactor/10));
}

void Player::affectByMatchup(int arg) {
	_2p_perc -= arg;
	_2p_rate += arg;
	_3p_perc -= arg;
	_3p_rate -= arg;
}