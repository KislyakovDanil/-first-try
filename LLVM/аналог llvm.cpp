#include <iostream>
using  namespace std;

int checker(int i){//аналог кода llvm
    for(int j = 0; j < 5; ++j){
        if (i == j){
            return j;
        }
    }
    return -1;
}

int main() {//вспомогательный код для проверки
    int i;
    cin >> i;
    cout << checker(i);
    return 0;
}