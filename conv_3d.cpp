#include "conv_3d.h"

#include <iostream>
#include <string>

#include <fstream>
#include <sstream>

using namespace std;

Conv3D::Conv3D(vector<vector<vector<double>>> v, string name, int c_out){
    conv_name = name;

    input_3d = v;
    c_in = v.size();
    this->c_out = c_out;
}

Conv3D::Conv3D(string name, int c_in, int c_out){
    conv_name = name;

    this->c_in = c_in;
    this->c_out = c_out;
}

void Conv3D::readBias(const string dir){
    ifstream infile(dir);

    while(!infile.eof()){
        string s, tok;

        getline(infile, s);
        if(s.empty())
            break;

        istringstream ss(s);
        while(getline(ss, tok, ' ')){
            istringstream os(tok);
            double d;
            os >> d;
            bias_3d.push_back(d);
        }
    }
    infile.close();
}

bool Conv3D::calc_3d(bool front){
    string kernel_name = "C:\\Users\\JY\\Desktop\\lenet\\" + conv_name;

    readKernel(kernel_name + "_weight_0_0.txt");
    if(!front){
        input_calc = input_3d[0];
        i_h = input_calc.size();
        i_w = input_calc[0].size();
    }
    calcOutputSize();
    
    cout << o_h << " " << o_w << endl;

    vector<vector<vector<double>>> result(c_out, vector<vector<double>>(o_h, vector<double> (o_w, 0.)));

    readBias(kernel_name + "_bias.txt");

    /*
    printInput();
    printKernel();
    for(auto i : bias_3d)
        cout << i << " ";;
    cout << endl;
    */

    for(auto i = 0; i < c_out; i++){
        for(auto j = 0; j < c_in; j++){
            if(!front)
                input_calc = input_3d[j];
            cout << "CALC 3D " << j << " " << i << endl;
            output.clear();
            kernel.clear();
            readKernel(kernel_name + "_weight_" + to_string(j) + "_" + to_string(i) + ".txt");
            calc(1, 0, bias_3d[i]);
            for(int dy = 0; dy < o_h; dy++){
                for(int dx = 0; dx < o_w; dx++)
                    result[i][dy][dx] += output[dy][dx];
            }
        }
    }
    output_3d = result;
}

vector<vector<vector<double>>> Conv3D::get3dOutput(){
    return output_3d;    
}

void Conv3D::printShape(){
    cout << "[Output] C: " << output_3d.size() << ", H: " << output_3d[0].size() << ", W: " << output_3d[0][0].size() << endl;
}