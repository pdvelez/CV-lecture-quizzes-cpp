
#include "applyMedianFilter.h"
#include "exploreEdgeOptions.h"

int main(int argc, const char** argv) {

    int status = applyMedianFilter();

    if (status != 0){
        return status;
    }

    status = exploreEdgeOptions();

    return status;

}