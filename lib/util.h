#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
using namespace std;

typedef vector<vector<vector<double>>> DV_3D;
typedef vector<vector<double>> DV_2D;

class Util{
public:
    DV_2D flatten(DV_3D v);

    void v_tanh(DV_3D& v);
    void v_tanh(DV_2D& v);

    void v_relu(DV_3D& v);
    void v_relu(DV_2D& v);
};

#endif