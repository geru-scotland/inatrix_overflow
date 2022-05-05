//
// Created by Gerun on 18/4/22.
//

#include "utils.h"

unsigned utils_concatenate(int a, int b){
    int p = 10;

    while(b >= p){
        p *= 10;
    }
    return a * p + b;
}