#ifndef STOCK_H
#define STOCK_H
#include <string>

typedef struct Stock
{
    char code[8];
    char date[10];
    int m_open;
    int m_high;
    int m_low;
    int m_diff;
    float m_fScale;
    double m_dVolume;
    double m_dPMA5;
    double m_dPMA10;
    double m_dPMA20;
    double m_dPMA60;
    double m_dPMA120;
    double m_dVMA5;
    double m_dVMA10;
    double m_dVMA20;
    double m_dVMA60;
    double m_dVMA120;
} StockData;

class Stock
{
    Stock();
	~Stock();
    char* GetCode();
	char* GetDate();
	int GetClose();
	int GetOpen();
	int GetHigh();
	int GetLow();
	int GetDiff();
	double GetVolume();
	float GetScale();

	int GetPMA5();
	int GetPMA10();
	int GetPMA20();
	int GetPMA60();
	int GetPMA120();

    int GetVMA5();
	int GetVMA10();
	int GetVMA20();
	int GetVMA60();
	int GetVMA120();
};
#endif
