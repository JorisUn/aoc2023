#include <algorithm>
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
class TargetNum{
    public:
        //Start location values
        int posI, posJ;
        int value;
        TargetNum(int i, int j, int num)
            : posI{i}, posJ{j}, value{num}
        {}
        TargetNum(){}
};
class Star{
    public:
        TargetNum Numbers[100];
        int n;
        int posI, posJ;
        Star(int i, int j)
        : n{0}, posI{i}, posJ{j}
        {}
        bool exists(int i, int j, int value){
            for(int k=0;k<n;k++){
                if(Numbers[k].value == value && Numbers[k].posI == i
                        && Numbers[k].posJ == j)
                    return true;
            }
            return false;
        }
        void addNum(int i, int j, int value){
            if(!exists(i, j, value))
                Numbers[n++] = TargetNum(i, j, value);
        }
        void addNum(TargetNum a){
            if(!exists(a.posI, a.posJ, a.value))
                Numbers[n++] = a;
        }
        int result(){
            if(n!=2)
                return 0;
            int temp{1};
            for(int i=0;i<n;i++){
                temp*= Numbers[i].value;
            }
            return temp;
        }
};
int findSymbol(Matrix input);
int findNumber(Matrix input, Star &A);
TargetNum constructNumber(Matrix &input, int posI, int posJ);

int main(){
    std::ifstream in("input.txt");
    std::string line;
    Matrix input;
    while (std::getline(in, line)) {
        input.setString(line, input.height++);
    }
    auto ans = findSymbol(input);
    std::cout << "Answer is: " << ans << '\n';
    //for(int i=0;i<input.height;i++)
    //    std::cout << input.getString(i) << '\n';
}
int findSymbol(Matrix input){
    int sum = 0;
    for(int i=0;i<input.height;i++){
        for(size_t j=0;j<input.getString(0).length();j++){
            if(input.getChar(i, j) == '*'){
                Star A = Star(i, j);
                sum+=findNumber(input, A);
            }
        }
    }
    return sum;
}
int findNumber(Matrix input, Star &A){
    for(int i=A.posI-1;i<=A.posI+1;i++){
        for(int j=A.posJ-1;j<=A.posJ+1;j++){
            if(isdigit(input.getChar(i, j))){
                A.addNum(constructNumber(input, i, j));
            }
        }
    }
    return A.result();
}
/*
 * finds the whole number from initial digit position
 * @param input - input matrix
 * @param posI - digit line number
 * @param posJ - digit column number
 * @return the whole number
 */
TargetNum constructNumber(Matrix &input, int posI, int posJ){
    std::string ans{};
    ans.push_back(input.getChar(posI, posJ));
    int a{0}, b{0};
    //frist pos = posI, posJ - a
    while(isdigit(input.getChar(posI, posJ - ++a))){
        ans.insert(0, 1, input.getChar(posI, posJ-a));
        //input.setChar('d', posI, posJ-a);
    }    
    while(isdigit(input.getChar(posI, posJ + ++b))){
        ans.push_back(input.getChar(posI, posJ+b));
        //input.setChar('d', posI, posJ+b);
    }
    TargetNum T = TargetNum(posI, posJ-a, std::stoi(ans));
    return T;
}
