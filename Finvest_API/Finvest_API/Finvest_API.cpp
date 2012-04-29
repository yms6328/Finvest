/*
    Finvest_API.cpp
    * API test program
    * author: Finvest
    * jag9123@gmail.com
*/

#include <iostream>
#include <string>
#include "DBAccess.h"
#include "StockIndex.h"
using namespace std;

int main()
{
    StockIndex st_index;
    string name;
    st_index.init();
    st_index.GetEMA(5);
    return 0;
}