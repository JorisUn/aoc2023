#include <fstream>
#include <iostream>
#include <string>

bool parseInput(std::string input);
bool splitCase(std::string set);
bool possibleCase(int num, std::string value);

std::ifstream in("input.txt");
int main(){
    std::string input;
    int sum = 0;
    int lineNum = 1;
    while (std::getline(in, input)) {
        if(parseInput(input))
            sum += lineNum;
        lineNum++;
    }
    std::cout << sum << '\n';
}
bool parseInput(std::string input){
    std::string set{};
    // false - impossible, true - possible
    input = input.substr(input.find(':')+2);
    while(input.length()>0){
        int delim = input.find(';');
        if(delim == -1){
            if(!splitCase(input)) return false;
            break;
        }
        if(!splitCase(input.substr(0, delim))) return false;
        input = input.substr(delim+2);
    }
    return true;
} 
bool splitCase(std::string set){
    while(set.length()>0){
        int delim1 = set.find(',');
        if(delim1 == -1){
            int delim2 = set.find(' ');
            if(!possibleCase(std::stoi(set.substr(0, delim2)),set.substr(delim2+1)))
                return false;
            break;
        }
        std::string buffer = set.substr(0, delim1);
        set = set.substr(delim1+2);
        int delim2 = buffer.find(' ');
        int num = std::stoi(buffer.substr(0, delim2));
        if(!possibleCase(num, buffer.substr(delim2+1)))
            return false;
    }
    return true;
}
bool possibleCase(int num, std::string value){
    if((value == "red" && num > 12) 
        || (value == "green" && num > 13)
        || (value == "blue" && num > 14))
            return false;
    else return true;
}
