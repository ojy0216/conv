#include "util.h"

#include <iostream>
#include <vector>
using namespace std;

int main(){
    DV_3D v = {
        {
            {-2.5, -1.5, -0.5},
            {0.5, 1.5, 2.5}
        },
        {
            {-1, -0.7, -0.3},
            {0.3, 0.7, 1}
        }
    };

    Util u;

    u.v_relu(v);

    for(auto c : v){
        for(auto y : c){
            for(auto x : y)
                cout << x << " ";
            cout << endl;
        }
    }

    auto f_v = u.flatten(v);

    for(auto y : f_v){
        for(auto x : y)
            cout << x << " ";
        cout << endl;
    }
}