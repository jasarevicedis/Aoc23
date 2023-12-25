#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

typedef unsigned long long int ull;

std::map<char, int> letters = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

std::vector<std::string> parseRules(std::string line, int position = 0){
    std::vector<std::string> rules;
    int space = 0;
    line = line.substr(0, line.size() - 1);
    while (space != -1){
        space = line.find(',', position);
        rules.push_back(line.substr(position, space - position));
        position = space + 1;
    }
    return rules;
}

std::string getNextLocation(std::vector<std::string> rules, std::vector<int> properties){
    int ruleIndex = 0;
    while (ruleIndex < rules.size() - 1){
        std::string currRule = rules[ruleIndex];
        int property = properties[letters[currRule[0]]];
        char op = currRule[1];
        int colon = currRule.find(':');
        int comparison = stoi(currRule.substr(2, colon - 2));
        std::string location = currRule.substr(colon + 1, -1);
        if ((op == '<' && property < comparison) || (op == '>' && property > comparison))
            return location;
        ruleIndex++;
    }
    return rules[rules.size() - 1];
}

int getSum(const std::vector<int>& vect){
    int total = 0;
    for (int value : vect)
        total += value;
    return total;
}

bool processWorkflow(std::vector<int> properties, int workflowIndex, const std::vector<std::vector<std::string>>& rules, const std::vector<std::string>& locations){
    while (true){
        std::string nextLocation = getNextLocation(rules[workflowIndex], properties);
        if (nextLocation == "R")
            return false;
        else if (nextLocation == "A")
            return true;
        workflowIndex = std::find(locations.begin(), locations.end(), nextLocation) - locations.begin();
    }
}

ull calculateRanges(const std::vector<int>& ranges){
    ull total = 1;
    for (int i = 0; i < 4; i++)
        total *= ranges[2 * i + 1] - ranges[2 * i] + 1;
    return total;
}

ull calculateGoodRanges(const std::vector<std::vector<int>>& goodRanges){
    ull total = 0;
    for (const auto& range : goodRanges){
        std::vector<std::vector<int>> num;
        num.resize(4, std::vector<int>(4000, 0));
        for (int j = 0; j < 4; j++)
            for (int k = range[j * 2]; k <= range[j * 2 + 1]; k++)
                num[j][k - 1] = 1;
        std::vector<int> numEach = { 0, 0, 0, 0 };
        for (int i = 0; i < 4000; i++)
            for (int j = 0; j < 4; j++)
                numEach[j] += num[j][i];
        ull ruleRange = static_cast<ull>(numEach[0]) * numEach[1] * numEach[2] * numEach[3];
        total += ruleRange;
    }
    return total;
}

std::vector<std::vector<int>> processWorkflowPart2(std::vector<int> ranges, int workflowIndex, const std::vector<std::vector<std::string>>& rules, const std::vector<std::string>& locations){
    std::vector<std::vector<int>> goodRanges;
    std::vector<std::string> currentRules = rules[workflowIndex];
    int ruleIndex = 0;
    while (ruleIndex < currentRules.size() - 1){
        int done = 0;
        std::string currentRule = currentRules[ruleIndex];
        int property = letters[currentRule[0]];
        char op = currentRule[1];
        int colon = currentRule.find(':');
        int comparison = stoi(currentRule.substr(2, colon - 2));
        std::string location = currentRule.substr(colon + 1, -1);
        if (location == "A")
            done = 1;
        if (location == "R")
            done = 2;
        int newWorkflowIndex = std::find(locations.begin(), locations.end(), location) - locations.begin();

        if (op == '<'){
            std::vector<int> newRanges = ranges;
            newRanges[property * 2 + 1] = comparison - 1;
            ranges[property * 2] = comparison;
            if (done == 1)
                goodRanges.push_back(newRanges);
            else if (done == 0){
                std::vector<std::vector<int>> temp = processWorkflowPart2(newRanges, newWorkflowIndex, rules, locations);
                goodRanges.insert(goodRanges.end(), temp.begin(), temp.end());
            }
        }
        else if (op == '>'){
            std::vector<int> newRanges = ranges;
            newRanges[property * 2] = comparison + 1;
            ranges[property * 2 + 1] = comparison;
            if (done == 1)
                goodRanges.push_back(newRanges);
            else if (done == 0){
                std::vector<std::vector<int>> temp = processWorkflowPart2(newRanges, newWorkflowIndex, rules, locations);
                goodRanges.insert(goodRanges.end(), temp.begin(), temp.end());
            }
        }
        ruleIndex++;
    }
    std::string last = currentRules[currentRules.size() - 1];

    if (last == "A")
        goodRanges.push_back(ranges);
    else if (last != "R"){
        int newWorkflowIndex = std::find(locations.begin(), locations.end(), last) - locations.begin();
        std::vector<std::vector<int>> temp = processWorkflowPart2(ranges, newWorkflowIndex, rules, locations);
        goodRanges.insert(goodRanges.end(), temp.begin(), temp.end());
    }
    return goodRanges;
}

void part01(const std::vector<std::string>& locations, const std::vector<std::vector<std::string>>& rules, const std::vector<std::vector<int>>& properties){
    int totalCount = 0;
    int startPoint = std::find(locations.begin(), locations.end(), "in") - locations.begin();
    for (int i = 0; i < properties.size(); i++){
        if (processWorkflow(properties[i], startPoint, rules, locations)){
            totalCount += getSum(properties[i]);
        }
    }
    std::cout << "Part 1: " << totalCount << std::endl;
}

void part02(const std::vector<std::string>& locations, const std::vector<std::vector<std::string>>& rules, const std::vector<std::vector<int>>& properties){
    std::vector<int> initialRanges = {1, 4000, 1, 4000, 1, 4000, 1, 4000};
    int startPoint = std::find(locations.begin(), locations.end(), "in") - locations.begin();

    std::vector<std::vector<int>> goodRanges = processWorkflowPart2(initialRanges, startPoint, rules, locations);
    ull part2Total = calculateGoodRanges(goodRanges);
    std::cout << "Part 2: " << part2Total << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day19.txt");
    std::string inputLine;
    bool ruleSection = true;
    std::vector<std::string> locations;
    std::vector<std::vector<std::string>> rules;
    std::vector<std::vector<int>> properties;

    while (getline(inputFile, inputLine)) {
        if (ruleSection){
            if (inputLine.empty()){
                ruleSection = false;
                continue;
            }
            int pos = inputLine.find('{');
            locations.push_back(inputLine.substr(0, pos));
            rules.push_back(parseRules(inputLine.substr(pos + 1, -1)));
        }
        else{
            std::vector<int> temp;
            int pos = 3;
            std::string line = inputLine.substr(0, inputLine.size() - 1);
            for (int i = 0; i < 4; i++){
                int comma = line.find(',', pos);
                temp.push_back(stoi(line.substr(pos, comma - pos)));
                pos = comma + 3;
            }
            properties.push_back(temp);
        }
    }

    part01(locations, rules, properties);
    part02(locations, rules, properties);

    return 0;
}
