#ifndef stockindex_h
#define stockindex_h
#include "IndexFormula.h"

class StockIndex
{
    IndexFormula formula;

    public:
        void init();

        bool CCI();
        bool Sonar();
        bool Sc();
        
        int GetEMA(int day);
};
#endif;
