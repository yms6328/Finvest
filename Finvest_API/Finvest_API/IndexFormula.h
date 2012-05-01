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
        int GetTodayCloseValue();
       // int GetPivotResValue1();
       // int GetPivotResValue2();

        void GetSonarValue();
    	void GetTrixValue();
    	int GetCCIValue();
        void GetVRValue();
        void GetRCIValue();
        void GetDisparityValue();
<<<<<<< HEAD
        int GetNCOValue();
        int GetPriceOSValue();
        int GetTADLineValue();
        int GetPrevADLineValue();
=======
		void Get60DisparityValue();
		void Get120DisparityValue();
	private:
		int GetSignalValue();
>>>>>>> e7d7d729ac383c91c9c63a9caba36539357c7316

    /* s -- hyeyeng.ahn - 2012. 04. 29 */
        int GetEMA(int day, int* data); // 지수이동평균
};

#endif