#include "fc.h"

#include <iostream>

#include <fstream>
#include <sstream>

#include <iomanip>

using namespace std;

FC::FC(string weightDir, string name, vector<vector<double>> v){
    weight_dir = weightDir + name;

    input = v;

    i_h = v.size();
    i_w = v[0].size();
}

vector<vector<double>> FC::read(const string dir){
    vector<vector<double>> tmp;

    ifstream infile(dir);

    if(!infile.is_open()){
        cout << "[File Open Error] : " << dir << endl;
        return tmp;
    }

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


void FC::readInput(const string dir){
    input = read(dir);

    i_h = input.size();
    i_w = input[0].size();
}

void FC::readWeight(const string dir){
    weight = read(dir);

    w_h = weight.size();
    w_w = weight[0].size();

    wt_h = w_w;
    wt_w = w_h;

    for(auto x = 0; x < w_w; x++){
        vector<double> tmp;
        for(auto y = 0; y < w_h; y++)
            tmp.push_back(weight[y][x]);
        weight_t.push_back(tmp);
    }
}

void FC::readBias(const string dir){
    ifstream infile(dir);

    if(!infile.is_open()){
        cout << "[File Open Error] : " << dir << endl;
        return;
    }

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
            bias.push_back(d);
        }
    }
    infile.close();
}

void FC::print(vector<vector<double>> v){
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

void FC::printInput(){
    cout << "Input: (" << i_h << ", " << i_w << ")\n";
    print(input);
}

void FC::printWeight(){
    cout << "Weight: (" << w_h << ", " << w_w << ")\n";
    print(weight);
}

void FC::printBias(){
    cout << "Bias: (" << bias.size() << ")\n";
    cout << "[";

    cout << fixed;
    cout.precision(8);
    
    for(auto i = 0; i < bias.size(); i++){
        if(i != 0)
            cout << " ";
        cout << bias[i];
    }
    cout << "]\n";
    cout << resetiosflags(cout.flags());
}

void FC::printOutput(){
    cout << "Output: (" << o_h << ", " << o_w << ")\n";
    print(output);
}

vector<vector<double>> FC::getOutput(){
    return output;
}

void FC::calc(bool manual){
    if(!manual){
        readWeight(weight_dir + "_weight.txt");
        readBias(weight_dir + "_bias.txt");
    }

    o_h = i_h;
    o_w = wt_w;

    if(bias.size() != o_w){
        bias.clear();
        for(auto i = 0; i < o_w; i++)
            bias.push_back(0.);
    }

    for(auto i = 0; i < o_h; i++){
        vector<double> o_row;
        for(auto j = 0; j < o_w; j++){
            double sum = 0.;
            for(auto k = 0; k < i_w; k++)
                sum += input[i][k] * weight_t[k][j];
            o_row.push_back(sum + bias[j]);
        }
        output.push_back(o_row);
    }
}