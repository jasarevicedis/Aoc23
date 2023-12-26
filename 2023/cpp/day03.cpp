#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>


bool isDigit(char c){
    return c>='0' && c<='9';
}
bool isSymbol(char c) {
    return (c!='.' && !isDigit(c));
}
// skracuje if uslov u dijelu 2  zntano, pomaze kod provjere da li
// su dvije cifre u okruzenju jedna pored druge u istom redu
bool isInRange(int a, int b, int x, int y){
    return (a<=x+1 && a>=x-1 && b<=y+1 && b>=y-1);
}

void part01(std::vector<std::string> inputLines) {
    int rowSize = inputLines.at(0).size();
    int rowNumber = inputLines.size();
    std::string partString;
    int part;
    int partSum(0);
    for(int i = 0; i < rowNumber; i++ ) {
        for(int j = 0; j < rowSize; j++){
            if(isDigit(inputLines.at(i).at(j))){
                //no need to check if its not first digit in number
                if((j == 0) || (j >0 && !isDigit(inputLines.at(i).at(j-1)))) {
                    partString="";
                    int k=i;
                    int l=j;
                    while(l < rowSize && isDigit(inputLines.at(k).at(l))){
                        partString.push_back(inputLines.at(k).at(l));
                        l++;
                        
                    }
                    part = std::stoi(partString);
                    //nakon ovog l je na mjestu zadnje cifre broja, pa mozemo pretrazit okolinu stringa broja
                    //red i, od kolone j do kolone l;
                    
                    for(int m = j-1; m <=l;m++){
                        for(int n = i-1;n <=i+1; n++){
                            if(m>=0 && m < rowSize && n >=0 && n < rowNumber){
                                if(isSymbol(inputLines.at(n).at(m))){
                                   // std::cout << part << std::endl;
                                    partSum+= part;
                                    break;
                                }
                            }
                        }
                    }
                    //malo neefikasno jer se provjervaju i brojevi, ali kraca sintaxa zato
                    //std::cout << part << std::endl;
                }
            }
        }
    }
    std::cout << "Part 01: " << partSum << std::endl;
}


void part02(std::vector<std::string> inputLines) {
    int rowSize = inputLines.at(0).size();
    int rowNumber = inputLines.size();
    std::string partString;
    int gearProduct;
    int gearRatio(0);
    int partNumbersCounter(0);
    std::vector<int> nums;
    for(int i = 0; i < rowNumber; i++ ) {
        for(int j = 0; j < rowSize; j++){
            if(inputLines.at(i).at(j) == '*'){
                gearProduct=1;
                nums.clear();
                partNumbersCounter=0;//ako dostigne 2, imamo tacno 2 broja pored zvjezdice
                for(int m = i-1; m <=i+1;m++){
                    for(int n = j-1;n <=j+1; n++){
                        if(n>=0 && n < rowSize && m >=0 && m < rowNumber){
                            if(isDigit(inputLines.at(m).at(n))  && !(isInRange(m, n+1, i, j) && isDigit(inputLines.at(m).at(n+1))) ){
                                partNumbersCounter++;
                                int k=m;
                                int l=n;
                                
                                while(isDigit(inputLines.at(k).at(l))){
                                    if(l==0){
                                        l--;
                                        break;
                                    }
                                    l--;
                                }
                                l++;
                                partString="";
                                
                                
                                while(l< rowSize && isDigit(inputLines.at(k).at(l))){
                                    partString.push_back(inputLines.at(k).at(l));
                                    l++;
                                }
                                //std::cout << "x"<< partString <<std::endl;
                                nums.push_back(std::stoi(partString));
                                
                            }
                        }
                    }
                }
                //std::cout << partNumbersCounter <<std::endl;
                if(partNumbersCounter == 2){
                
                    gearProduct=1;
                    //std::cout << "()" << std::endl;
                    for(int num: nums){
                        //std::cout << num <<std::endl;
                        gearProduct*=num;
                        //std::cout << gearProduct <<std::endl;
                    }
                    //std::cout << "()" << std::endl;
                    
                    gearRatio += gearProduct;
                }
            }
        }
    }
    std::cout << "Part 02: " << gearRatio << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day03.txt");
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
