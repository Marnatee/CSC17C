/* 
 * File:   main.cpp
 * Author: michael donnelly
 * Project 1 CSC17C - War card game
 * Created on October 28, 2023, 5:16 PM
 */

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <random> // default_random_engine
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <iomanip>
#include <string>
#include "AsciiArt.h"

using namespace std;

void printMap(map<int,float>);
void printQueue(queue<int>);
void printStack(stack<int>);
void prntDeck(int Card[], int SIZE);
void faceDSP (queue<int> &, queue<int> &);
void faceWAR (int);
void WAR(queue<int> &, queue<int> &,stack<int> &, stack<int> &, float &, float &, float &, float &);
void dealDeck(int [], int);
void timeTrack(int);

int main(int argc, char** argv) {

    int Card[52]; // deck
    int SIZE = 52; // size of deck
    int PERLINE=5; // (not used) but would have used it to make skirmishes print nicer
    queue<int> Hand1; // player's hand
    queue<int> Hand2; // ai's hand
    stack<int> WAR1; // player's war stack
    stack<int> WAR2; // ai's war stack
    AsciiArt Art; //display my beautiful art
    Art.INTRO(); // ASCII art

    list<int> choices; // stores menu choices
    float gameNum=0; // tracks # of games played
    
    float tester1=0,tester2=0,tester3=0; // Tracks wars and skirmishes
    float warD=0,warT=0,warQ=0; // tracks double / triple / quad wars
    float warW=0; // tracks wars won
    
    //Maps tracking gameplay stats
    map<int,float> stat1; // total skirmishes fought
    map<int,float> stat2; // p1 skirmishes won
    map<int,float> stat3; // wars fought
    map<int,float> stat4; // double wars fought
    map<int,float> stat5; // triple wars fought
    map<int,float> stat6; // quad wars fought
    map<int,float> stat7; // simulated time game took
    map<int,float> stat8; // wars won
    map<int,float> stat9; // games won
    
    //Force the program to play 1 round first which prevents any bugs when
    //the user asks the game for stats when they haven't played any matches yet
    int x=1;
    //All 5 program options are within this gigantic do-while loop
    do{
        choices.push_back(x); //add choice to list
        
        //Play game
        //Primary gameplay-loop starts here
        if (x==1){
            gameNum+=1;
            dealDeck(Card, 52);
            cout << "Dealing deck..."<<endl<<endl;
            prntDeck(Card,52);

            for (int i=0;i<52;i++){
                if (i>25){
                    //Populate AI's Hand
                    Hand2.push(Card[i]);
                }
                else {
                    //Populate Player's Hand
                    Hand1.push(Card[i]);
                }
            }
            //DEBUG code
            //printQueue(Hand1);
            //printQueue(Hand2);

            tester1=0,tester2=0,tester3=0;
            //warD=0,warT=0,warQ=0;
            cout << "Start Skirmishes!"<<endl;
            while (!Hand1.empty() && !Hand2.empty()){
                //faceDSP outputs this line below but changes card 11/12/13 to J/Q/K
                //cout << Hand1.front() << " vs " << Hand2.front()<<"   ";
                faceDSP(Hand1, Hand2); //Change card 11/12/13 to display as J/Q/K
                //DEBUG code
                //printQueue(Hand1);
                //printQueue(Hand2);
                if (Hand1.front()==Hand2.front()){
                    //both players played the same card = go to WAR!
                    tester1+=1; // count how many times went to WAR
                    cout <<endl<< "WAR!"<<endl;
                    if (Hand1.size()<=4){
                        //If player 1 doesn't have enough cards for war
                        //Then pop all remaining cards in their Hand
                        //Thereby triggering the loss condition
                        cout << "Player 1 only has "<< Hand1.size()-1<<" cards"<<endl;
                        cout << "Player 1 needs 4 cards to go to WAR"<<endl;
                        while (!Hand1.empty()){
                            Hand1.pop();
                            //Debug code
                            //cout << "Hand1 <=3"<<endl;
                        }

                    } else if (Hand2.size()<=4){
                        //If player 2 doesn't have enough cards for war
                        //Then pop all remaining cards in their Hand
                        //Thereby triggering the loss condition
                        cout << "Player 2 only has "<< Hand2.size()-1<<" cards"<<endl;
                        cout << "Player 2 needs 4 cards to go to WAR"<<endl;             
                        while (!Hand2.empty()){
                            Hand2.pop();
                            //Debug code
                            //cout << "Hand2 <=3"<<endl;
                        }
                    } else {
                        //queue<int> Hand1copy(Hand1);
                        //queue<int> Hand2copy(Hand2);

                        //warChecker(Hand1copy,Hand2copy,warD,warT,warQ);
                        //DEBUG code
                        //printQueue(Hand1);
                        //printQueue(Hand2);
                        
                        //Call War function
                        //Send in 2 queues / 2 stacks / 3 tracker variables
                        WAR(Hand1,Hand2,WAR1,WAR2,warD,warT,warQ,warW);
                        
                        //When returning from war, print out player and AI hands
                        //so the user can better track the course of the game
                        cout << "P1 Hand (";
                        cout << setw(2) << Hand1.size() << " cards):";
                        printQueue(Hand1);
                        cout << "P2 Hand (";
                        cout << setw(2) << Hand2.size() << " cards):";
                        printQueue(Hand2);
                        cout << "Back to Skirmishes!"<<endl;                        
                    }
                } else if (Hand1.front()>Hand2.front()){
                    //Player 1 wins skirmish
                    //Player 1 grabs both cards
                    Hand1.push(Hand1.front());
                    Hand1.push(Hand2.front()); // Order actually matters
                    Hand1.pop();
                    Hand2.pop();
                    tester2+=1;
                } else if (Hand1.front()<Hand2.front()){
                    //Player 2 wins skirmish
                    //Player 2 grabs both cards
                    Hand2.push(Hand2.front()); //Order actually matters
                    Hand2.push(Hand1.front());
                    Hand1.pop();
                    Hand2.pop();
                    tester3+=1;
                }
                //DEBUG code
                //printQueue(Hand1);
                //printQueue(Hand2);
                //cout << endl;
            }
            if(!Hand1.empty()){
                //You won
                cout << endl;
                cout << "Player 2 ran out of cards."<<endl;
                cout << "Player 2 forfeits!"<<endl;
                cout << "Player 1 VICTORY!" << endl;
                Art.WIN();
                stat9.emplace(gameNum, 1);
            }
            if(!Hand2.empty()){
                //You lost
                cout <<endl;
                cout << "Player 1 ran out of cards."<<endl;
                cout << "Player 1 forfeits!"<<endl;
                cout << "Player 2 VICTORY!" <<endl;
                Art.LOSS();
                stat9.emplace(gameNum, 0);
            }
            cout << endl;
            //output game stats
            cout << "Skirmishes fought = " << tester2+tester3<<endl;
            cout<< "Player 1 skirmishes won = "<<tester2 << endl;
            cout<< "Player 2 skirmishes won = "<<tester3<< endl;
            cout << endl;
            cout << "Wars fought = " <<tester1 << endl;
            cout << "Wars won = " << warW<<endl;
            cout << "Double Wars fought = "<< warD<<endl;
            cout << "Triple Wars fought = "<< warT<<endl;
            cout << "Quad Wars fought = "<<warQ<<endl;
            float TimeInSeconds=0;
            TimeInSeconds=tester1*6+tester2*1.5+tester3*1.5;
            timeTrack(TimeInSeconds); // output the time 
            float temp = tester3+tester2;
            //Add all stats to 8 Maps with the KEY value being the Game#
            stat1.emplace(gameNum, temp);
            stat2.emplace(gameNum, tester2);
            stat3.emplace(gameNum, tester1);
            stat4.emplace(gameNum, warD);
            stat5.emplace(gameNum, warT);
            stat6.emplace(gameNum, warQ);
            stat7.emplace(gameNum, TimeInSeconds);
            stat8.emplace(gameNum, warW);
            
            //Reset all counter variables
            //(possibly extraneous, just making sure)
            tester1=0;
            tester2=0;
            tester3=0;
            warD=0,warT=0,warQ=0,warW=0;
            
            //Delete contents of player hand
            while(!Hand1.empty()){
                Hand1.pop();
            }
            
            //Delete contents of AI hand
            while(!Hand2.empty()){
                Hand2.pop();
            }
            
            //Delete contents of player war stack
            while(!WAR1.empty()){
                WAR1.pop();
            }
            
            //Delete contents of ai war stack
            while(!WAR2.empty()){
                WAR2.pop();
            }
        }
        
        //Game stats (lookup specific game)
        if (x==2){
            int temp=0;
            //Ask user to input the key value that will be used to search stats
            cout <<endl<< "Input value from 1 to "<<gameNum<<endl;
            cin >> temp;
            //Force user to only input int from 1 to [amount of games played]
            while (temp <1 || temp > gameNum){
                cout << "Invalid input. Please input number from 1 to "<< gameNum<<endl;
                cin >> temp;
            }
            //output data from the chosen KEY from my 7 maps that track data
            cout << endl;
            cout << "GAME "<<temp<< " ";
            if (stat9[temp]==1)cout << "WIN";
            if (stat9[temp]==0)cout << "LOSS";
            cout << endl<<"Total skirmishes = "<< stat1[temp]<<endl;
            cout << "Player 1 skirmishes won = "<< stat2[temp]<<endl;
            cout << "Wars fought = "<<stat3[temp]<<endl;
            cout << "Wars won = "<<stat8[temp]<<endl;
            cout << "Double wars = "<<stat4[temp]<<endl;
            cout << "Triple wars = "<<stat5[temp]<<endl;
            cout << "Quad wars = "<<stat6[temp]<<endl;
            timeTrack(stat7[temp]);                               
        }
        
        //Game stats (print all)
        if (x==3){
            cout << endl;
            Art.STAT();
            cout << endl;
            //output data from the 7 maps that track data for this game
            for (int i=1;i<gameNum+1;i++){
                cout << "GAME "<<i<< " ";
                if (stat9[i]==1)cout << "WIN";
                if (stat9[i]==0)cout << "LOSS";                
                cout <<endl<< "Total skirmishes = "<< stat1[i]<<endl;
                cout << "Player 1 skirmishes won = "<< stat2[i]<<endl;
                cout << "Wars fought = "<<stat3[i]<<endl;
                cout << "Wars won = " <<stat8[i]<<endl;
                cout << "Double wars = "<<stat4[i]<<endl;
                cout << "Triple wars = "<<stat5[i]<<endl;
                cout << "Quad wars = "<<stat6[i]<<endl;
                timeTrack(stat7[i]);
                cout << endl;
            }
            //declare counters
            int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;
            int temp7=0,temp8=0,temp9=0;
            //going to sum up every map's contents
            for (int i=1;i<gameNum+1;i++){
                temp1+=stat1[i];
                temp2+=stat2[i];
                temp3+=stat3[i];
                temp4+=stat4[i];
                temp5+=stat5[i];
                temp6+=stat6[i];
                temp7+=stat7[i];
                temp8+=stat8[i];
                temp9+=stat9[i];                
            }
            cout << endl << "TOTAL STATS FROM ALL "<<gameNum<< " GAMES"<<endl;
            //total games + skirmishes + wars won out of a total
            cout << "You won " << temp9 << " games out of " << gameNum<< " total"<<endl;
            cout << "You won " << temp2 << " skirmishes out of " << temp1 << " total"<<endl;
            cout << "You won " << temp8 << " WARs out of " << temp3+temp4+temp5+temp6 << " total"<<endl;
            //double war
            if (temp4==0)cout << "No Double Wars"<<endl;
            else cout << temp4<< " Double Wars"<<endl;
            //triple war
            if (temp5==0)cout << "No Triple Wars"<<endl;
            else cout << temp5<< " Triple Wars"<<endl;
            //quad war
            if (temp6==0)cout << "No Quad Wars"<<endl;
            else cout << temp6<< " Quad Wars"<<endl;
            //timeTrack(stat7[i]);
            cout << "Total ";
            timeTrack(temp7);
            
            cout << endl;
            //DEBUG code
            //printMap(stat1);
            //printMap(stat2);
            //printMap(stat3);
            //printMap(stat4);
            //printMap(stat5);
            //printMap(stat6);
            //printMap(stat7);            
        }
        
        //Show previous menu choices
        if (x==4){
            cout << endl;
            cout << "You selected these choices"<<endl;
            for (auto v : choices){
                cout << v << ", ";
            }
            cout << endl;
        }
        
        //Exit the program
        if (x==5){
            cout << endl<< "Exiting program. Goodbye."<<endl;
            Art.EXIT();
            exit(0);
        }
        
        cout << endl;
        cout << "MENU - Choose input 1-5"<<endl;
        cout << "(last option picked = "<<choices.back()<<")"<<endl;
        cout << "1 = play again"<<endl;
        cout << "2 = Stats (specific match)"<<endl;
        cout << "3 = Stats (all matches)"<<endl;
        cout << "4 = See previous menu choices"<<endl;
        cout << "5 = EXIT"<<endl;
        cin >> x;
        if (x < 1 || x > 5){
            cout << "Please input a number 1-5"<<endl;
        }
    }
    while(true);
    //while(cin>>x);
    cout << endl;

    return 0;
}

void printMap(map<int,float> m){
    //Output entire map contents for debugging purposes
    for(auto it = m.cbegin(); it != m.cend(); ++it){
        cout << "Game "<< it->first << ": "<< it->second<<endl;
    }
}

void printQueue(queue<int> q){
    //print any queue container of ints
    while (!q.empty()){
        cout << setw(3);
        //force 11/12/13 to become J/Q/K
        faceWAR(q.front());
        cout<< " ";
        q.pop();
    }
    cout << endl;
}

void printStack(stack<int> s){
    //print any stack container of ints
    while (!s.empty()){
        cout << setw(3);
        //force 11/12/13 to become J/Q/K
        faceWAR(s.top());
        cout<< " ";
        s.pop();
    }
    cout << endl;
}

void prntDeck(int Card[], int SIZE){
    float dtotal1=0,dtotal2=0,dtotal3=0;
    //Print the deck and then analyze your hand
    cout << "Player 1's Hand (YOU)" << endl;
    for (int i=0;i<52;i++){
        cout << setw(3);
        faceWAR(Card[i]); //Display J/Q/K instead of 11/12/13
        cout  << " ";
        dtotal3+=Card[i];
        if (i==25)cout<<endl<<"Player 2's Hand (AI)"<<endl;
        if (i>25){
            dtotal2+=Card[i];
            //cout << " ";
        }
        else dtotal1+=Card[i];
    }
    cout << endl<<endl;
    //cout << dtotal1 << " " <<dtotal2 << " "<< dtotal3 << endl<<endl;
    //cout << "Dealt "<<dtotal1 << " out of " << dtotal3 << " = " << dtotal1/dtotal3*100 << "%"<<endl;
    cout << "Analyzing Your HAND:"<<endl;
    cout << "Worst Hand total =  98"<<endl;
    cout << " Best Hand total = 266"<<endl;
    cout << " Your Hand total = " << dtotal1 << endl;
    //STL count() to find how many J/Q/K cards the player has
    int count11=0,count12=0,count13=0;
    count11 = count(Card,Card+26,11); // Jacks
    count12 = count(Card,Card+26,12); // Queens
    count13 = count(Card,Card+26,13); // Kings
    cout << "You have "<<count11<<" J's  "<<count12<< " Q's  "<<count13<<" K's"<<endl;
    //This tells the player how good of a hand they got from 98-266
    cout << "You are " << (dtotal1-98)/168*100<< "% favored to win"<< endl; 
    cout << endl;
}

void WAR(queue<int> &q1, queue<int> &q2, stack<int> &s1, stack<int> &s2, float &w2, float &w3, float &w4, float &w5){
    //Declaring this here so I can make cool ASCII art appear
    AsciiArt Art2;
    
    //Add the extra card into stack from each player's queue that triggered the initial war
    if (s1.size()==0){
        s1.push(q1.front());
        q1.pop();
        s2.push(q2.front());
        q2.pop();
    }
    //Add the initial 4 war cards for each player to the stack
    for (int i=0;i<4;i++){
        s1.push(q1.front());
        q1.pop();
        s2.push(q2.front());
        q2.pop();
    }
    int sizeSTACK=s1.size();
    int n1=s1.top(), n2=s2.top();
    
    if (sizeSTACK==5){
        //Normal war = 4 cards + 1 card from initial war triggering = 5
        cout << "Player 1 lays down 4 cards with >";
        faceWAR(n1);
        cout << "< faceup"<<endl<< "Player 2 lays down 4 cards with >";
        faceWAR(n2);
        cout << "< faceup"<<endl;
    }
    if (sizeSTACK==9){
        //Detect if double war recursion has successfully occurred
        //w2+=1;
        cout << "Double war has been declared!"<<endl;
        Art2.TWO();
        cout << "Each player lays down 4 more cards again for a total of 16+2 cards"<<endl;
                      
        cout << "Player 1 top card = ";
        faceWAR(n1);
        cout<<endl<< "Player 2 top card = ";
        faceWAR(n2);
        cout<<endl;
    }
    if (sizeSTACK==13){
        //Detect if triple war recursion has successfully occurred
        //w3+=1;
        cout << "Triple war has been declared!"<<endl;
        Art2.THREE();
        cout << "Each player lays down 4 more cards again for a total of 24+2 cards"<<endl;
                      
        cout << "Player 1 top card = ";
        faceWAR(n1);
        cout << endl<< "Player 2 top card = ";
        faceWAR(n2);
        cout<<endl;        
    }
    if (sizeSTACK==17){
        //Detect if quad war recursion has successfully occurred
        //w4+=1;
        cout << "Quadrouple war has been declared!"<<endl;
        Art2.FOUR();
        cout << "Each player lays down 4 more cards again for a total of 32+2 cards"<<endl;
        
        cout << "Player 1 top card = ";
        faceWAR(n1);
        cout << endl<< "Player 2 top card = ";
        faceWAR(n2);
        cout <<endl;
    }
    
    //DEBUG CODE
    //cout << "print stack WAR1"<<endl;
    //printStack(s1);
    //cout << "print stack WAR2"<<endl;
    //printStack(s2);
    //cout << "Size of Stack = " << sizeSTACK<<endl;
    //cout << s1.top()<<" vs " << s2.top()<<endl;
    if (s1.top()>s2.top()){
        w5+=1;
        cout << "Player 1 gains "<<sizeSTACK<<" cards!"<<endl;
        cout << "Player 2 loses "<<sizeSTACK<<" cards!"<<endl;
        cout << endl;
        //cout << "Back to Skirmishes!"<<endl;
        //add 8 cards to Hand1 queue from WAR stack
        //adds 16 if double war
        //adds 24 if triple war
        //adds 32 if quad war
        for (int i=0;i<sizeSTACK;i++){
            q1.push(s1.top());
            s1.pop();
        }
        for (int i=0;i<sizeSTACK;i++){
            q1.push(s2.top());
            s2.pop();
        }
        //printQueue(q1);
        //printQueue(q2);
    } else if (s1.top()<s2.top()){
        cout << "Player 2 gains "<<sizeSTACK<<" cards!"<<endl;
        cout << "Player 1 loses "<<sizeSTACK<<" cards!"<<endl;
        cout << endl;
        //cout << "Back to Skirmishes!"<<endl;
        //add 8 cards to Hand2 queue from WAR stack
        //adds 16 cards if double war
        //adds 24 if triple war
        //adds 32 if quad war
        for (int i=0;i<sizeSTACK;i++){
            q2.push(s2.top());
            s2.pop();
        }
        for (int i=0;i<sizeSTACK;i++){
            q2.push(s1.top());
            s1.pop();
        }
        //printQueue(q1);
        //printQueue(q2);
    } else if (s1.top()==s2.top()){
        //This recursively calls the war function again
        //and makes the stack size increase by 4 each
        cout <<endl<< "STALEMATE!" << endl;
        
        //double triple quad war counters
        switch (sizeSTACK){
            case 5:
                w2+=1; //double war counter
                break;
            case 9:
                w3+=1; //triple war counter
                break;
            case 13:
                w4+=1; //quad war counter
                break;
        }
        //Check if either player has enough cards for another war
        if (q1.size()<4){
            cout << "Player 1 does not have enough cards to continue"<<endl;
            for (int i=0;i<sizeSTACK;i++){
                q2.push(s2.top());
                s2.pop();
            }
            for (int i=0;i<sizeSTACK;i++){
                q2.push(s1.top());
                s1.pop();
            }
        }
        else if (q2.size()<4){
            cout << "Player 2 does not have enough cards to continue"<<endl;
            for (int i=0;i<sizeSTACK;i++){
                q1.push(s1.top());
                s1.pop();
            }
            for (int i=0;i<sizeSTACK;i++){
                q1.push(s2.top());
                s2.pop();
            }            
        }   
        else{
            cout<<"ANOTHER WAR!"<<endl<<endl; 
            //w2+=1;
            //RECURSION WAR function
            //Sending in queue1/2 stack1/2 and my 3 counter variables
            WAR(q1,q2,s1,s2,w2,w3,w4,w5);
        }
    }
    return ;
}

void dealDeck(int Card[], int SIZE){
    //Use a Set containing all cards 1<->13 to populate the deck
    //Then shuffle it twice
    set<int> deckDeal;
    for (int i=0;i<13;i++){
        deckDeal.insert(i+1);
    }

    //Iterate through my Set and add it to Card[1-52]
    for (int i: deckDeal){
        Card[i-1]=i;
        Card[i+12]=i;
        Card[i+25]=i;
        Card[i+38]=i;
    }

    //shuffle twice with Knuth-Shuffle Engine
    //Knuth_b is supposed to be good for card shuffling
    shuffle(Card, Card+SIZE, knuth_b(time(NULL)));
    shuffle(Card, Card+SIZE, knuth_b(time(NULL)));
    
    //Just trying to include the Copy() STL function
    int copyCard[52];
    copy(Card,Card+52,copyCard);
    sort(copyCard,copyCard+52);
    //Display unshuffled deck to verify 4 of each card
    for (int i=0;i<52;i++){
        cout << copyCard[i]<< " ";
    }
    cout << endl;
    cout << "Shuffling Deck x2"<<endl; 
    //Display shuffled deck
    for (int i=0;i<52;i++){
        cout << Card[i]<<" ";
    }
    cout << endl;
}    

void faceDSP (queue<int> &q1, queue<int> &q2){
    //This function replaces this line of code
    //cout << q1.front() << " vs " << q2.front()<<"   ";
    
    //Forcing output of J/Q/K instead of 11/12/13
    //But doing so rather inefficiently.
    //I should have called faceWAR() twice instead

    switch (q1.front()){
        case 11:
            cout << "J";
            break;
        case 12:
            cout << "Q";
            break;
        case 13:
            cout << "K";
            break;
        default:
            cout << q1.front();
            break;
    }
    cout << " vs ";
    switch (q2.front()){
        case 11:
            cout << "J";
            break;
        case 12:
            cout << "Q";
            break;
        case 13:
            cout << "K";
            break;
        default:
            cout << q2.front();
            break;        
    }
    
    cout <<"   ";
    return;
}

void faceWAR (int n){
    //Force output of below to display J/Q/K instead of 11/12/13
    //cout << s1.top() << " vs " << s2.top();
    switch (n){
        case 11:
            cout << "J";
            break;
        case 12:
            cout << "Q";
            break;
        case 13:
            cout << "K";
            break;
        default:
            cout << n;
            break;
    }
    return;
}

void timeTrack(int x){
    //My program generates "Time in seconds"
    //This function converts seconds to minutes
    int seconds,minutes;
    seconds= x%60;
    minutes = (x-seconds)/60;
    cout << "Simulated Play Time = "<< minutes << "min "<< seconds << "sec"<<endl;
}
