#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Matrix {
    std::vector<std::vector<char>> elements;
    int horizontalRefStart=0, verticalRefStart=0;
};
void findHorizontalReflection(Matrix &mat){
    for(int i=0;i<mat.elements.size()-1;i++){
        int curr=i;
        int j=i+1;
        int k= curr;
        while(mat.elements[curr] == mat.elements[j]){
            curr--;
            j++;
            if(curr ==-1 || j == mat.elements.size()){
                mat.horizontalRefStart=i+1;
                return;
            }
        }   
    }
    return;
}
void findVerticalReflection(Matrix &mat){
    int rowNum =mat.elements.size();
    int colNum = mat.elements[0].size();
    Matrix rotatedMat;
    std::vector<std::vector<char>> elements(colNum, std::vector<char>(rowNum));
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            elements[j][rowNum - 1 - i] = mat.elements[i][j];
        }
    }
    rotatedMat.elements=elements;
    findHorizontalReflection(rotatedMat);
    mat.verticalRefStart=rotatedMat.horizontalRefStart;
    
    return;
}

void part01(std::vector<Matrix> &patterns) {
    int sum(0);
    for(int i =0;i<patterns.size();i++){
        findVerticalReflection(patterns[i]);
        findHorizontalReflection(patterns[i]);
        //std::cout << i << ": " << patterns[i].horizontalRefStart << " " << patterns[i].verticalRefStart << std::endl;
        sum+= (patterns[i].horizontalRefStart)*100 + patterns[i].verticalRefStart;
    }
    std::cout << "Part 01: " << sum <<std::endl;
}


void part02(std::vector<Matrix> patterns) {
    
}

int main() {
    std::ifstream inputFile("../input/day13.txt");
    std::vector<std::string> inputLines;
    std::string inputLine;
    std::vector<Matrix> patterns;
    Matrix current;
    int i(0);
    while(std::getline(inputFile,inputLine)) {
        if(inputLine.empty()){
            patterns.push_back(current);
            current.elements.clear();
            i=0;
        }
        else {
            std::vector<char> row;
            for(char c: inputLine)
                row.push_back(c);
            current.elements.push_back(row);
            //current.elements.push_back(inputLine);
            i++;
        }
    }
    patterns.push_back(current);


    std::cout <<patterns.size() << std::endl;
    inputFile.close();

    part01(patterns);
    part02(patterns);

    return 0;
}
