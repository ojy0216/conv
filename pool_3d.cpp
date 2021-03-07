#include "pool_3d.h"

#include <iostream>
using namespace std;

Pool3D::Pool3D(vector<vector<vector<double>>> v){
    input_3d = v;
    channel = v.size();

    i_h = v[0].size();
    i_w = v[0][0].size();
}

bool Pool3D::avg_pool3D(int kernelSize){
    return avg_pool3D({kernelSize, kernelSize});
}

bool Pool3D::avg_pool3D(list<int> kernelSize){
    k_h = kernelSize.front();
    k_w = kernelSize.back();

    stride_h = k_h;
    stride_w = k_w;

    if(!calcOutputSize())
        return false;

    for(auto c = 0; c < channel; c++){
        v_out.clear();
        avg_pool(input_3d[c], kernelSize);
        output_3d.push_back(getOutput());
    }
    return true;
}

vector<vector<vector<double>>> Pool3D::get3dOutput(){
    return output_3d;
}

void Pool3D::printShape(){
    cout << "[Output] C: " << output_3d.size() << ", H: " << output_3d[0].size() << ", W: " << output_3d[0][0].size() << endl;
}