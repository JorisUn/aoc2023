#include <algorithm>
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
            int n=0;
            for(int i=0;i<winSize;i++){
                for(int j=0;j<haveSize;j++){
                    if(winNum[i] == haveNum[j])
                        n++;
                }
            }
            return n;
        }
    public:
        int idx{-1};
        Card(std::string input):
            line{input}
        {}
        Card(){}
        void setLine(std::string ln){
            line = ln;
        }
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
int columnSum(int column[], int i);
void calcWeights(Card A[], int n);
std::ifstream in("input.txt");
std::ofstream out("results.txt");

int main (int argc, char *argv[]) {
    std::string line{};
    Card A[200];
    [[maybe_unused]] int sum{0}, n{0};
    while (std::getline(in, line)){
        A[n] = Card(line);
        A[n].idx = n;
        A[n].parseInput();
        n++;
    }

    calcWeights(A, n);
}
int countWin(Card A[], int n){
    for(int i=0;i<n;i++){
        A[i].winningNumber();
    }
    return 0;
}
void calcWeights(Card A[], int n){
    int valuesA[201][200];
    //Clearing matrix;
    for(int i=0;i<n+1;i++){
        for(int j=0;j<n;j++){
            valuesA[i][j]=0;
        }
    }
    for(int j=0;j<n;j++)
        valuesA[0][j] = 1;
    for(int i=1;i<n+1;i++){
        for(int j=i;j<i+A[i-1].winningNumber();j++){
            int sum{0};
            for(int k=0;k<i;k++)
                sum+=valuesA[k][j-1];
            valuesA[i][j] = sum;
        }
    }
    int sum = 0;
    for(int i=0;i<n+1;i++){
        for(int j=0;j<n;j++){
           sum+=valuesA[i][j];
        }
    }
    std::cout << sum+198 << '\n';
}


