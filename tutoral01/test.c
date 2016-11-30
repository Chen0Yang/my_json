#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "leptjson.h"

static int main_ret;
static int total;
static int  pass;

#define EXCEPT_EQ_BASE(equality, except, actual, format) \
    do {\
        total ++;
        if(equivalent)\
            pass++;\
        else{\
            fprintf(stderr,"%s:%d: except:" format "actual :"format "\n",__FILE__,__LINE__,except,actual);\
            main_ret = 1;\
        }\
    }while(0)

#define EXCEPT_EQ_INT(except
static void test_null (){

