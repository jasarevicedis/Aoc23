#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long  ull;

struct Range {
    ull value;
    ull range;
};



struct Row {
    ull destinationStart;
    ull sourceStart;
    ull length;

    bool inRange(ull value){
        return sourceStart <= value && value < sourceStart + length;
    }

    friend bool operator<(Row r1, Row r2) {
        return r1.sourceStart < r2.sourceStart;
    }
};

std::vector<Row> readInputSection(std::ifstream &input){
    std::vector<Row> rows;

    std::string sectionName;
    std::getline(input,sectionName);

    while (!input.eof()) {
        std::string line;
        std::getline(input, line);
        if (line.empty()) {
            break;
        }

        std::istringstream linestream(line);
        ull destination, source, range;

        linestream >> destination;
        linestream >> source;
        linestream >> range;
        rows.push_back({destination,source,range});
    }

    std::sort(rows.begin(), rows.end());

    return rows;
}

std::vector<Range> seedsToRanges1(std::vector<ull> seedValues)
{
    std::vector<Range> seeds;
    ull size = seedValues.size();
    for (ull i = 0; i < size - 1; i++) {
        ull value = seedValues[i];
        ull range = 1;
        seeds.push_back({value,range});
    }
    return seeds;
}

std::vector<Range> seedsToRanges2(std::vector<ull> seedValues){
    std::vector<Range> seeds;
    ull size =seedValues.size();
    for (ull i = 0; i < size - 1; i++) {
        ull value = seedValues[i];
        i++;
        ull range = seedValues[i];
        seeds.push_back({value,range});
    }
    return seeds;
}

std::vector<Range> transformRange(std::vector<Range> ranges, std::vector<Row> rows)
{
    std::vector<Range> out;
    for (auto r : ranges) {
        ull start = r.value;
        ull count = r.range;

        for (auto row : rows) {

            
            if (start < row.sourceStart) {
                ull end = std::min(start + count, row.sourceStart) - start;

                out.push_back({start,end});

                count -= end;
                start = start + end;

                if (!count)
                    break; 
            }

            if (row.sourceStart <= start && start < row.sourceStart + row.length) {
                ull end = std::min(start + count, row.sourceStart + row.length) - start;

                ull start2 = row.destinationStart + (start - row.sourceStart);
                out.push_back({start2,end});

                count -= end;
                start = start + end;

                if (!count)
                    break; 
            }

            
        }

        if (count)//not in maps
            out.push_back({start,count});
    }
    return out;
}

int main ()
{
    std::ifstream inputFile("../input/day05.txt");
    
    std::vector<ull> seeds;
    std::string line;
    std::getline(inputFile, line);
    std::istringstream linestream(line);

    std::string sectionTitle;
    linestream >> sectionTitle;

    std::string num;
    while (linestream >> num) {
        ull seedid = stol(num);
        seeds.push_back(seedid);
    }

    std::string blank;
    std::getline(inputFile, blank);
    std::vector<Row> soil = readInputSection(inputFile);
    std::vector<Row> fertilizer = readInputSection(inputFile);
    std::vector<Row> water = readInputSection(inputFile);
    std::vector<Row> light = readInputSection(inputFile);
    std::vector<Row> temperature = readInputSection(inputFile);
    std::vector<Row> humidity = readInputSection(inputFile);
    std::vector<Row> location = readInputSection(inputFile);


    std::vector<Range> ranges = seedsToRanges1(seeds);
    ranges = transformRange(ranges, soil);
    ranges = transformRange(ranges, fertilizer);
    ranges = transformRange(ranges, water);
    ranges = transformRange(ranges, light);
    ranges = transformRange(ranges, temperature);
    ranges = transformRange(ranges, humidity);
    ranges = transformRange(ranges, location);

    ull lowest = std::numeric_limits<ull>::max();
    for (auto &r : ranges) {
        lowest = std::min(r.value, lowest);
    }

    std::cout << "Part 01: " << lowest << std::endl;

    ranges = seedsToRanges2(seeds);
    ranges = transformRange(ranges, soil);
    ranges = transformRange(ranges, fertilizer);
    ranges = transformRange(ranges, water);
    ranges = transformRange(ranges, light);
    ranges = transformRange(ranges, temperature);
    ranges = transformRange(ranges, humidity);
    ranges = transformRange(ranges, location);

    for (auto &r : ranges) {
        lowest = std::min(r.value, lowest);
    }

    
    std::cout << "Part 02: " << lowest << std::endl;

    return 0;
}
/*
int main(){
    std::ifstream inputFile("../input/day05.txt");
    std::vector<std::string> inputLines;
    std::string inputLine;
    while(std::getline(inputFile,inputLine)) {
        inputLines.push_back(inputLine);
    }
    inputFile.close();

    part01(inputLines);
    part02(inputLines);
    return 0;
}*/
