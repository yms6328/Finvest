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
*/

bool StockIndex::CCI()
{
    bool buying_flag;

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

/*
    Pivot Point
    보류
*/

bool StockIndex::Sonar()
{
    // formula.GetSonarValue()
    if(34 > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




/*
    private
*/
int StockIndex::GetEMA(int day)
{
    return formula.GetEMA(day);
}