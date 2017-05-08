
#include "blend2images.h"
#include "colorPlanes.h"

int main(int argc, const char** argv) {

    int status = blend2Images();

    if (status != 0){
        return status;
    }

    status = colorPlanes();

    return status;

}