#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

class Matrix{
    private:
        const int maxLength = 200;
        const int maxHeigth = 200;
    public:
        std::string input[200];
        int height{}; 
        Matrix()
            : height{0} {}
        void appendChar(char a, int i){
            input[i].push_back(a);
        }
        void setChar(char a, int i, int j){
            input[i][j] = a;
        }
        void setString(std::string a, int i){
            input[i] = a;
        }
        char getChar(int i, int j){
            return input[i][j];
        }
        std::string getString(int i){
            return input[i];
        }
};
int findSymbol(Matrix input, std::string symbols);
int findNumber(Matrix input, int posI, int posJ);
std::string constructNumber(Matrix &input, int posI, int posJ);

int main(){
    std::ifstream in("input.txt");
    std::string symbols {"+-*/=@#$%&"};
    std::string line;
    Matrix input;
    while (std::getline(in, line)) {
        input.setString(line, input.height++);
    }
    for(int i=0;i<input.height;i++){
        std::cout << input.getString(i) << '\n';    
    }
    std::cout << "Answer is: " << findSymbol(input, symbols);
}
int findSymbol(Matrix input, std::string symbols){
    int sum = 0;
    for(int i=0;i<input.height;i++){
        for(size_t j=0;j<input.getString(0).length();j++){
            int idx = symbols.find(input.getChar(i, j));
            if(idx>-1 && idx < 10){
                sum+=findNumber(input, i, j);
            }
        }
    }
    return sum;
}
int findNumber(Matrix input, int posI, int posJ){
    int sum = 0;
    for(int i=posI-1;i<=posI+1;i++){
        for(int j=posJ-1;j<=posJ+1;j++){
            if(isdigit(input.getChar(i, j))!=0){
                sum+=std::stoi(constructNumber(input, i, j));
            }
        }
    }
    return sum;
}
/*
 * finds the whole number from initial digit position
 * @param input - input matrix
 * @param posI - digit line number
 * @param posJ - digit column number
 * @return the whole number
 */
std::string constructNumber(Matrix &input, int posI, int posJ){
    std::string ans{};
    ans.push_back(input.getChar(posI, posJ));
    int a{0}, b{0};
    while(isdigit(input.getChar(posI, posJ - ++a))){
        ans.insert(0, 1, input.getChar(posI, posJ-a));
        input.setChar('.', posI, posJ-a);
    }    
    while(isdigit(input.getChar(posI, posJ + ++b))){
        ans.push_back(input.getChar(posI, posJ+b));
        input.setChar('.', posI, posJ+b);
    }
    input.setChar('.', posI, posJ);
    return ans;
}
