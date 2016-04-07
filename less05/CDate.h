#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>

class CDate {
	static tm *tm_now;
	int cdDay;
	int cdMonth;
	int cdYear;
	char * intToChar(int number, int size); //
public:
	CDate();
	CDate(int, int, int);
	~CDate();
	char * dateToChar(); // ����������� ���� � ��������� ������������� dd/MM/yyyy
	static void CheckInitTime();
	static bool CheckRangeDate(int, int, int); // ��������� ������������ ������������ ����
	bool operator < (CDate &);
	bool operator == (CDate &);
	int operator - (const CDate&);
	int diffDateInDay(); // ���������� ������� ����� ������� ����� � ����� this
	friend std::ostream & operator << (std::ostream & cout, CDate & obj);
};