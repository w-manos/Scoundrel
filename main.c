//
//  main.c
//  Scoundrel
//
//  Created by William Manos on 2/16/25.
//
#include "scoundrel.h"

int main(int argc, const char * argv[]) {
    int deck[44][2];
    int health = 20;
    int weaponStrength = 0;
    int weaponMax = 0;
    int tableau[4][2];
    int cardsInTableau = 0;
    int nextAction[2];
    int deckSize = 44;
    int runawayMeter = 0;
    
    
    //Build the shuffled deck and starting tableau
    InitializeDeck(deck);
    ShuffleDeck(deck);
    DrawCards(tableau, deck, 4, &cardsInTableau, &deckSize);
    
    
    
    
    
    while(health > 0){
        //loop through consistently until the end of the game
        if (cardsInTableau==1 || cardsInTableau == 0){
            DrawCards(tableau, deck, 4 - cardsInTableau, &cardsInTableau, &deckSize);
        }
        PrintStats(&health, &weaponStrength, &weaponMax);
        SelectAction(tableau, &cardsInTableau, nextAction, &runawayMeter);
        DoAction(nextAction, &health, &weaponMax, &weaponStrength, &deckSize, deck, tableau, &cardsInTableau, &runawayMeter);
        
        if(deckSize == 0 && cardsInTableau == 0){
            break;
        }
    }
     
    EndGame(health, &deckSize);
    return 0;
}

