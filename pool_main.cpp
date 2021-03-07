#include "pool.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    vector<vector<double>> v = {
        {1, 2, 3, 4, 5, 6, 7},
        {2, 3, 4, 5, 6, 7, 8},
        {3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 10},
        {5, 6, 7, 8, 9, 10, 11}
    };

    Pool p;

    p.avg_pool(v, 3);

    auto out = p.getOutput();

    for(auto i : out){
        for(auto j : i)
            cout << j << " ";
        cout << endl;
    }
}