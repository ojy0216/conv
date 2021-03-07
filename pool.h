#ifndef __POOL_H__
#define __POOL_H__

#include <vector>
#include <list>
using namespace std;

class Pool{
protected:
    vector<vector<double>> v_calc;
    vector<vector<double>> v_out;

    int i_h, i_w;
    int o_h, o_w;
    int k_h, k_w;

    int stride_h, stride_w;
    int pad_h = 0, pad_w = 0;
public:
    bool avg_pool(vector<vector<double>> v, int kernelSize);
    bool avg_pool(vector<vector<double>> v, list<int> kernelSize);

    bool calcOutputSize();

    void setStride(int stride);
    void setStride(list<int> stride);

    void setPad(int pad);
    void setPad(list<int> pad);

    void pad();

    vector<vector<double>> getOutput();
};

#endif