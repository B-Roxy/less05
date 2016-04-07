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
	char * dateToChar(); // преобразует дату в строковое представление dd/MM/yyyy
	static void CheckInitTime();
	static bool CheckRangeDate(int, int, int); // проверяет корректность составляющих даты
	bool operator < (CDate &);
	bool operator == (CDate &);
	int operator - (const CDate&);
	int diffDateInDay(); // возвращает разницу между текущей датой и датой this
	friend std::ostream & operator << (std::ostream & cout, CDate & obj);
};