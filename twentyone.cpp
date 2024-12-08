#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
 // ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Permute the deck of cards, effectively shuffling it.
 * Using the Fisher-Yates / Durstenfeld shuffle algorithm
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  //srand(time(0));
  // rand function 
  for (int i = 51; i > 0; i--) {
    // according to pseudocode, loop beings at n-1, goes to 1
    int j = rand() % (i + 1);
    // j is a random number. Expression used to ensure it is in range 
    int m = cards[i];
    cards[i] = cards[j]; 
    cards[j] = m; 
    // this exchanges a[j] and a[i] 
  }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  string s;
  string t;
  s = type[id % 13];
  // use modulus to determine the type 
  t = suit[id / 13];
  // use regular division to determine the suit 
  cout << s << t; 
  // prints the suit and the type 
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  int v; 
  v = value[id % 13];
  // use modulus to determine the value (like the type)
  return v; 
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  for (int i = 0; i < numCards; i++){
    // loop for the number of cards in the hand 
    printCard(hand[i]);
    // printCard function for i in the hand 
    cout << " ";
    // print space between each card 
  }
  cout << endl; 
  // print new line 
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  int score = 0;
  bool ace = false;
  // set initial value of score to 0
  // create boolean for if there is an ace in the deck (this is important for changing the value)
  for (int i = 0; i < numCards; i++){
    // loop through all cards 
    if ((hand[i] % 13 == 12) && (score + 11 > 21)){
      score++; 
      // if there is an ace and makes the value go above 21, change it to 1 
    }
    else{
      score += cardValue(hand[i]);
      // if not, keep at 11 
    }
    if (hand[i] % 13 == 12){
      ace = true;
      // determine if there is ace 
    }
  }
  if ((ace) && (score > 21)){
    // if there is ace and value above 21 
    score = 0;
    for (int i = 0; i < numCards; i++){
      if (hand[i] % 13 == 12){
        score++;
      }
      else {
        score += cardValue(hand[i]);
      }
    }
    // this loop goes back and changes the previous value of the ace to 1 
  }
  return score; 
  // return the calculated score at the end of the function 
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];

  int dcards = 0; 
  int pcards = 0; 
  int dscore = 0; 
  int pscore = 0; 
  int d_diff = 0; 
  int p_diff = 0; 
  int cardID = 0;
  // declare & assign the variables 


  bool repeat = true; 
  // declare variable for while loop 
  char play; 
  // char that asks to play again 


  while (repeat){
    // while loop that repeats if want to play again 
    for(int i = 0; i < 52; i++){
        cards[i] = i;}
        // initialize cards 

    cardID = 0; 
    dcards = 0; 
    pcards = 0; 
    dscore = 0; 
    pscore = 0; 
    d_diff = 0; 
    p_diff = 0;
    // reassign variables (effective for 2nd run)
    

    shuffle(cards);
    // shuffle cards 


    for (int i = 0; i < 2; i++){
      // for loop that deals two cards to each player 
      phand[pcards] = cards[cardID];
      pcards++; 
      cardID++;
      dhand[dcards] = cards[cardID]; 
      dcards++; 
      cardID++; 
    }



    cout << "Dealer: ? "; 
    printCard(dhand[1]);
    cout << endl;
    // print the dealer's hand but conceal the first card 


    cout << "Player: ";
    printHand(phand, pcards); 
    // print the player's hand 


    pscore = getBestScore(phand, pcards);
    dscore = getBestScore(dhand, dcards);
    // have both scores available

    if (pscore == 21){
      // if player score is 21 from first deal 
      while (dscore < 17){
        dhand[dcards] = cards[cardID]; 
        cardID++;
        dcards++; 
        dscore = getBestScore(dhand, dcards); 
        // allow dealer to play their turn 
      }
      if (dscore != 21){
        cout << "Dealer:";
        printHand(dhand, dcards);
        cout << endl; 
        cout << "Win " << pscore << " " << dscore << endl; 
        // if dealer does not have 21, player wins 
      }
      cout << "Play again? [y/n]"; 
      cin >> play;
      cout << endl;
      if (play == 'y'){
        repeat = true; 
      }
      else {
        break;
        // ask to play again
    }
    }


    cout << "Type 'h' to hit and 's' to stay: "; 
    char move; 
    cin >> move; 
    cout << endl;
    // ask to hit or stay (the first time)


    while (move == 'h'){
      // if player decides to hit 

      phand[pcards] = cards[cardID];
      cardID++;
      pcards ++; 
      pscore = getBestScore(phand, pcards);
      // add card to player's hand 


      cout << "Player:"; 
      printHand(phand, pcards);
      cout << endl;
      // print out player's new hand 

      pscore = getBestScore(phand, pcards); 
      // get player score 

      if (pscore > 21){
        cout << "Player busts" << endl; 
        cout << "Lose " << pscore << " "<< dscore << endl; 
        break;
      }
      // if player busts 

      if (pscore == 21){
        dscore = getBestScore(dhand,dcards); 
      // get dealer score 
        while (dscore < 17){
          dhand[dcards] = cards[cardID]; 
          cardID++;
          dcards++; 
          dscore = getBestScore(dhand, dcards); 
      }
        cout << "Dealer:";
        printHand(dhand, dcards);
        cout << "Win " << pscore << " " << dscore << endl; 
          break;
      }
      // if player has 21, let dealer play




      cout << "Type 'h' to hit and 's' to stay: ";  
      cin >> move; 
      // ask if player wants to hit or stay (to break out of while loop or not)

    }
    // end of hit while loop 



    if (move == 's'){
      // if statement for when player enters s 


      dscore = getBestScore(dhand,dcards); 
      // get dealer score 
      while (dscore < 17){
        dhand[dcards] = cards[cardID]; 
        cardID++;
        dcards++; 
        dscore = getBestScore(dhand, dcards); 
      }
      // dealer plays while it gets to score requirement 



      cout << "Dealer:";
      printHand(dhand, dcards);
      cout << endl; 
      // print dealer's hand 


      pscore = getBestScore(phand, pcards);
      // get player score 


      if (dscore > 21){
        cout << "Dealer busts" << endl; 
        cout << "Win " << pscore << " " << dscore << endl; 
      }
      // if dealer busts 


      else if (pscore > dscore){
        cout << "Win " << pscore << " " << dscore << endl; 
      }
      // if player is closer to 21 than dealer 


      else if (dscore > pscore){
        cout << "Lose " << pscore << " " << dscore << endl;
      }
      // if dealer is closer to 21 than player 


      else if (dscore == pscore){
        cout << "Tie " << pscore << " " << dscore << endl;
      }
      // if the two scores are equal 


      else if (pscore == 21){
        // if player has 21 
        if (dscore == 21){
          cout << "Tie " << pscore << " " << dscore << endl;
          // if dealer also has 21 --> tie 
        }
        else {
          // if dealer does not also have 21 
          cout << "Win " << pscore << " " << dscore << endl;
        }
      }


    }
    // end of s move loop 


    cout << "Play again? [y/n]"; 
    cin >> play;
    cout << endl;
    if (play == 'y'){
      repeat = true; 
    }
    else {
      repeat = false;
    }
    // determine if player wants to play again 


  }
  // end of playing game loop 
    return 0;
}
// end of main 
