// It's rather 5x5 streetball during NBA lockout than regular NBA game.

#include "Player.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int possesions = 0; // Initial match possesions;
	int t_t1 = 0;
	int t_t2 = 0; // Initial teams' score.
	Player teams[2][5]; // Two teams, 5 players each.
	cout << "Witamy w symulatorze meczu 5x5 zawodników NBA!" << endl;
	usleep(2000000);
	cout << "\nZaczynamy! Na boisko wybiegną w 1 drużynie: \n" << endl;
	for(int i=0;i<5;i++) {
		cout << teams[0][i].description() << endl;
		usleep(500000);
	}
	usleep(3000000);
	cout << "\nPo drugiej stronie staną: \n" << endl;
	for(int i=0;i<5;i++) {
		cout << teams[1][i].description() << endl;
		usleep(500000);
	}
	cout << "\nZaczynamy mecz!" << endl;
	while(possesions < 100) {
		int attacker = rand() % 4; // position of attacker
		int defender = rand() % 4; // position of defender
		int posDifference = abs(teams[possesions%2][attacker].position() - teams[1 - possesions%2][defender].position());
		// This determines matchupFactor.
		// If point guard (1) is covered by center (5), or vice versa, the difference between positions is 4.
		// Because comparing PG with C makes no sense, affectByMatchup (function, which decreases attacker's abilities) is 0.
		// Why? I assumed point guard will beat center with his speed, and center will use his strength and height.
		// So - defender wouldn't have any advantage at all.
		// But when positions are similar, better defender can affect attacker's abilities.
		if(teams[1-possesions%2][defender].matchupFactor() >= teams[possesions%2][attacker].matchupFactor()) {
			teams[possesions%2][attacker].affectByMatchup(10 - posDifference);
		}
		usleep(100000);
		cout << teams[possesions%2][attacker].getName() << " oraz " << teams[1 - possesions%2][defender].getName() << " naprzeciwko siebie." << endl;
		teams[possesions%2][attacker].whichShot();
		// Return to previous state. Affecting player's abliities by 
		teams[possesions%2][attacker].affectByMatchup(-10 + posDifference); 
		possesions++;
	}
	usleep(3000000);
	cout << "\nNa koniec osiagniecia punktowe zawodnikow druzyny nr 1: \n" << endl;
	for(int i=0;i<5;i++) {
		cout << teams[0][i].getName() << " " << teams[0][i].getScore() << " PKT, " << teams[0][i].acc_2pt() << " 2PT, " << teams[0][i].acc_3pt() << " 3PT" << endl;
		usleep(500000);
		t_t1 += teams[0][i].getScore();
	}
	usleep(3000000);
	cout << "\nI to, jak radzili sobie zawodnicy druzyny nr 2: \n" << endl;
	for(int i=0;i<5;i++) {
		cout << teams[1][i].getName() << " " << teams[1][i].getScore() << " PKT, " << teams[1][i].acc_2pt() << " 2PT, " << teams[1][i].acc_3pt() << " 3PT" << endl;
		usleep(500000);
		t_t2 += teams[1][i].getScore();
	}
	cout << "\nKoncowy wynik to: " << "Druzyna nr 1 " << t_t1 << ":" << t_t2 << " Druzyna nr 2\n";
}