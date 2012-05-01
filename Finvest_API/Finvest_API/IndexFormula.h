#ifndef INDEXFORMULA_H
#define INDEXFORMULA_H
#include <string>
#include "DBAccess.h"

class IndexFormula
{
    DBAccess db_acc;

    public:
        void init();
        int GetRSIValue();
        int GetMACDValue();
        int GetStochasticValue();
        int GetRatioValue();
	    int GetPivotValue();
        void GetSonarValue();
    	void GetTrixValue();
    	int GetCCIValue();
        void GetVRValue();
        void GetRCIValue();
        void GetDisparityValue();
		void Get60DisparityValue();
		void Get120DisparityValue();
	private:
		int GetSignalValue();

    /* s -- hyeyeng.ahn - 2012. 04. 29 */
        int GetEMA(int day, int* data); // 지수이동평균
};

#endif