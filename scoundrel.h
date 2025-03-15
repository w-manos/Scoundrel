//
//  scoundrel.h
//  Scoundrel
//
//  Created by William Manos on 2/16/25.
//

#ifndef scoundrel_h
#define scoundrel_h

//include libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//prototypes for functions
void InitializeDeck(int deck[44][2]);
void ShuffleDeck(int deck[44][2]);
void fight(int * health, int * weaponStrength, int * weaponMax, int monsterStrength);
void PickupWeapon(int * weaponStrength, int * weaponMax, int newWeaponStrength);
void heal(int *health, int healamount);
void PrintStats(int * health, int * weaponStrength, int * weaponMax);
void DrawCards(int tableau[4][2], int deck[44][2], int cardsToDraw, int * cardsInTableau, int * deckSize);
void PrintTableau(int tableau[4][2], int cardsInTableau, int runawayMeter);
void SelectAction(int tableau[4][2], int * cardsInTableau, int nextAction[], int * runawayMeter);
void DoAction(int nextAction[2], int * health, int * weaponMax, int * weaponStrength, int * deckSize, int deck [44][2], int tableau[4][2], int * cardsInTableau, int * runawayMeter);
void EndGame(int health, int * deckSize);
void RunAway(int * deckSize, int deck [44][2], int tableau[4][2], int * cardsInTableau, int * runawayMeter);

#endif
