#include "../include/helperLogic.hpp"
#include <cmath>

colorStruct HSItoRGB(int i, int numElem){
    auto factor = 360.0f/numElem;
    auto h = i * factor;
    auto in = 78.0f;
    auto hp = h/60.0;
    auto s = 1.0f;
    auto z = 1.0f - fabs(fmod(hp, 2)-1);
    auto c = (3.0f * in * s)/1+z;
    auto x = c*z;
    double r = 0, g = 0, b = 0;
    if(hp >= 0 && hp <= 1){
        r = c;
        g = x;
        b = 0;
    }else if(hp >= 1 && hp <= 2){
        r = x;
        g = c;
        b = 0;
    }else if(hp >= 2 && hp <= 3){
        r = 0;
        g = c;
        b = x;
    }else if(hp >= 3 && hp <= 4){
        r = 0;
        g = x;
        b = c;
    }else if(hp >= 4 && hp <= 5){
        r = x;
        g = 0;
        b = c;
    }else{
        r = c;
        g = 0;
        b = x;
    }
    auto m = in * (1-s);
    colorStruct result{r+m, g+m, b+m};
    return result;
}
