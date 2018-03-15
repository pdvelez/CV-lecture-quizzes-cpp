/*
Code that demonstrates how a template can be found by performing a 2D cross
correlation.

Required libraries:
- opencv
- dlib
*/

#include <iostream>
#include <vector>
#include <limits>
#include <dlib/matrix.h>

using namespace dlib;
using namespace std;

std::vector<int> findTemplate1D(const matrix<int>&, const matrix<int>&);
std::vector<int> matrixArgMax(const matrix<int>&);

int main(int argc, char const *argv[]) {

    matrix<int> s(1,15);
    matrix<int> t(1,3);

    s = -1, 0, 0, 5, 1, 1, 0, 0, -1, -7, 2, 1, 0, 0, -1;
    t = -1, -7, 2;

    cout << "Signal:" << endl;
    cout << s << endl;

    cout << "Template:" << endl;
    cout << t << endl;

    std::vector<int> index = findTemplate1D(s, t);

    cout << "Raw Index:" << endl;
    cout << index[1] << endl;

    return 0;
}

std::vector<int> matrixArgMax(const matrix<int>& inputMatrix)
{
    int maxVal = std::numeric_limits<int>::min();
    int maxRow = 0;
    int maxCol = 0;

    for (int i = 0; i < inputMatrix.nr(); i++)
    {
        for (int j = 0; j < inputMatrix.nc(); j++)
        {
            int tempVal = inputMatrix(i, j);

            if (tempVal > maxVal)
            {
                maxVal = tempVal;
                maxRow = i;
                maxCol = j;
            }

        }
    }

    std::vector<int> argMax;

    argMax = {maxRow, maxCol};

    return argMax;
}

std::vector<int> findTemplate1D(const matrix<int>& signalMatrix, const matrix<int>& templateMatrix)
{
    matrix<int> corr1D;

    corr1D = xcorr_valid(signalMatrix, templateMatrix);

    std::vector<int> rawIndex = matrixArgMax(corr1D);

    return rawIndex;
}
