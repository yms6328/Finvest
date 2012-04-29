/*
    IndexFormula.cpp
    * A set of fomulars
    * author: Finvest
*/
#include <stdio.h>
#include <string>
#include <math.h>
#include "DBAccess.h"
#include "IndexFormula.h"

void IndexFormula::init()
{
    printf("Enter the stock name: ");
    std::string name;
    std::cin >> name;
    if(db_acc.SetStock(name))
    {
        printf("Load data complete \n");
    }
}

//int IndexFormula::GetRSIValue()
//{
//    //RSI = {(14일간 상승폭 합계) / (14일간 상승폭 합계 + 14일간 하락폭 합계) } * 10
//}

int IndexFormula::GetRatioValue() 
{
    // 변화율 = {(오늘종가 - 12일전 종가) / 12일전 종가 } * 100
    int ratio;

    /* s --hyeyeng.ahn - 2012. 04. 29 */
    int t_close = db_acc.GetTodayClose();
    int p_close = db_acc.GetPrevClose(12);

    ratio = ((t_close - p_close) / p_close) * 100;
    /* e -- hyeyeng.ahn - 2012. 04. 29 */
    return ratio;
}

int IndexFormula::GetPivotValue()
{
    //pivot point = (전일의 고가 + 전일의 저가 + 전일의 종가) / 3
    int y_high = db_acc.GetPrevHigh(1);
    int y_low = db_acc.GetPrevLow(1);
    int y_close = db_acc.GetPrevClose(1);
 
    std::cout << "test: " << y_high << std::endl;
    std::cout << "test: " << y_low << std::endl;
    std::cout << "test: " << y_close << std::endl;

    int ppoint = (y_high + y_low + y_close) / 3;

    /* s --hyeyeng.ahn - 2012. 04. 29 */
    // what res, sup means?
    //int res1 = (2 * ppoint) - y_low;
    //int sup1 = (2 * ppoint) - y_high;
    //int res2 = (ppoint - sup1) + res1;
    //int sup2 = ppoint - (res1 - sup1);

    return ppoint;
    /* e -- hyeyeng.ahn - 2012. 04. 29 */
}

void IndexFormula::GetSC_KValue()
{ 
    //n기간동안 하는거 포인터 해결 어떻게 하는지 ㅠㅠㅠ	
    //int sc_k = ((db_acc.GetClose() - db_acc.GetPeriodLow())/(db_acc.GetPeriodHigh()- dbhelper.GetPeriodLow()))*100;
}

void IndexFormula::GetSC_DValue()
{
    int sc_d = 0;
    for(int i=0; i<3; i++)
    {
        //sc_d = ((db_acc.GetClose() - dbhelper.GetPeriodLow())/(dbhelper.GetPeriodHigh() - dbhelper.GetPeriodLow()))*100 + sc_d;		
    }
    sc_d = sc_d/3;
}

/* s -- hyeyeng.ahn - 2012. 04. 29 */
int IndexFormula::GetCCIValue()
{
    /* 
        CCI = (M - m) / (d * 0.015)
        M(평균가격) = (당일의 고가 + 당일의 저가 + 당일의 종가) / 3
        m = M의 n일 단순이동평균
          = M + M + .... M / 20
    */
    int* h_arr = db_acc.GetHigh(20);
    int* l_arr = db_acc.GetLow(20);
    int* c_arr = db_acc.GetClose(20);

    int M[20];
    int m_sum = 0;
    int d_sum = 0;
    int n_cci = 0;
    int m, d, cnt; // cnt: for loop index

    for(cnt = 0; cnt < 20; cnt++)
    {
        M[cnt] = (h_arr[cnt] + l_arr[cnt] + c_arr[cnt]) / 3;
        m_sum += M[cnt];
    }
    m = m_sum / 20;

    int abs_d[20];
    for(cnt = 0; cnt < 20; cnt++)
    {
        abs_d[cnt] = abs(M[cnt] - m);
        d_sum += abs_d[cnt];
    }
    d = d_sum / 20;

    //n_cci = (M[0] - m) / (d * 0.015);
    
    return n_cci;
}

void IndexFormula::GetSonarValue()
{
    /*
        sonar momentum = (금일지수이동평균 - n일전 지수이동평균) / n일전 지수이동평균
        sonar momentum signal = sonar momentum의 m일 지수이동평균
        m = 5, n = 10 추천
     */

    //int sonar_m;
}
//
//void IndexFormula::GetSonarAve()
//{
//    int Sonarave = 0;
//    for(int i=0; i<5; i++)
//    {
//        Sonarave = ((db_acc.GetClose() - db_acc.GetPrevClose(10)) / db_acc.GetPrevClose(10))+Sonarave;
//    }
//    Sonarave = Sonarave/5;
//}

int IndexFormula::GetEMA(int day)
{
    /*
        지수이동평균 exponential moving average
        1일: 11,200
        2일: 10,800 * 0.33 + 11,200 * 0.67 = 11,068
        3일: (종가 * k) + (전날 지수이동평균(11,068) * (1-k)) = 3일째 지수이동평균
    */
    int cnt, sum = 0;

    int* close = new int[day];
    // 평활계수
    int k = 0;
    printf("%d \t", day);
    printf("%d \t", day+1);
    printf("%d \t", (2 / 6));
    printf("%f \n", (2 / (day+1)));
    float ma = 0;

    // n일간의 종가
    close = db_acc.GetClose(day);
    ma = close[0];
    for(cnt = 1; cnt < day; cnt++)
    {
        printf("close: %d \n", close[cnt]);
        printf("k: %f", k);
        ma = (close[cnt] * k) + (ma * (1-k));
        printf("ma: %d \n", ma);
    }

    return (int) ma;
}