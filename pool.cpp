#include "pool.h"

#include <iostream>
using namespace std;

bool Pool::avg_pool(vector<vector<double>> v, int kernelSize){
    return avg_pool(v, {kernelSize, kernelSize});
}

bool Pool::avg_pool(vector<vector<double>> v, list<int> kernelSize){
    v_calc = v;
    i_h = v.size();
    i_w = v[0].size();

    k_h = kernelSize.front();
    k_w = kernelSize.back();
    
    stride_h = k_h;
    stride_w = k_w;

    if(pad_h != 0 || pad_w != 0)
        pad();
        
    if(!calcOutputSize())
        return false;

    for(auto i = 0; i < o_h; i++){
        vector<double> o_row;
        for(auto j = 0; j < o_w; j++){
            double tmp = 0.;
            for(auto dy = 0; dy < k_h; dy++){
                for(auto dx = 0; dx < k_w; dx++)
                    tmp += v_calc[i * stride_h + dy][j * stride_w + dx];
            }
            tmp /= (k_h * k_w);
            o_row.push_back(tmp);
        }
        v_out.push_back(o_row);
    }    
    return true;
}

bool Pool::calcOutputSize(){
    bool avail = true;
    if(i_w + 2 * pad_w < k_w){
        cout << "Kernel Width Violation\n";
        avail = false;
    }
    if(i_h + 2 * pad_h < k_h){
        cout << "Kernel Height Violation\n";
        avail = false;
    }
    if(pad_h < 0 || pad_w < 0){
        cout << "Padding Violation\n";
        avail = false;
    }

    o_h = (i_h + 2 * pad_h - k_h) / stride_h + 1;
    o_w = (i_w + 2 * pad_w - k_w) / stride_w + 1;

    return avail;
}

void Pool::pad(){
    for(auto& row : v_calc){
        for(int i = 0; i < pad_w; i++){
            row.insert(row.begin(), 0.);
            row.push_back(0.);
        }
    }

    vector<double> pad_row(i_w + 2 * pad_w, 0.);
    for(auto i = 0; i < pad_h; i++){
        v_calc.insert(v_calc.begin(), pad_row);
        v_calc.push_back(pad_row);
    }
}

void Pool::setStride(int stride){
    stride_h = stride;
    stride_w = stride;
}

void Pool::setStride(list<int> stride){
    stride_h = stride.front();
    stride_w = stride.back();
}

void Pool::setPad(int pad){
    pad_h = pad;
    pad_w = pad;
}

void Pool::setPad(list<int> pad){
    pad_h = pad.front();
    pad_w = pad.back();
}

vector<vector<double>> Pool::getOutput(){
    return v_out;
}