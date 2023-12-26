#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>


struct Hand {
    std::string cards;
    int bid;
};

bool jokerExists=false;

int getHandType(Hand hand){
    std::string cards = hand.cards;
    std::sort(cards.begin(), cards.end());

    int singles = 0;
    int pairs = 0;
    int threes = 0;
    int fours = 0;
    int fives = 0;
    int jokers = 0;

    int size = cards.length();
    int counter = 1;
    for (int i = 0; i < size; i++) {
        if (jokerExists == true && cards[i] == 'J') {
            jokers++;
            counter = 1;
            continue;
        }

        if (i + 1 == size || cards[i] != cards[i + 1]) {
            switch (counter) {
            case 5:
                fives++;
                break;
            case 4:
                fours++;
                break;
            case 3:
                threes++;
                break;
            case 2:
                pairs++;
                break;
            case 1:
                singles++;
                break;
            default:
                exit(-1);
            }

            counter = 1;
        } 
        else {
            counter++;
        }
    }

    int rank = 0;
    if (fives || (fours && jokers) || (threes && jokers == 2) ||
    (pairs && jokers == 3) || jokers == 4 || jokers == 5)
        rank = 6;
    else if (fours || (threes && jokers) || (pairs && jokers == 2) || jokers == 3)
        rank = 5;
    else if ((threes && pairs == 1) || (pairs == 2 && jokers))
        rank = 4;
    else if (threes || (pairs && jokers) || jokers == 2)
        rank = 3;
    else if (pairs == 2)
        rank = 2;
    else if (pairs == 1 || jokers)
        rank = 1;
    else
        rank = 0;
    return rank;
}

int compareCard(char c1, char c2){
    std::string cardOptions;
    if (jokerExists)
        cardOptions = "AKQT98765432J";
    else 
        cardOptions = "AKQJT98765432";

    if (c1 == c2)
        return 0;

    auto index1 = std::find(cardOptions.begin(),cardOptions.end(), c1);
    auto index2 = std::find(cardOptions.begin(),cardOptions.end(), c2);
 
    if (index1 < index2)
        return 1;
    else
        return -1;
}

bool lessThan(Hand h1, Hand h2){
    int rank1 = getHandType(h1);
    int rank2 = getHandType(h2);
    if (rank1 == rank2) {
        for (int i = 0; i < h1.cards.length(); i++) {
            if (h1.cards[i] == h2.cards[i])
                continue;
            return compareCard(h1.cards[i], h2.cards[i]) < 0;
        }

        return false;
    }

    return rank1 < rank2;
}





int calculateSum(std::vector<Hand> hands) {
    int rank = 1;
    int sum = 0;
    for (auto h : hands){
        sum += rank * h.bid;
        rank++;
    }
    return sum;
}

int main () {
    std::ifstream inputFile("../input/day07.txt");
    std::vector<Hand> hands;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream linestream(line);
        std::string cards;
        linestream >> cards;
        int bid;
        linestream >> bid;
        hands.push_back({cards,bid});
    }

    std::sort(hands.begin(), hands.end(), [](Hand &a, Hand &b) {
        return lessThan(a,b);
    }
    );
     

    int sum1 = calculateSum(hands);
   
    std::cout << "Part 01: " << sum1 << "\n";

    jokerExists=true;
    std::sort(hands.begin(), hands.end(), [](Hand &a, Hand &b) {
        return lessThan(a,b);
    }
    );
    int sum2 = calculateSum(hands);
    
   
    std::cout << "Part 02: " << sum2 << "\n";

    return 0;
}
