#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

int convertNumber(std::string initial);
int getNumber(std::string input);

std::ifstream in("input.txt");

int main(){
    std::string input;
    int sum = 0;
    while(in >> input){
        sum+= getNumber(input);
    }
    std::cout << sum << '\n';
}

int getNumber(std::string input){
    std::string buffer{};
    for(std::size_t i=0;i<input.length();i++){
        if(isdigit(input[i])){
            buffer += input[i];
        }
    }
    return convertNumber(buffer);
}

int convertNumber(std::string initial){
    if(initial.length() == 1) return std::stoi(initial)*10 + std::stoi(initial);
    if(initial.length() == 2) return std::stoi(initial);
    std::string ans{" "};
    ans.push_back(initial[0]);
    ans.push_back(initial[initial.length()-1]);
    return std::stoi(ans);
}
