#ifndef INDEXFOMULA_H
#define INDEXFOMULA_H
#include <string>
#include "DBHelper.h"

class IndexFomula
{
    DBHelper db_helper;
    public:
        int GetRSIValue();
        int GetRatioValue();
	    int GetPivotValue();

    	void getSC_KValue();
	    void getSC_DValue();

    	void getSonarValue();
    	void getSonarAve();

    	void getCCIValue();
};

#endif;
