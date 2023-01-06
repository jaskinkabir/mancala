#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#ifdef _WIN32 // Makes sure Sleep() works cross platform.
#include <Windows.h> //
#else
#include <unistd.h>
#endif

using namespace std;

vector<int> board;
bool gameEnd;
int turn;
int p1wins = 0;
int p2wins = 0;
int ties = 0;
string player1;
string player2;
string r;
unsigned char i;
bool endGame;

/* How vector is mapped to board:
    cout << "--------------------------------------------------" << endl;
    cout << "|  ------                                ------  |" << endl;
    cout << "|  |    |  ---- ---- ---- ---- ---- ---- |    |  |" << endl;
    cout << "|  |    |  |13| |12| |11| |10| |09| |08| |    |  |" << endl;
    cout << "|  |    |  ---- ---- ---- ---- ---- ---- |    |  |" << endl;
    cout << "|  | 00 |                                | 07 |  |" << endl;
    cout << "|  |    |  ---- ---- ---- ---- ---- ---- |    |  |" << endl;
    cout << "|  |    |  |01| |02| |03| |04| |05| |06| |    |  |" << endl;
    cout << "|  |    |  ---- ---- ---- ---- ---- ---- |    |  |" << endl;
    cout << "|  ------                                ------  |" << endl;
    cout << "--------------------------------------------------" << endl;
    */

void clear() //makes sure clear() works cross-platform
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void printBoard(int selected) {
    vector<string> strBoard;
    char q = ' ';
    char w = ' ';
    char e = ' ';
    char r = ' ';
    char t = ' ';
    char y = ' ';
    char u = ' ';
    char i = ' ';
    char o = ' ';
    char p = ' ';
    char a = ' ';
    char s = ' ';
    char d = ' ';
    char f = ' ';
    char g = ' ';

    //Each space on the board is surrounded by a variable. When that variable is changed to an asterisk, that space will be displayed surrounded by asterisks.

    for (auto& n : board) { // Adds a 0 before single digit numbers so that the spacing in the board is maintained
        if (n / 10 > 0) {
          strBoard.push_back(to_string(n));
        }
        else {
          strBoard.push_back("0" + to_string(n));
        }
    }

    //code for selection of space in board
    //When space is selected, the area surrounding that space is changed to asterisks.

    switch (selected) { //Changes a variable to asterisks based on the argument passed to the function
    case -2:
        strBoard = { "B2", "P1", "P1", "P1", "P1", "P1", "P1", "B1", "P2", "P2", "P2", "P2", "P2", "P2"}; //-2 is passed for the displayRules function
    case -1: //-1 is passed to not select a space
        break;
    case 0:
        f = '*';
        break;
    case 1:
        i = '*';
        break;
    case 2:
        o = '*';
        break;
    case 3:
        p = '*';
        break;
    case 4:
        a = '*';
        break;
    case 5:
        s = '*';
        break;
    case 6:
        d = '*';
        break;
    case 7:
        g = '*';
        break;
    case 8:
        y = '*';
        break;
    case 9:
        t = '*';
        break;
    case 10:
        r = '*';
        break;
    case 11:
        e = '*';
        break;
    case 12:
        w = '*';
        break;
    case 13:
        q = '*';
        break;
    }

    //Print board line by line
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "|  " << f << f << f << f << f << f << f << f << f << f << f << f << "                                                                        " << g << g << g << g << g << g << g << g << g << g << g << g << "  |" << endl;
    cout << "|  " << f << "----------" << f << "    " << q << q << q << q << q << q << q << q << "   " << w << w << w << w << w << w << w << w << "   " << e << e << e << e << e << e << e << e << "   " << r << r << r << r << r << r << r << r << "   " << t << t << t << t << t << t << t << t << "   " << y << y << y << y << y << y << y << y << "     " << g << "----------" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << q << "------" << q << "   " << w << "------" << w << "   " << e << "------" << e << "   " << r << "------" << r << "   " << t << "------" << t << "   " << y << "------" << y << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << q << "| " << strBoard[13] << " |" << q << "   " << w << "| " << strBoard[12] << " |" << w << "   " << e << "| " << strBoard[11] << " |" << e << "   " << r << "| " << strBoard[10] << " |" << r << "   " << t << "| " << strBoard[9] << " |" << t << "   " << y << "| " << strBoard[8] << " |" << y << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << q << "------" << q << "   " << w << "------" << w << "   " << e << "------" << e << "   " << r << "------" << r << "   " << t << "------" << t << "   " << y << "------" << y << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << q << q << q << q << q << q << q << q << "   " << w << w << w << w << w << w << w << w << "   " << e << e << e << e << e << e << e << e << "   " << r << r << r << r << r << r << r << r << "   " << t << t << t << t << t << t << t << t << "   " << y << y << y << y << y << y << y << y << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|   " << strBoard[0] << "   |" << f << "                                                                        " << g << "|   " << strBoard[7] << "   |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << i << i << i << i << i << i << i << i << "   " << o << o << o << o << o << o << o << o << "   " << p << p << p << p << p << p << p << p << "   " << a << a << a << a << a << a << a << a << "   " << s << s << s << s << s << s << s << s << "   " << d << d << d << d << d << d << d << d << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << i << "------" << i << "   " << o << "------" << o << "   " << p << "------" << p << "   " << a << "------" << a << "   " << s << "------" << s << "   " << d << "------" << d << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << i << "| " << strBoard[1] << " |" << i << "   " << o << "| " << strBoard[2] << " |" << o << "   " << p << "| " << strBoard[3] << " |" << p << "   " << a << "| " << strBoard[4] << " |" << a << "   " << s << "| " << strBoard[5] << " |" << s << "   " << d << "| " << strBoard[6] << " |" << d << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "|        |" << f << "    " << i << "------" << i << "   " << o << "------" << o << "   " << p << "------" << p << "   " << a << "------" << a << "   " << s << "------" << s << "   " << d << "------" << d << "     " << g << "|        |" << g << "  | " << endl;
    cout << "|  " << f << "----------" << f << "    " << i << i << i << i << i << i << i << i << "   " << o << o << o << o << o << o << o << o << "   " << p << p << p << p << p << p << p << p << "   " << a << a << a << a << a << a << a << a << "   " << s << s << s << s << s << s << s << s << "   " << d << d << d << d << d << d << d << d << "     " << g << "----------" << g << "  | " << endl;
    cout << "|  " << f << f << f << f << f << f << f << f << f << f << f << f << "                                                                        " << g << g << g << g << g << g << g << g << g << g << g << g << "  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
}

int flipTurn() { //Flips whose turn it is at the end of each turn
    if (turn == 1) {
        return 2;
    }
    if (turn == 2) {
        return 1;
    }
    else { return 0; }
}

void initializeGame() {
    srand(time(0));
    clear();
    board = { 0,4,4,4,4,4,4,0,4,4,4,4,4,4 };
    turn = 1 + rand() % 2; //Sets turn to 1 or 2 randomly
    gameEnd = false;
}

void displayRules() {
    while (true) {
        clear();
        
        printf("\nMANCALA \nBy Adam Damreh, Carter Yeh, and Jaskin Kabir\n");
        printf("\nRules and Instructions: \n");
        printf("1. Press r at any time to return to this screen.");
        printf("2. Player 1 has the bottom half of the board, and the bank on the right. The banks are the two spaces on the left and right edges of the board. \n   Player 2 has the top half of the board, and the bank on the left. View the diagram below for more info. \n\n");
        printf("3. Each turn, select a space on your side of the board, then all of the marbles\n   in that space will be picked up and dropped into the next spaces one by one, moving counterclockwise. \n\n");
        printf("4. If your turn goes past your bank, drop a marble in your bank. \n\n");
        printf("5. If your turn goes past your opponents bank, their bank is skipped.\n\n");
        printf("6. If you drop the last marble into your bank, you get another turn.\n\n"); 
        printf("7. If you drop the last marble into an empty space on your side of the board,\n   that marble and your opponents marbles in the space opposite the one you landed in are captured and moved into your bank.\n\n");
        printf("8. The game is over once all the spaces on one side of the board are empty.\n   The remaining marbles on the other players side are then added to their bank.\n\n");
        printf("9. The winner is the player with the most marbles in their bank at the end of the game.\n\n");
        printBoard(-2); //Display labeled board
        cout << "P1 spaces belong to player 1, and B1 is the bank of player 1. Player 2 has bank B2 and spaces labeled P2" << endl;
        printf("\nPress enter to continue...\n");

        i = _getch();
        if (i == 13) { //if enter is pressed, exit loop
            clear();
            break;
        }


    }
}

int handleTurn() {
    int selected; //Space user currently has selected
    int spcheck; //Temporary variable for checking if next space over is empty
    unsigned char a; //ASCII code for character user has pressed

    while (true) { //Doesn't move on until player lands on a space that is not their bank

        switch (turn) { //Hanldes player input
        case 1: //code for player 1's turn
            selected = 1;
            while (board[selected] == 0) { //Initialize the board selection so that the user starts on a non empty space
                selected++;
            }

            if (board[1] == 0 && board[2] == 0 && board[3] == 0 && board[4] == 0 && board[5] == 0 && board[6] == 0) { //Checks if P1's side of the board is empty
                cout << "You have no valid moves!" << endl;
                Sleep(700);
                return -1; //return -1 so that checkCapture does nothing

            }

            while (true)
            {
                clear();
                cout << "Player 1: " << player1 << "'s turn!" << endl;
                cout << "Use the arrow keys to select a space, then hit enter." << endl;
                cout << "Press r to view the rules." << endl << endl;
                printBoard(selected);

                a = _getch(); //Gets user's keystroke

                if (a == 0 || a == 0xE0) a = _getch(); //The arrow keys output a 0 and then the code for their key, so getch must be called twice

                if (a == 13) break; //When enter is pressed, exit the loop

                if (a == 114) displayRules(); //When r is pressed, display the rules

                if (a == 99) { // Demonstrate capture (press c)
                    board[selected] = 1;
                    board[selected+1] = 0;
                    if (board[13 - selected] == 0) board[13 - selected]++;
                }

                if (a == 119) { //demonstrate handleGameEnd (press w)
                    for (int i = 0; i < 6; i++) {
                        board[i] = 0;
                    }
                    board[6] = 1;
                } 

                if (a == 98) board[selected] = 7 - selected;  //Demonstrate repeat turn (press b)

                else if (a == 75) { //left arrow key is pressed, does nothing if there is no valid space to the left
                    if (selected > 1) { // Check if already at the left edge 
                        spcheck = selected - 1;// Set spcheck to the index to the left
                        while (board[spcheck] == 0 && spcheck > 1) {//loops until the nearest non empty space to the left is found. 
                            spcheck--;
                        }
                        if (board[spcheck] != 0) selected = spcheck; //Update which space is selected
                    }
                }

                else if (a == 77) // right arrow key is pressed, does nothing if there is no valid space to the right
                    if (selected < 6) { // Check if already at the right edge 
                        spcheck = selected + 1; // Set spcheck to the index to the right
                        while (board[spcheck] == 0 && spcheck < 6) {//loops until the nearest non empty space to the right is found.                        
                            spcheck++;
                        }
                        if (board[spcheck] != 0) selected = spcheck; //Update which space is selected
                    }
            }

            break;
        case 2: //Code for player 2's turn
            selected = 13;
            while (board[selected] == 0) { //Initialize the board selection so that the user starts on a non empty space
                selected--;
            }

            if (board[13] == 0 && board[12] == 0 && board[11] == 0 && board[10] == 0 && board[9] == 0 && board[8] == 0) { //Checks if P2's side of the board is empty
                cout << "You have no valid moves!" << endl;
                Sleep(700);
                return -1; //return -1 so that checkCapture does nothing
            }

            while (true)
            {
                clear();
                cout << "Player 2: " << player2 << "'s turn!" << endl;
                cout << "Use the arrow keys to select a space, then hit enter." << endl;
                cout << "Press r to view the rules." << endl << endl;
                printBoard(selected);

                a = _getch(); //Gets user's keystroke

                if (a == 0 || a == 0xE0) a = _getch(); //The arrow keys output a 0 and then the code for their key, so getch must be called twice

                if (a == 13) { //When enter is pressed, exit the loop
                    break;
                }

                if (a == 114) displayRules(); //When r is pressed, display the rules

                if (a == 99) { // Demonstrate capture (press c)
                    board[selected] = 1;
                    board[selected + 1] = 0;
                    if (board[13 - selected] == 0) board[13 - selected]++;
                }

                if (a == 98) board[selected] = 14 - selected; //demonstrate repeat turn (press b)


                if (a == 119) { //demonstrate handleGameEnd (press w)
                    for (int i = 8; i < 14; i++) {
                        board[i] = 0;
                    }
                    board[13] = 1;
                }

                else if (a == 75) { // left arrow key is pressed, does nothing if there is no valid space to the left
                    if (selected < 13) {//skips over empty spaces
                        spcheck = selected + 1; // Set spcheck to the index to the left
                        while (board[spcheck] == 0 && spcheck < 13) { //Find nearest non empty space to the left                            
                            spcheck++;

                        }
                        if (board[spcheck] != 0) selected = spcheck;//Update which space is selected
                    }
                }

                else if (a == 77) { //right arrow key is pressed, does nothing if there is no valid space to the right
                    if (selected > 8) {//skips over empty spaces
                        spcheck = selected - 1; // Set spcheck to the index to the right
                        while (board[spcheck] == 0 && spcheck > 8) { //Find nearest non empty space to the right                           
                            spcheck--;
                        }
                        if (board[spcheck] != 0) selected = spcheck;//Update which space is selected
                    }
                }
            }
            break;
        }


        int marbles = board[selected]; //Sets up screen for "animating" turn
        clear();
        printBoard(-1);
        Sleep(500);
        board[selected] = 0;
        clear();
        printBoard(selected);

        for (marbles; marbles > 0; marbles--) { //increments space after current space, waits 500ms, then clears screen and prints board with changes made
            selected++;
            if (selected == 14) { selected = 0; } //makes sure function doesn't go out of bounds
            if (turn == 1 && selected == 0) { // if statements skip over bank of opponent
                selected++;
            }
            if (turn == 2 && selected == 7) {
                selected++;
            }
            board[selected]++;//increment space, then clear and print board
            Sleep(500);
            clear();
            printBoard(selected);
        }

        if (turn == 1 && selected == 7) { //If statments check if player landed on their bank and gives them an extra turn if they did
            cout << endl << player1 << "'s turn again!" << endl;
            Sleep(600);
            clear();
            printBoard(-1);
        }
        else if (turn == 2 && selected == 0) {
            cout << endl << player2 << "'s turn again!" << endl;
            Sleep(600);
            clear();
            printBoard(-1);
        }
        else {
            break;
        }

    }

    return selected; //Return ending space so the checkCapture function can check if a capture must be evaluated
}

void checkCapture(int endSpace) {
    //if statement checks which space stone last lands in, then checks if spot opposite is empty excluding spots 0 and 7
    //if opposite spot is on the opposing side, the stones from your spot and the opposing spot go into your bank
    int marbles;
    Sleep(500);

    if (endSpace == -1) { //Do nothing if -1 is passed
        return;
    }

    if (board[endSpace] == 1) { // checks if player's turn ended on an empty space
        if (turn == 1 && endSpace >= 1 && endSpace <= 6 && board[14 - endSpace] > 0) { //checks if it is player one's turn, the turn landed on their side of the board, and that the opposite space is not empty

            board[endSpace] = 0; //sets player one's ending space to zero
            clear();
            printBoard(endSpace);
            board[7] ++; //adds single stone to player one's bank
            Sleep(500);
            clear();
            printBoard(7);
            marbles = board[14 - endSpace];
            board[14 - endSpace] = 0; //sets opposite space to zero
            Sleep(500);
            clear();
            printBoard(14 - endSpace);
            board[7] += marbles; //adds opposite space's stones to player one's bank
            Sleep(500);
            clear();
            printBoard(7);
            Sleep(500);
        }
        if (turn == 2 && endSpace >= 8 && endSpace <= 13 && board[14 - endSpace] > 0) { //checks if it is player two's turn, the turn landed on their side of the board, and that the opposite space is not empty

            board[endSpace] = 0; //sets player two's ending space to zero
            clear();
            printBoard(endSpace);
            board[0] ++; //adds single stone to player two's bank
            Sleep(500);
            clear();
            printBoard(0);
            marbles = board[14 - endSpace];
            board[14 - endSpace] = 0; //sets opposite space to zero
            Sleep(500);
            clear();
            printBoard(14 - endSpace);
            board[0] += marbles; //adds score of opposite space's stone to player two's bank
            Sleep(500);
            clear();
            printBoard(0);
            Sleep(500);
        }
    }
}

void handleGameEnd() {
    int marbles;
    if (board[1] == 0 && board[2] == 0 && board[3] == 0 && board[4] == 0 && board[5] == 0 && board[6] == 0 || board[13] == 0 && board[12] == 0 && board[11] == 0 && board[10] == 0 && board[9] == 0 && board[8] == 0) { //Check if one row is empty
        gameEnd = true;
        cout << "Game over!" << endl;
        Sleep(500);
        for (int i = 1; i < 14; i++) { //loop through the board, adding all of the stones to the player's bank who still has valid moves
            marbles = 0;
            if (i == 7) i++;
            if (board[i] != 0) {
                marbles = board[i]; //Display board with selected space emptied
                board[i] = 0;
                Sleep(500);
                clear();
                printBoard(i);
                if (i < 7) { //Add marbles to p1's bank
                    board[7] += marbles; //Then display board with stones added to bank
                    Sleep(500);
                    clear();
                    printBoard(7);
                }
                if (i > 7) { //Add marbles to p2's bank
                    board[0] += marbles; //Then display board with stones added to bank
                    Sleep(500);
                    clear();
                    printBoard(0);
                }
            }
        }
    }
    if (gameEnd) { //Display who won or if there is a tie
        if (board[0] > board[7]) {
            p2wins++;
            cout << player2 << " wins!";
        }
        if (board[7] > board[0]) {
            p1wins++;
            cout << player1 << " wins!";
        }
        if (board[7] == board[0]) {
            ties++;
            cout << "It's a tie!";
        }
    }
}


int main() {

    cout << "Player 1 Name?" << endl;//Ask for player names
    getline(cin, player1);
    cout << endl << "Player 2 Name?" << endl;
    getline(cin, player2);

    displayRules();

    initializeGame();

    while (!gameEnd) {
        checkCapture(handleTurn()); //Game loop
        handleGameEnd();
        turn = flipTurn();

        if (gameEnd) { //Code to ask player to play again:
            Sleep(750);

            char a = ' ';//Variable surrounding Yes
            char b = ' ';//Variable surrounding No
            int res = 1;//User's selection, 1 if yes, 2 if no


            while (true)
            {
                switch (res) { //Sets whether yes or no should be highlighted based on what the user has selected
                case 1:
                    a = '*';
                    b = ' ';
                    break;
                case 2:
                    b = '*';
                    a = ' ';
                    break;
                }
                clear();
                printBoard(-1);
                cout << player1 << " Has won " << p1wins << " times!" << endl;
                cout << player2 << " Has won " << p2wins << " times!" << endl;
                cout << "You have tied " << ties << " times!" << endl << endl;
                cout << "Play again?" << endl;
                cout << "Use the arrow keys to select an answer, then press enter." << endl << endl;
                cout << a << a << a << a << a << " " << b << b << b << b << endl; 
                cout << a << "Yes" << a << " " << b << "No" << b << endl;
                cout << a << a << a << a << a << " " << b << b << b << b << endl;

                i = _getch(); //Gets user's keystroke

                if (i == 0 || a == 0xE0) i = _getch(); //The arrow keys output a 0 and then the code for their key, so getch must be called twice

                if (i == 13) { //When enter is pressed, exit the loop
                    break;
                }
                else if (i == 75 && res == 2) {//left arrow key, checks if no is selected and moves to yes if it is
                    res = 1;
                }
                else if (i == 77 && res == 1) {//right arrow key, checks if yes is selected and moves to no if it is
                    res = 2;
                }
            }
            if (res == 1) {//reinitialize game if yes
                initializeGame();
            }
            else {//end program if no
                return 0;
            }

        }
    }
} 

/*Cheat codes:
    Press c to demonstrate capture
    Press b to demonstrate repeat turn
    press w to demonstrate game end
*/