/*
   StockIndex.cpp
    * Implements index
    * Return up/down flag
    * author: Finvest
*/
#include <stdio.h>
#include <string>
#include "DBAccess.h"
#include "StockIndex.h"
#include "IndexFormula.h"

void StockIndex::init()
{
    formula.init();
}

/*
    Index List
        bool RSI(); // RSI
        bool MACD(); // MACD
        bool Stochastics(); // 스토캐스틱
        bool RateOfChange(); // 변화율
        bool PivotPoint(); // Pivot Point 
        bool SonarMomentum(); // Sonar Momentum
        bool TRIX(); // TRIX
        bool CCI(); // CCI
        bool VR(); // VR
        bool RCI(); // RCI
        bool Disparity(); // 이격도
        bool NCO();//NCO
        bool PriceOS(); //Price Oscillator 
        bool ADLine(); //ADLine 
*/

bool StockIndex::RSI()
{
    return false;
}

bool StockIndex::MACD()
{
    return false;
}

bool StockIndex::Stochastics()
{
    return false;
}

bool StockIndex::RateOfChange()
{
    formula.GetRatioValue();
    return false;
}

bool StockIndex::PivotPoint()
{
    printf("Pivot \n");
    bool buying_flag = false;;
    printf("pivot value: %d \t", formula.GetPivotValue());
    printf("pivot value: %d \n", formula.GetTodayCloseValue());

    if(formula.GetPivotValue() < formula.GetTodayCloseValue())
    {
       buying_flag = true;
    }
    else
    {
       buying_flag = false;
    }
    return buying_flag;
}


bool StockIndex::SonarMomentum()
{
    // formula.GetSonarValue()
    return false;
}

bool StockIndex::TRIX()
{
    return false;
}

bool StockIndex::CCI()
{
    printf("CCI value: %d \n", formula.GetCCIValue());
    bool buying_flag = false;;

    if(formula.GetCCIValue() > 100)
    {
	    buying_flag = true;
    }
    else if(formula.GetCCIValue() < -100)
    {
        buying_flag = false;
    }
    return buying_flag;
}

bool StockIndex::VR()
{
    return false;
}

bool StockIndex::RCI()
{
    return false;
}

bool StockIndex::Disparity()
{
    return false;
}

bool StockIndex::NCO()
{
    printf("NCO value: %d \n", formula.GetNCOValue());
    bool buying_flag = false;;

    if(formula.GetNCOValue() > 0){
     buying_flag = true;
    }
    else if(formula.GetNCOValue() < 0){
     buying_flag = false;
    }

    return buying_flag;
}

bool StockIndex::PriceOS()
{
    printf("PriceOS value: %d \n", formula.GetPriceOSValue());
    bool buying_flag = false;;

    if(formula.GetPriceOSValue() > 0)
    {
        buying_flag = true;
    }
    else
    {
        buying_flag = false;
    }

    return buying_flag;
}

bool StockIndex::ADLine()
{
    printf("ADLine value: %d \t \%d \n", formula.GetTADLineValue(), formula.GetPrevADLineValue());
    bool buying_flag = false;;

    if(formula.GetTADLineValue() > formula.GetPrevADLineValue()){
        buying_flag = true;
    }
    else if(formula.GetTADLineValue() < formula.GetPrevADLineValue()){
        buying_flag = false;
    }

    return buying_flag;
}

/*
    private
*/
