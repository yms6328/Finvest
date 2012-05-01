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

    if(st_index.CCI())
    {
        printf("CCI Recommended \n");
    }
    else
    {
        printf("CCI false \n");
    }

    if(st_index.ADLine())
    {
        printf("ADLine Recommended \n");
    }
    else
    {
        printf("ADLine false \n");
    }

    if(st_index.Disparity())
    {
        printf("Disparity Recommended \n");
    }
    else
    {
        printf("Disparity false \n");
    }

    if(st_index.MACD())
    {
        printf("MACD Recommended \n");
    }
    else
    {
        printf("MACD false \n");
    }

    if(st_index.NCO())
    {
        printf("NCO Recommended \n");
    }
    else
    {
        printf("NCO false \n");
    }

    if(st_index.PivotPoint())
    {
        printf("Pivot Recommended \n");
    }
    else
    {
        printf("Pivot false \n");
    }

    if(st_index.PriceOS())
    {
        printf("PriceOS Recommended \n");
    }
    else
    {
        printf("PriceOS false \n");
    }

    if(st_index.RateOfChange())
    {
        printf("RateOfChange Recommended \n");
    }
    else
    {
        printf("RateOfChange false \n");
    }

    if(st_index.RCI())
    {
        printf("RCI Recommended \n");
    }
    else
    {
        printf("RCI false \n");
    }

    if(st_index.RSI())
    {
        printf("RSI Recommended \n");
    }
    else
    {
        printf("RSI false \n");
    }

    if(st_index.SonarMomentum())
    {
        printf("Sonar Recommended \n");
    }
    else
    {
        printf("Sonar false \n");
    }

    if(st_index.Stochastics())
    {
        printf("Stochastic Recommended \n");
    }
    else
    {
        printf("Stochastic false \n");
    }

    if(st_index.TRIX())
    {
        printf("TRIX Recommended \n");
    }
    else
    {
        printf("TRIX false \n");
    }

    if(st_index.VR())
    {
        printf("VR Recommended \n");
    }
    else
    {
        printf("VR false \n");
    }

    return 0;
}