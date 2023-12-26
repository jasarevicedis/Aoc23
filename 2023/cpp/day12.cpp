#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>
#include <map>
typedef unsigned long long ull;

struct Row {
    std::string rowMap;
    std::vector<ull> counters;
};

ull countCombinations(std::map<std::tuple<ull, ull, ull>,ull> &map, Row &row,ull lineStart, ull currBroken, ull sizeOff)
{
    std::tuple<ull, ull, ull> t(lineStart, currBroken, sizeOff);
    if (map.count(t))
        return map[t];

    ull   counter = 0;
    bool groupEnd = false;
    if (currBroken) {
        if (currBroken == row.counters[sizeOff]) {
            currBroken = 0;
            sizeOff++;
            groupEnd = true;
        } else if (currBroken > row.counters[sizeOff]) {
            return 0;
        }
    }

    if (lineStart == row.rowMap.length()) {
        if (!currBroken && sizeOff == row.counters.size())
            return 1;

        return 0;
    }
    //BLOODY RECURSION
    if (row.rowMap[lineStart] == '.') {
        if (!currBroken)
            counter = countCombinations(map, row, lineStart + 1, 0, sizeOff);
    }
    else if (row.rowMap[lineStart] == '#') {
        if (!groupEnd && sizeOff < row.counters.size())
            counter = countCombinations(map, row, lineStart + 1, currBroken + 1, sizeOff); 
    }
    else if (row.rowMap[lineStart] == '?') {
        //#
        if (!groupEnd && sizeOff< row.counters.size())
            counter += countCombinations(map, row, lineStart + 1, currBroken + 1, sizeOff);

        //.
        if (currBroken == 0)
            counter += countCombinations(map, row, lineStart + 1, 0,sizeOff);
    }

    map[t] = counter;
    return counter;
}

void part01(std::vector<std::string> inputLines) {
    ull result(0);
    ull size = inputLines.size();
    std::vector<Row> rows;
    for(ull i=0;i< size;i++){
        std::string rowString;
        std::stringstream linestream(inputLines.at(i));
        std::getline(linestream, rowString, ' ');
        std::vector<ull> v;
        std::string num;
        while (std::getline(linestream, num, ',')) 
            v.push_back(stoi(num));
        
        //std::cout << rowString << " " << v[1] << std::endl;
        rows.push_back({rowString, v});
    }

    ull  sum1 = 0;
    for (auto r : rows) {
        std::map<std::tuple<ull, ull, ull>,ull> m;
        sum1 += countCombinations(m, r, 0, 0, 0);
    }

    std::cout << "Part 01: " << sum1 << "\n";
    
}


void part02(std::vector<std::string> inputLines) {
    ull result(0);
    ull size = inputLines.size();
    std::vector<Row> rows;
    for(ull i=0;i< size;i++){
        std::string s;
        std::string rowString;
        std::stringstream linestream(inputLines.at(i));
        std::getline(linestream, s, ' ');
        /*
        
        */

        std::vector<ull> v;
        std::string num;
        while (std::getline(linestream, num, ',')) {
            v.push_back(stoi(num));
            
        }
        //std::cout << rowString << " " << v[1] << std::endl;
        
        rows.push_back({s, v});
    }
    ull  sum2 = 0;
    for (auto r : rows) {
        std::vector<ull> unfoldedNums;
        std::string unfoldedString;
        
        for (int i = 0; i < 5; i++) {
            unfoldedNums.insert(unfoldedNums.end(), r.counters.begin(), r.counters.end());
            unfoldedString.append(r.rowMap);
            if (i < 4)
                unfoldedString.append("?");
        }
        Row temp{unfoldedString,unfoldedNums};
        std::map<std::tuple<ull, ull, ull>,ull> m;
        sum2 += countCombinations(m, temp,0, 0, 0);
    }

    std::cout << "Part 02: " << sum2 << "\n";

}

int main() {
    std::ifstream inputFile("../input/day12.txt");
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
