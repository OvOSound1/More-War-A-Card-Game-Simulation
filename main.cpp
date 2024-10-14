// Name: Francisco Fausto
// Class (CECS 325-02)
// Project Name (Prog 2 – More War)
// Due Date (10/1/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <ctime>  // Include for std::time

using namespace std;

class Card {
private:
    char suit;
    char rank;

public:
    // Correct order of initialization
    Card(char r = ' ', char s = ' ') : suit(s), rank(r) {}

    void print() {
        if (rank == 'T') cout << "10";  // Special case for 'T'
        else cout << rank;
        cout << suit;
    }

    int compare(Card other)
    {
        char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        int thisValue = 0, otherValue = 0;

        for (int i = 0; i < 13; ++i)
        {
            if (rank == ranks[i])
                thisValue = i;
            if (other.rank == ranks[i])
                otherValue = i;
        }

        if (thisValue > otherValue)
            return 1;
        if (thisValue < otherValue)
            return -1;
        return 0;
    }
};

class Deck {
private:
    vector<Card> cards;
    int currentCard;

public:
    Deck() : currentCard(0) {
        char suits[] = {'C', 'S', 'D', 'H'};
        char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        for (char s : suits) {
            for (char r : ranks) {
                cards.push_back(Card(r, s));
            }
        }
    }

    void shuffle() {
        std::srand(static_cast<unsigned int>(std::time(0)));  // Seed random number generator
        for (int i = 0; i < 52; ++i)
        {
            int r = i + std::rand() / (RAND_MAX / (52 - i) + 1);
            Card temp = cards[i];
            cards[i] = cards[r];
            cards[r] = temp;
        }
        currentCard = 0;  // Reset current card index after shuffling
    }

    Card deal() {
        if (currentCard >= cards.size()) {
            throw runtime_error("No more cards to deal!");  // Exception handling
        }
        return cards[currentCard++];
    }

    void print() {
        for (int i = currentCard; i < cards.size(); ++i) {
            cards[i].print();
            cout << " ";
        }
        cout << endl;
    }

    bool isEmpty() {
        return currentCard >= cards.size();
    }
};

int main() {
    string player1, player2;
    Deck deck;

    // Player input
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;

    // Number of games input
    int numGames;
    cout << "Enter number of games to play: ";
    cin >> numGames;

    // Print original deck
    cout << "\nOriginal Deck" << endl;
    deck.print();

    // Shuffle the deck
    deck.shuffle();
    cout << "\nShuffled Deck" << endl;
    deck.print();

    // Initialize scores
    int player1Wins = 0, player2Wins = 0, ties = 0;

    try {
        // Play numGames rounds
        for (int i = 0; i < numGames; ++i) {
            cout << "\nGame " << setw(2) << i + 1 << "\n" << string(8, '-') << endl;

            // Deal cards to each player
            Card card1 = deck.deal();
            Card card2 = deck.deal();

            // Print player's card
            cout << player1 << " => ";
            card1.print();
            cout << endl;

            cout << player2 << " => ";
            card2.print();
            cout << endl;

            // Compare cards and update scores
            int result = card1.compare(card2);
            if (result == 1) {
                cout << player1 << " => Winner" << endl;
                ++player1Wins;
            } else if (result == -1) {
                cout << player2 << " => Winner" << endl;
                ++player2Wins;
            } else {
                cout << "Tie game" << endl;
                ++ties;
            }
        }
    } catch (const runtime_error& e) {
        // If there's a problem, we print an error message.
        cout << "Error - " << e.what() << endl;
    }

    // Final stats output
    cout << "\n------Final Stats-------" << endl;
    cout << left << setw(15) << player1 << " vs. " << player2 << endl;
    cout << left << setw(15) << "Wins" << setw(5) << player1Wins << player2Wins << endl;
    cout << left << setw(15) << "Losses" << setw(5) << player2Wins << player1Wins << endl;
    cout << left << setw(15) << "Ties" << setw(5) << ties << ties << endl;

    return 0;
}
