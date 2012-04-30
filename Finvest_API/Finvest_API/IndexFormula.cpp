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

int IndexFormula::GetRSIValue()
{
    //RSI = {(14일간 상승폭 합계) / (14일간 상승폭 합계 + 14일간 하락폭 합계) } * 10
    return 0;
}

/* s :: hyeyeong.ahn - 2012. 04. 30 */
int IndexFormula::GetStochasticValue()
{
    /*
        Stochastic
        (종가 - 5일동안의 최저가) / (5일동안의 최고가 - 5일동안의 최저가)
    */
    int st_k;
    int* low_arr = db_acc.GetLow(5);
    int* high_arr = db_acc.GetHigh(5);
    int min_low, max_high;
    int close = db_acc.GetTodayClose();

    min_low = low_arr[0];
    max_high = high_arr[0];

    for(int cnt = 1; cnt < 5; cnt++)
    {
        if(low_arr[cnt] < min_low)
        {
            min_low = low_arr[cnt];
        }

        if(high_arr[cnt] > max_high)
        {
            max_high = high_arr[cnt];
        }
    }

    st_k = (close - min_low) / (max_high - min_low);
    return st_k;
}

/* s --hyeyeng.ahn - 2012. 04. 29 */
int IndexFormula::GetRatioValue() 
{
    /*
        변화율
        마이너스 영역에서 0선을 통과하여 플러스로 가면 매수
        플러스 영역에서 0선을 통과하여 마이너스로 가면 매도
        변화율 = {(오늘종가 - 12일전 종가) / 12일전 종가 } * 100
    */

    int ratio;
    int t_close = db_acc.GetTodayClose();
    int p_close = db_acc.GetPrevClose(12);

    ratio = ((t_close - p_close) / p_close) * 100;
    return ratio;
}
/* e -- hyeyeng.ahn - 2012. 04. 29 */

///* s -- hyeunjeong.song */
int IndexFormula::GetPivotValue()
{
    
    //pivot point = (전일의 고가 + 전일의 저가 + 전일의 종가) / 3
    int y_high = db_acc.GetPrevHigh(1);
    int y_low = db_acc.GetPrevLow(1);
    int y_close = db_acc.GetPrevClose(1);

    int ppoint = (y_high + y_low + y_close) / 3;

     /*
        res: 저항선
        sup: 지지선
    */
    int res1 = (2 * ppoint) - y_low;
    int sup1 = (2 * ppoint) - y_high;
    int res2 = (ppoint - sup1) + res1;
    int sup2 = ppoint - (res1 - sup1);

    return ppoint;
}
///* e -- hyeunjeong.song */

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
/* e -- hyeyeng.ahn - 2012. 04. 29 */

/* s -- hyeyeng.ahn - 2012. 04. 30 */
void IndexFormula::GetSonarValue()
{
    /*
        sonar momentum = (금일지수이동평균 - n일전 지수이동평균) / n일전 지수이동평균
        sonar momentum signal = sonar momentum의 m일 지수이동평균
        m = 5, n = 10 추천
     */
     int today_ema = GetEMA(1, db_acc.GetClose(1));
     int nday_ema = GetEMA(10, db_acc.GetClose(10));
     //int sonar_m_signal[5];
     /*for(int cnt = 0; cnt < 5; cnt++)
     {
        sonar_m_signal[cnt] = 
     }
     sonar momentum을 n일동안 구해야 함? -> 금일 지수 이동 평균 5번.. 날짜가 5번 바뀌어야함;;
     */
}

int IndexFormula::GetEMA(int day, int* data)
{
    /*
        지수이동평균 exponential moving average
        1일: 11,200
        2일: 10,800 * 0.33 + 11,200 * 0.67 = 11,068
        3일: (종가 * k) + (전날 지수이동평균(11,068) * (1-k)) = 3일째 지수이동평균
    */
    int cnt, sum = 0;

    // 평활계수
    float k = 2 / (float)(day + 1);
    float ma;

    ma = data[0];
    if(day > 1)
    {
        for(cnt = 1; cnt < day; cnt++)
        {
            printf("ma: %f\n", ma);
            printf("close: %d \n", data[cnt]);
            printf("k: %f\n", k);
            printf("close*k: %f \n", (data[cnt] * k));
            printf("ma*(1-k): %f \n", (ma * (1-k)));

            float ck = data[cnt] * k;
            float mk = ma * (1-k);
            ma = ck + mk;
            printf("ck: %f \n", ck);
            printf("mk: %f \n", mk);
            printf("ma: %d \n", (int)ma);
        }
    }
    else if(day == 1)
    {
        float ck = data[0] * k;
        float mk = ma * (1-k);
        ma = ck + mk;
        printf("ck: %f \n", ck);
        printf("mk: %f \n", mk);
        printf("ma: %d \n", (int)ma);
    }

    return (int) ma;
}
/* e -- hyeyeng.ahn - 2012. 04. 30 */