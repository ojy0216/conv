#include "pool_3d.h"

#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<vector<vector<double>>> v = {
        {
            {1, 2, 3, 4, 5},
            {2, 3, 4, 5, 6},
            {3, 4, 5, 6, 7}
        },
        {
            {4, 5, 6, 7, 8},
            {5, 6, 7, 8, 9},
            {6, 7, 8, 9, 10}
        }
    };

    Pool3D p(v);
    p.avg_pool3D(2);

    auto out = p.get3dOutput();

    for(auto c : out){
        for(auto i : c){
            for(auto j : i)
                cout << j << " ";
            cout << endl;
        }
        cout << "-----\n";
    }
    p.printShape();
}