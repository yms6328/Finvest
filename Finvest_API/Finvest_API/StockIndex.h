#ifndef stockindex_h
#define stockindex_h
#include "IndexFormula.h"

class StockIndex
{
    IndexFormula formula;

    public:
        void init();

        bool RSI(); // RSI
        bool MACD(); // MACD ==보류
        bool Stochastics(); // 스토캐스틱 ==완성
        bool RateOfChange(); // 변화율 ==완성
        bool PivotPoint(); // Pivot Point ==보류 --> 우선완성
        bool SonarMomentum(); // Sonar Momentum ==보류
        bool TRIX(); // TRIX ==보류
        bool CCI(); // CCI ==완성
        bool VR(); // VR
        bool RCI(); // RCI
        bool Disparity(); // 이격도
        bool NCO(); //NCO ==완성
        bool PriceOS(); //Price Oscillator ==완성
        bool ADLine(); //ADLine ==완성
};
#endif;
