/*
    IndexFomula.cpp
    * A set of fomulars
    * author: Finvest
*/
#include <iostream>
#include "IndexFomula.h"
#include "DBHelper.h"
#include <math.h>

using namespace std;

//RSI = {(14일간이 상승폭 합계) / (14일간의 상승폭 합계 + 14일간의 하락폭 합계) } * 10
int IndexFomula::GetRSIValue()
{
    //data1 = db_helper.GetData();
    //data 14 = sql_manager.GetData();
}

int IndexFomula::GetRatioValue() 
{
// 변화율 = {(오늘종가 - 12일전 종가) / 12일전 종가 } * 100

    int ratio = 0;
    int t_close;
    int prev_close;

    return ratio;
}

int IndexFomula::GetPivotValue()
{
//pivot point = (전일의 고가 + 전일의 저가 + 전일의 종가) / 3
    int y_high = db_helper.GetPrevHigh(1);
    int y_low = db_helper.GetPrevLow(1);
    int y_close = db_helper.GetPrevClose(1);
 
    cout << "test: " << y_high << endl;
    cout << "test: " << y_low << endl;
    cout << "test: " << y_close << endl;

    int ppoint = (y_high + y_low + y_close) / 3;
    int res1 = (2 * ppoint) - y_low;
    int sup1 = (2 * ppoint) - y_high;
    int res2 = (ppoint - sup1) + res1;
    int sup2 = ppoint - (res1 - sup1);

    return 1;
}

void IndexFomula::getSC_KValue()
{ 
    //n기간동안 하는거 포인터 해결 어떻게 하는지 ㅠㅠㅠ	
    //int sc_k = ((db_helper.GetClose() - db_helper.GetPeriodLow())/(db_helper.GetPeriodHigh()- dbhelper.GetPeriodLow()))*100;
}

void IndexFomula::getSC_DValue()
{
    int sc_d = 0;
    for(int i=0; i<3; i++)
    {
        //sc_d = ((db_helper.GetClose() - dbhelper.GetPeriodLow())/(dbhelper.GetPeriodHigh() - dbhelper.GetPeriodLow()))*100 + sc_d;		
    }
    sc_d = sc_d/3;
}

void IndexFomula::getCCIValue()
{
    int M = (db_helper.GetHigh() + db_helper.GetLow() + db_helper.GetClose()) / 3;
    int m;

    for(int i=0; i<20; i++)
    {
        m = ((db_helper.GetHigh() + db_helper.GetLow() + db_helper.GetClose()) / 3)+m;
    }

    m = m/20;

    int d;
    for(int i=0; i<20; i++)
    {
        d = abs(M-m) + d;
    }
    d = d/20;

    int cci = (M-m) / (d*0.015);
} 

void IndexFomula::getSonarValue()  //day는 10일을 추천
{
    int Sonar = (db_helper.GetClose() - db_helper.GetPrevClose(10)) / db_helper.GetPrevClose(10);
}

void IndexFomula::getSonarAve() //기간은 5일을 추천
{
    int Sonarave = 0;
    for(int i=0; i<5; i++)
    {
        Sonarave = ((db_helper.GetClose() - db_helper.GetPrevClose(10)) / db_helper.GetPrevClose(10))+Sonarave;
    }
    Sonarave = Sonarave/5;
}
