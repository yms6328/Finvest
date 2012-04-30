#ifndef stockindex_h
#define stockindex_h
#include "IndexFormula.h"

class StockIndex
{
    IndexFormula formula;

    public:
        void init();

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
        
        int GetEMA(int day);
};
#endif;
