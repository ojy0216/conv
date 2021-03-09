#include "util.h"

#include <cmath>
using namespace std;

DV_2D Util::flatten(DV_3D v){
    vector<vector<double>> result(1, vector<double> (0));

    for(auto c : v){
        for(auto y : c){
            for(auto x : y)
                result[0].push_back(x);
        }
    }

    return result;
}

void Util::v_tanh(DV_3D& v){
    for(auto& c : v)
        v_tanh(c);
}

void Util::v_tanh(DV_2D& v){
    for(auto& y : v){
        for(auto& x : y)
            x = tanh(x);
    }
}

void Util::v_relu(DV_3D& v){
    for(auto& c : v)
        v_relu(c);
}

void Util::v_relu(DV_2D& v){
    for(auto& y : v){
        for(auto& x : y)
            x = x > 0 ? x : 0;
    }
}