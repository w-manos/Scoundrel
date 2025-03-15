//
//  scoundrel_functions.c
//  Scoundrel
//
//  Created by William Manos on 2/16/25.
//
#include "scoundrel.h"

void InitializeDeck(int deck[44][2]){
    //loop through and fill out all the values for the deck
    //first index is the value, second is the function.
    int challengeRating;
    fprintf(stdout, "How challenging would you like your run to be? (choose a number from -1 to 3)\n");
    scanf("%d", &challengeRating);
    //Spades and Clubs are enemies to fight, 1, with 13 of each, strength 2-14
    //Diamonds are weapons to fight with, 2, 9 of them, strength 2-10
    //Hearts are health potions to heal, 3, 9 of them, strength 2-10
    for (int cardcount = 0;cardcount < 44;cardcount++){
        if(cardcount < 13){
            deck[cardcount][1] = 1;
            deck[cardcount][0] = cardcount + 2 + challengeRating;
        }
        
        else if (cardcount < 26){
            deck[cardcount][1] = 1;
            deck[cardcount][0] = cardcount - 11 + challengeRating;
        }
        else if(cardcount < 35){
            deck[cardcount][1] = 2;
            deck[cardcount][0] = cardcount - 24 + challengeRating;
        }
        else {
            deck[cardcount][1] = 3;
            deck[cardcount][0] = cardcount - 33 + challengeRating;
        }
    }
    
    
}


void ShuffleDeck(int deck[44][2]){
    //randomize the order of the deck so the game is always different
    
    
    int randomcard;
    int temp[2];
    //seed the random number generator
    time_t t;
    srand((unsigned int) time(&t));
    
    //loop through the deck, choosing a random card, putting it at the last slot
    //then repeating with the remaining cards
    for (int index = 43; index >= 0; index--){
        randomcard = rand() % (index+1);
        temp[0] = deck[randomcard][0];
        temp[1] = deck[randomcard][1];
        deck[randomcard][0] = deck[index][0];
        deck[randomcard][1] = deck[index][1];
        deck[index][0] = temp[0];
        deck[index][1] = temp[1];
    }
}


void fight(int * health, int * weaponStrength, int * weaponMax, int monsterStrength){
    
    //temp variable to store whether a weapon is used
    int weaponUse;
    
    //set the default damage
    int damage = monsterStrength;
    
    //check if a weapon can be used
    if (monsterStrength < *weaponMax){
        
        //check if player wants to use their weapon
        printf("Use weapon? (1 yes, 0 no): ");
        scanf("%d", &weaponUse);
        
        //if they do, update the maximum uses and calculate the damage to be taken
        if (weaponUse == 1){
            damage = monsterStrength - *weaponStrength;
            *weaponMax = monsterStrength;
        }
    }
    //deal damage to player, if any
    if (damage > 0){
        *health = *health - damage;
    }
    
}


void PickupWeapon(int * weaponStrength, int * weaponMax, int newWeaponStrength){
    //reset the max weapon fight, and update the new strength
    *weaponMax = 15;
    *weaponStrength = newWeaponStrength;
}

void heal(int *health, int healamount){
    //heal the player up to the max of 20
    *health = *health + healamount;
    if (*health > 20){
        *health = 20;
    }
}

void PrintStats(int * health, int * weaponStrength, int * weaponMax){
    printf("Health: %d\nWeapon Max: %d\nWeapon Strength: %d\n", *health, *weaponMax, *weaponStrength);
}


void DrawCards(int tableau[4][2], int deck[44][2], int cardsToDraw, int * cardsInTableau, int * deckSize){
    // place the first cards in the deck into the tableau
    for (int index = 0; index < cardsToDraw; index++){
        tableau[3 - index][0] = deck[index][0];
        tableau[3 - index][1] = deck[index][1];
    }
    //move all other cards forward in the deck
    for (int index = 0; index < 44-cardsToDraw;index++){
        deck[index][0] = deck[index+cardsToDraw][0];
        deck[index][1] = deck[index+cardsToDraw][1];
    }
    //empty out the used cards
    for (int index = 44; index > 44 - cardsToDraw;index--){
        deck[index][0] = 0;
        deck[index][1] = 0;
    }
    *cardsInTableau = *cardsInTableau + cardsToDraw;
    *deckSize = *deckSize - cardsToDraw;
}


void PrintTableau(int tableau[4][2], int cardsInTableau, int runawayMeter){
    printf("\nThere remains ");
    for (int index = 0; index < cardsInTableau; index++){
        if (tableau[index][1] == 1){
            printf("\n%d. An enemy with %d strength, ", index+1, tableau[index][0]);
        }
        else if (tableau[index][1] == 3){
            printf("\n%d; A potion capable of restoring %d health, ", index+1, tableau[index][0]);
        }
        else if (tableau[index][1] == 2){
            printf("\n%d. A weapon of %d strength, ", index+1, tableau[index][0]);
        }
    }
    if (runawayMeter == 0)
    {
        printf("\n5. You can also escape to another room");
        printf("\n");
    }
}

void SelectAction(int tableau[4][2], int * cardsInTableau, int nextAction[2], int * runawayMeter){
    int actionChosen;
    
    PrintTableau(tableau, *cardsInTableau, *runawayMeter);
    
    while(1)
    {
        
        printf("Choose your next move: ");
        scanf("%d", &actionChosen);
        if (actionChosen == 5 && *runawayMeter == 0)
        {
            nextAction[1] = 4;
            break;
        }
        else if(actionChosen > 0 && actionChosen <= *cardsInTableau)
        {
            nextAction[0] = tableau[(actionChosen-1)][0];
            nextAction[1] = tableau[actionChosen-1][1];
            for (int index = actionChosen-1; index < 4; index++){
                tableau[index][0] = tableau[index+1][0];
                tableau[index][1] = tableau[index+1][1];
            }
            (*cardsInTableau)--;
            *runawayMeter = 0;
            break;
        }
        else{
            printf("Invalid choice, Please Try again\n");
        }
    }
}

void DoAction(int nextAction[2], int * health, int * weaponMax, int * weaponStrength, int * deckSize, int deck [44][2], int tableau[4][2], int * cardsInTableau, int * runawayMeter){
    
    
    if (nextAction[1] == 1){
        fight(health, weaponStrength, weaponMax, nextAction[0]);
    }
    else if (nextAction[1] == 2){
        PickupWeapon(weaponStrength, weaponMax, nextAction[0]);
    }
    else if (nextAction[1] == 3){
        heal(health, nextAction[0]);
    }
    else if (nextAction[1] == 4){
        RunAway(deckSize, deck, tableau, cardsInTableau, runawayMeter);
    }
    
}


void EndGame(int health, int * deckSize){
    if (health <= 0){
        printf("\nYou lost! Better luck next time. \n\n");
    }
    else{
        printf("\nYou have reached the end of the Dungeon!\nCongratulations!\n\n");
    }
}

void RunAway(int * deckSize, int deck [44][2], int tableau[4][2], int * cardsInTableau, int * runawayMeter){
    for (int index = *deckSize; index < (*deckSize + *cardsInTableau); index++){
        deck[index][0] = tableau[index-*deckSize][0];
        deck[index][1] = tableau[index-*deckSize][1];
    }
    *deckSize = *deckSize + *cardsInTableau;
    *cardsInTableau = 0;
    *runawayMeter = 1;
}
