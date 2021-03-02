#ifndef __FC_H__
#define __FC_H__

#include <vector>
#include <string>
using namespace std;

class FC{
    vector<vector<double>> input;
    vector<vector<double>> weight;
    vector<double> bias;
    vector<vector<double>> output;

    int i_h, i_w;
    int w_h, w_w;
    int o_h, o_w;    

public:
    FC(vector<vector<double>> v);
    FC(){};

    vector<vector<double>> read(const string dir);
    void readInput(const string dir);
    void readWeight(const string dir);
    void readBias(const string dir);

    void print(vector<vector<double>> v);
    void printInput();
    void printWeight();
    void printBias();
    void printOutput();

    vector<vector<double>> getOutput();

    void calc();
};

#endif