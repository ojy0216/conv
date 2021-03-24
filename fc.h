#ifndef __FC_H__
#define __FC_H__

#include <vector>
#include <string>
using namespace std;

class FC{
    vector<vector<double>> input;
    vector<vector<double>> weight;
    vector<vector<double>> weight_t;
    vector<double> bias;
    vector<vector<double>> output;

    int i_h, i_w;
    int w_h, w_w;
    int wt_h, wt_w;
    int o_h, o_w;    

    string weight_dir;

public:
    FC(string weightDir, string name, vector<vector<double>> v);
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

    void calc(bool manual = false);
};

#endif