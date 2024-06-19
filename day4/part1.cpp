#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

class Card{
    private:
        std::string line;
        int winNum[100];
        int winSize{0};
        int haveNum[100];
        int haveSize{0};
        void splitToArray(std::string input, int A[], int &n){
            for(size_t i=0;i<input.length();i+=3){
                A[n++] = std::stoi(input.substr(i, 2));
            }
        }
        int findWinners(){
            int k=0;
            for(int i=0;i<winSize;i++){
                for(int j=0;j<haveSize;j++){
                    if(winNum[i] == haveNum[j])
                        k++;
                }
            }
            return k;
        }
    public:
        int idx{-1};
        Card(std::string input):
            line{input}
        {}
        int getWinSize(){
            return winSize;
        }
        int getHaveSize(){
            return haveSize;
        }
        void parseInput(){
            line = line.substr(line.find(':')+2);
            //Winning numbers
            std::string win{line.substr(0, line.find('|')-1)};
            splitToArray(win, winNum, winSize);
            //Your numbers
            std::string have{line.substr(line.find('|')+2)};
            splitToArray(have, haveNum, haveSize);
        }
        int calcPoints(){
            return pow(2, findWinners()-1);
        }
        int winningNumber(){
            return findWinners();
        }
};
std::ifstream in("input.txt");

int main (int argc, char *argv[]) {
    std::string line{};
    [[maybe_unused]] int sum{0}, k{0};
    while (std::getline(in, line)){
        Card A = Card(line);
        A.idx = k;
        k++;
        A.parseInput();
    }
}


