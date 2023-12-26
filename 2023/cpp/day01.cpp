#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>


std::vector<std::string> digitsStrings{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "0","1", "2", "3", "4", "5", "6", "7", "8", "9"};

bool isDigit(char c){
    return c>='0' && c<='9';
}

//NE IDE S ITERATORIMA, IDE KRKANSKO RJESENJE :)

bool isDigit(std::string digitString){
    return (std::find(digitsStrings.begin(), digitsStrings.end(), digitString) != digitsStrings.end());
}


int digitStringToInt(std::string digitString)  {
    if (digitString=="0" || digitString=="zero") {
        return 0;
    }
    else if (digitString == "1" || digitString == "one") {
        return 1;
    }
    else if (digitString == "2" || digitString == "two") {
        return 2;
    }
    else if (digitString == "3" || digitString == "three") {
        return 3;
    }
    else if (digitString == "4" || digitString == "four") {
        return 4;
    }
    else if (digitString == "5" || digitString == "five") {
        return 5;
    }
    else if (digitString == "6" || digitString == "six") {
        return 6;
    }
    else if (digitString == "7" || digitString == "seven") {
        return 7;
    }
    else if (digitString == "8" || digitString == "eight") {
        return 8;
    }
    else if (digitString == "9" || digitString == "nine") {
        return 9;
    }
    return -1;
}

void part01(std::vector<std::string> inputLines) {
    int digitCount = 0;
    int myNumber = 0;
    int total = 0;
    int twodigits=0;

    for(std::string line: inputLines) {
        myNumber=0;
        for (char c : line) {
        if (isDigit(c)) {
            myNumber = myNumber * 10 + (c - '0');   
        }
    }
    twodigits=0;
    std::string numString = std::to_string(myNumber);
    twodigits = 10 * (numString.at(0) - '0') + (numString.at(numString.size() - 1) - '0');
    
    total+=twodigits;
    myNumber=0;
                
    }
    std::cout <<"Part 01: " <<  total << std::endl;
}


void part02(std::vector<std::string> inputLines) {
    int total(0);

    for (const auto &line : inputLines) {
        unsigned int lineLength = line.size();
        std::vector<int> numbers;

        for (int i = 0; i < lineLength; ++i) {
            std::string substring;
            for (int j = i; j < lineLength; ++j) {
                const auto &c = line[j];
                substring += c;
                if (isDigit(substring)) {
                    numbers.push_back(digitStringToInt(substring));
                    break;
                }
            }
        }
        total += (numbers.front()*10 + numbers.back());
    }   
    std::cout <<"Part 02: " <<  total << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day01.txt");
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
