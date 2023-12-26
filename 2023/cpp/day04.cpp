#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>




void part01(std::vector<std::string> inputLines) {
    int pointSum=0;
    for(std::string line: inputLines) {  
        std::stringstream linestream(line);
        std::string card;
        std::getline(linestream,  card, ':');
        int cardId;
        sscanf(card.c_str(), "Card %d", &cardId);
        //std::cout << cardId << " ";
        int cardPoints=1;
        std::vector<int> winningNumbers;
        std::vector<int> yourNumbers;
        int number;
        
        while (linestream >> number)
        {   
        
           winningNumbers.push_back(number);   
        if(linestream.peek() == '|')
            break;
        }
        
        linestream.clear();  // Clear the stream state
        linestream.seekg(0);
        std::string yours;
        std::getline(linestream, card, '|');
        while (linestream >> number)
        {
            //std::cout << "x" << number;
           yourNumbers.push_back(number);   
            
        }
        /*
        for(auto v: winningNumbers)
            //std::cout << v << " ";
        std::cout << std::endl;
        for(auto e: yourNumbers)
            //std::cout << e << " ";
        std::cout << std::endl;*/
        cardPoints = 1;
        /*
        for(auto v1: winningNumbers) {
            for(auto v2: yourNumbers){
                if(v1 == v2){
                    cardPoints*=2;
                    break;
                }
            }
            
            std::cout << cardPoints << " ";
        }*/
        std::sort(winningNumbers.begin(), winningNumbers.end());
        std::sort(yourNumbers.begin(), yourNumbers.end());

        
        for (int winNumber : winningNumbers) {
            if (std::binary_search(yourNumbers.begin(), yourNumbers.end(), winNumber)) {
                cardPoints*=2;
            }
        }
        if(cardPoints>1)
            cardPoints/=2;
        else cardPoints=0;
        //std::cout << cardPoints;
        pointSum+=cardPoints;
        
    }

    std::cout << "Part01: " << pointSum  << std::endl;
}


void part02(std::vector<std::string> inputLines) {
    int cardSum=0;
    std::vector<int> instances;
    instances.resize(inputLines.size(), 1);
    std::vector<int> matchesNum;
    for(std::string line: inputLines) {  
        std::stringstream linestream(line);
        std::string card;
        std::getline(linestream,  card, ':');
        int cardId;
        sscanf(card.c_str(), "Card %d", &cardId);
        //std::cout << cardId << " ";
        int cardPoints=1;
        std::vector<int> winningNumbers;
        std::vector<int> yourNumbers;
        int number;
        
        while (linestream >> number)
        {   
        
           winningNumbers.push_back(number);   
        if(linestream.peek() == '|')
            break;
        }
        
        linestream.clear();  // Clear the stream state
        linestream.seekg(0);
        std::string yours;
        std::getline(linestream, card, '|');
        while (linestream >> number)
        {
            //std::cout << "x" << number;
           yourNumbers.push_back(number);   
            
        }
        
        cardPoints = 1;
        int matches=0;
        
        std::sort(winningNumbers.begin(), winningNumbers.end());
        std::sort(yourNumbers.begin(), yourNumbers.end());

        
        for (int winNumber : winningNumbers) {
            if (std::binary_search(yourNumbers.begin(), yourNumbers.end(), winNumber)) {
                matches++;
            }
        }
        matchesNum.push_back(matches);
        //std::cout << matches << std::endl;
        
        
        
    }
    for (int i = 0; i < instances.size(); i++) {
            for (int j = i + 1; j < std::min(i + 1 + matchesNum[i], int(matchesNum.size())); j++)
                instances[j] +=instances[i];
            cardSum += instances[i];
        }

    std::cout << "Part03: " << cardSum  << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day04.txt");
    std::vector<std::string> inputLines;
    std::string inputLine;
    while(std::getline(inputFile,inputLine)) {
        inputLines.push_back(inputLine);
    }
    inputFile.close();

    part01(inputLines);
    part02(inputLines);

    return 0;
}
