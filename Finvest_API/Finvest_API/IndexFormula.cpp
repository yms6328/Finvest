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
        bool MACD(); // MACD =======보류
        bool Stochastics(); // 스토캐스틱 ========완성
        bool RateOfChange(); // 변화율 =========완성
        bool PivotPoint(); // Pivot Point =========보류
        bool SonarMomentum(); // Sonar Momentum =========보류
        bool TRIX(); // TRIX ===========보류
        bool CCI(); // CCI ==========완성
        bool VR(); // VR 
        bool RCI(); // RCI
        bool Disparity(); // 이격도
        bool NCO(); //NCO
        bool PriceOS(); //Price Oscillator 
        bool ADLine(); //ADLine 
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


 void GetDisparityValue()
 {
	 //20일 이격도
	 int DV20= db_acc.GetClose();
 }


int IndexFormula::GetMACDValue()
{

	int short_sum, long_sum, i, j;
	int short_average, long_average;
	int macd_line;

	int* short_average_arr = db_acc.GetClose(12); //단기이동평균선을 위한 12일동안의 종가
	int* long_average_arr = db_acc.GetClose(26); //장기이동평균선을 위한 26일동안의 종가
	
	for(i=0; i<12; i++)
	{
		short_sum += short_average_arr[i];
	}

	for(j=0; j<26; j++)
	{
		long_sum += long_average_arr[j];
	}

	short_average = short_sum/12; //단기이동평균선
	long_average = long_sum/26; //장기이동평균선

	macd_line = short_average-long_average; //macd곡선

	return macd_line;

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

/* s -- hyojin.kim * - 2012. 05. 01 */
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
   // int res1 = (2 * ppoint) - y_low;
   // int sup1 = (2 * ppoint) - y_high;
  //  int res2 = (ppoint - sup1) + res1;
    //int sup2 = ppoint - (res1 - sup1);

    return ppoint;
}

int IndexFormula::GetTodayCloseValue()
{
    int tclose = 0; //오늘의 종가

    tclose = db_acc.GetTodayClose();

    return tclose;
}

/*int IndexFormula::GetPivotResValue1()
{
    int res1 = 0; //1차 저항선
    int y_low = db_acc.GetPrevLow(1);

    res1 = (2 * GetPivotValue()) - y_low;

    return res1;
}

int IndexFormula::GetPivotResValue2()
{
    int sup1 = 0; //1차 지지선
    int y_high = db_acc.GetPrevHigh(1);

    sup1 = (2 * GetPivotValue()) - y_high;

    return sup1;
}*/

///* e -- hyojin.kim  http://blog.daum.net/tax8282kds/15848281 */

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


/*void IndexFormula::GetTrixValue()
{
	//EMA1 = 종가의 N일 지수 이동평균(Exponential Moving Average)  
	//EMA2 = EMA1의 N일 지수 이동평균  
	//EMA3 = EMA2의 N일 지수 이동평균 
	//TRIX = (금일의 EMA3값 - 전일의 EMA3값) / 전일의 EMA3값 TRIX Siganl 
       // = TRIX의 M일 지수이동평균 
	//TRIX signal = TRIX의 K일의 지수이동평균

	int EMA1 = IndexFormula::GetEMA(15, );
	int EMA2 = 
}*/

/* s -- hyojin.kim - 2012. 05. 01 */
int IndexFormula::GetNCOValue()
{
   /*
        momentum = (최근종가 - 12일전 종가)
   */
    int momentum = 0;
    momentum = (db_acc.GetTodayClose() - db_acc.GetPrevClose(12));
    return (int) momentum;
}

int IndexFormula::GetPriceOSValue(){

    /*
        priceoscillator = ((ma(종가, 단기) - ma(종가, 장기)) / ma (종가, 단기)) * 100
        ma(단순이동평균) = (n일동안의 종가의 합)/ n일
    */
    int pos = 0;//price oscillator
    int mas[6]; //단기이동평균
    int mal[75]; //장기이동평균
    int ms, ml, cnt; //cnt : for loop index
    int ps_sum = 0; //단기 종가의 합
    int pl_sum = 0; //장기 종가의 합
    int* s_close = db_acc.GetClose(6); //6일동안의 종가
    int* l_close = db_acc.GetClose(75); //75일동안의 종가

    for(cnt = 0; cnt < 6; cnt++)
    {
        mas[cnt] = (s_close[cnt]);
        ps_sum += mas[cnt];
    }
    ms = ps_sum / 6;

    for(cnt = 0; cnt < 75; cnt++){
        mal[cnt] = (l_close[cnt]);
        pl_sum += mal[cnt];
    }
    ml = pl_sum/ 75;

    pos = ((ms - ml) / ms) * 100;

    return pos;
}

int IndexFormula::GetTADLineValue(){

	/*
	AccDist = ((((종가 - 저가) - (고가 - 저가)) / (고가 - 저가)) * 거래량) + 전일AccDist
	*/

    int taccdist; //당일 accdist
    int prevaccdist;
    int tclose, tlow, thigh = 0; //오늘의 종가, 저가, 고가
    int volume; //거래량

    tclose = db_acc.GetTodayClose();
    tlow = db_acc.GetTodayLow();
    thigh = db_acc.GetTodayHigh();
    volume = db_acc.GetTodayVolume();

    taccdist = ((((tclose - tlow) - (thigh - tlow)) / (thigh - tlow)) * volume) + GetPrevADLineValue();

    return taccdist;
}

int IndexFormula::GetPrevADLineValue(){

	/*
	AccDist = ((((종가 - 저가) - (고가 - 저가)) / (고가 - 저가)) * 거래량) + 전일AccDist
	*/
   
    int prevaccdist; //전일 accdist
    int prevclose, prevlow, prevhigh = 0; //전날의 종가, 저가, 고가
    int prevvolume; //거래량

    prevclose = db_acc.GetPrevClose(1);
    prevlow = db_acc.GetPrevLow(1);
    prevhigh = db_acc.GetPrevHigh(1);
    prevvolume = db_acc.GetPrevVolume(1);

    prevaccdist = ((((prevclose - prevlow) - (prevhigh - prevlow)) / (prevhigh - prevlow)) * prevvolume) + GetPrevADLineValue();
    //근데 여기서 GetPrevADLineValue를 또 사용해서 그 전 날의 accdist값을 불러주어야함. 이게 가능한지 알아야함.

    return prevaccdist;
}
/* e -- hyojin.kim - 2012. 05. 01 */




/*
    private functions
*/
int IndexFormula::GetSignalValue()
{
	int* macd_arr; //9일동안의 macd지수이동평균 - 9일동안의 macd값을 배열의 넣는것을 못했음~~
	int macd_sum, i;
	int signal_line;

	for(i=0; i<9; i++)
	{
		macd_sum += macd_arr[i];
	}

	signal_line = macd_sum/9; //시그널 곡선

	return signal_line;
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
            float ck = data[cnt] * k;
            float mk = ma * (1-k);
            ma = ck + mk;
        }
    }
    else if(day == 1)
    {
        float ck = data[0] * k;
        float mk = ma * (1-k);
        ma = ck + mk;
    }

    return (int) ma;
}
/* e -- hyeyeng.ahn - 2012. 04. 30 */