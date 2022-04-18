//
// Created by Eideann on 18/4/22.
//

#include "../include/utils.h"

unsigned utils_concatenate(int a, int b){
    int p = 10;

    while(b >= p){
        p *= 10;
    }
    return a * p + b;
}