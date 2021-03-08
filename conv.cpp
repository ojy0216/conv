#include "conv.h"

#include <iostream>

#include <fstream>
#include <sstream>

#include <iomanip>

using namespace std;

Conv::Conv(vector<vector<double>> v){
    input = v;
    input_calc = input;

    i_h = input.size();
    i_w = input[0].size();
}

vector<vector<double>> Conv::read(const string dir){
    vector<vector<double>> tmp;

    ifstream infile(dir);

    while(!infile.eof()){
        string s, tok;
        vector<double> tmp_row;

        getline(infile, s);
        if(s.empty())
            break;

        istringstream ss(s);
        while(getline(ss, tok, ' ')){
            istringstream os(tok);
            double d;
            os >> d;
            tmp_row.push_back(d);
        }
        tmp.push_back(tmp_row);
    }
    infile.close();
    return tmp;
}

void Conv::readInput(const string dir){
    input = read(dir);

    i_h = input.size();
    i_w = input[0].size();
    input_calc = input;
}

void Conv::readKernel(const string dir){
    kernel = read(dir);
    
    k_h = kernel.size();
    k_w = kernel[0].size();
}

void Conv::print(vector<vector<double>> v){
    cout << "[[";

    cout << fixed;
    cout.precision(8);

    int h = v.size();
    int w = v[0].size();

    for(auto i = 0; i < h; i++){
        if(i != 0)
            cout << "  ";
        for(auto j = 0; j < w; j++){
            cout << v[i][j];
            if(j != w - 1)
                cout << " ";
        }
        cout << "]";
        if(i != h - 1)
            cout << '\n';
    }
    cout << "]\n";
    cout << resetiosflags(cout.flags());
}

void Conv::printInput(){
    cout << "Input: (" << i_h << ", " << i_w << ")\n";
    print(input); 
}

void Conv::printKernel(){
    cout << "Kernel: (" << k_h << ", " << k_w << ")\n";
    print(kernel);
}

void Conv::printOutput(){
    cout << "Output: (" << o_h << ", " << o_w << ")\n";
    print(output);
}

vector<vector<double>> Conv::getOutput(){
    return output;
}

void Conv::pad(){
    for(auto& row : input_calc){
        for(int i = 0; i < pad_w; i++){
            row.insert(row.begin(), 0.);
            row.push_back(0.);
        }
    }

    vector<double> pad_row(i_w + 2 * pad_w, 0.);
    for(auto i = 0; i < pad_h; i++){
        input_calc.insert(input_calc.begin(), pad_row);
        input_calc.push_back(pad_row);
    }
}

bool Conv::calcOutputSize(){
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

bool Conv::calc(double bias){
    if(!calcOutputSize())
        return false;

    if(pad_h != 0 || pad_w != 0)
        pad();

    for(auto i = 0; i < o_h; i++){
        vector<double> o_row;
        for(auto j = 0; j < o_w; j++){
            double tmp = 0;
            for(auto dy = 0; dy < k_h; dy++){
                for(auto dx = 0; dx < k_w; dx++)
                    tmp += input_calc[i * stride_h + dy][j * stride_w + dx] * kernel[dy][dx];
            }
            o_row.push_back(tmp + bias);
        }
        output.push_back(o_row);
    }
    return true;
}

void Conv::setStride(int stride){
    stride_h = stride;
    stride_w = stride;
}

void Conv::setStride(list<int> stride){
    stride_h = stride.front();
    stride_w = stride.back();
}

void Conv::setPad(int pad){
    pad_h = pad;
    pad_w = pad;
}

void Conv::setPad(list<int> pad){
    pad_h = pad.front();
    pad_w = pad.back();
}