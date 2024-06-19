#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int parseInput(std::string input);
void splitCase(std::string set, int values[], std::string colors[], int &n);
void possibleCase(int num, std::string color, int values[], std::string colors[], int &n);
int minPower(int values[], std::string colors[], int size);

std::ifstream in("input.txt");
int main(){
    std::string input;
    int sum = 0;
    while (std::getline(in, input)) {
        sum += parseInput(input);
    }
    std::cout << sum << '\n';
}
int parseInput(std::string input){
    std::string colors[100];
    int values[100];
    int size{0};
    std::string set{};
    input = input.substr(input.find(':')+2);
    while(input.length()>0){
        int delim = input.find(';');
        if(delim == -1){
            splitCase(input, values, colors, size);
            break;
        }
        splitCase(input.substr(0, delim), values, colors, size);
        input = input.substr(delim+2);
    }
    return minPower(values, colors, size);

} 
int minPower(int values[], std::string colors[], int size){
    //red, green, blue
    int max[3] {0, 0, 0};
    for(int i=0;i<size;i++){
        if(colors[i]=="red" && values[i] > max[0])
            max[0] = values[i];
        if(colors[i]=="green" && values[i] > max[1])
            max[1] = values[i];
        if(colors[i]=="blue" && values[i] > max[2])
            max[2] = values[i];
    }
    return max[0]*max[1]*max[2];
}
void splitCase(std::string set, int values[], std::string colors[], int &n){
    while(set.length()>0){
        int delim1 = set.find(',');
        if(delim1 == -1){
            int delim2 = set.find(' ');
            possibleCase(std::stoi(set.substr(0, delim2)),set.substr(delim2+1), values, colors, n);
            break;
        }
        std::string buffer = set.substr(0, delim1);
        set = set.substr(delim1+2);
        int delim2 = buffer.find(' ');
        int num = std::stoi(buffer.substr(0, delim2));
        possibleCase(num, buffer.substr(delim2+1), values, colors, n);
    }
}
void possibleCase(int num, std::string color, int values[], std::string colors[], int &n){
    values[n++] = num;
    colors[n-1] = color;
}
