#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>



struct Node{
    std::string point;
    std::string left;
    std::string right;

    bool operator==(const Node& other) const {
        return point == other.point && left == other.left && right == other.right;
    }
};

void part01(std::vector<std::string> inputLines) {
    std::string directions;
    if(!inputLines.empty())
        directions =  inputLines[0];
    std::map<std::string, Node> nodes;
    int size=inputLines.size();
    for(int i=2;i<size;i++){
        Node current;
        current.point=inputLines.at(i).substr(0,3);
        current.left=inputLines.at(i).substr(7,3);
        current.right=inputLines.at(i).substr(12,3);
        nodes.insert(std::make_pair(current.point, current));

        //nodes[current.point] = current;
        //std::cout << current.point << " " << current.left << " " << current.right << std::endl;
    }
    //int i=0;
    int counter(0);
    size=nodes.size();
    int dirSize=directions.size();
    Node final=nodes.begin()->second;
    
    for(int i=0;i<dirSize;i++){
        
        if(directions[i]=='L'){     
            final=nodes[final.left];
            counter++;
            
        }
        else if(directions[i]=='R') {
           
            final=nodes[final.right] ;
            counter++;
  
        }
        
        
        if(final.point=="ZZZ")
            break;
        if(i==dirSize-1)
            i=-1;
    }
    std::cout << "Part01: "<<counter<<std::endl;;
}

long int lcm(long int a, long int b) {
    return (a * b) / std::__gcd(a, b);//algorithm lib
}

long int lcmOfVector(std::vector<long int> numbers) {
    long int result = numbers[0];
    for (int i = 1; i < numbers.size(); ++i) 
        result = lcm(result, numbers[i]);
    
    return result;
}
void part02(std::vector<std::string> inputLines) {
    std::string directions;
    if(!inputLines.empty())
        directions =  inputLines[0];
    std::map<std::string, Node> nodes;
    int size=inputLines.size();
    for(int i=2;i<size;i++){
        Node current;
        current.point=inputLines.at(i).substr(0,3);
        current.left=inputLines.at(i).substr(7,3);
        current.right=inputLines.at(i).substr(12,3);
        nodes.insert(std::make_pair(current.point, current));

        
    }
    long int counter(0);
    std::vector<long int> counters;
    for (auto n: nodes) {
        counter=0;
        Node node = n.second;
        if (node.point.back() == 'A') {
                        
            size=nodes.size();
            int dirSize=directions.size();
            Node final=node;
    
    for(int i=0;i<dirSize;i++){
        
        if(directions[i]=='L'){     
            final=nodes[final.left];
            counter++;
            
        }
        else if(directions[i]=='R') {
           
            final=nodes[final.right] ;
            counter++;
  
        }
        
        
        if(final.point.back()=='Z'){
            counters.push_back(counter);
            break;
        }
        if(i==dirSize-1)
            i=-1;
    }
        }
        
    }
    //for(auto c: counters)
        //std::cout << c <<std::endl;
    long int result = lcmOfVector(counters);
    std::cout << "Part02: "<< result <<std::endl;;
}

int main() {
    std::ifstream inputFile("../input/day08.txt");
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
