#include "CDate.h"

tm *CDate::tm_now = NULL;

/**
Метод преобразует дату в строковое представление yyyyMMdd
\param y год
\param m месяц
\param d день
\return указатель на строку
*/
/*char * CDate::dateToChar(int d, int m, int y) {
	char *str;
	char *buffer;
	str = new char[9];
	str[0] = '\0';
	buffer = intToChar(y, 4);
	strcat_s(str, 9, buffer);
	buffer = intToChar(m, 2);
	strcat_s(str, 9, buffer);
	buffer = intToChar(d, 2);
	strcat_s(str, 9, buffer);
	return str;
}*/

/**
Метод преобразует число в строку.
\param number число
\param size разрядность
в случае, если число состоит из одного символа, добавляет в начале строки 0
\return указатель на строку
*/
/*char * CDate::intToChar(int number, int size) {
	int i, count;
	char *s;

	s = new char[size + 1];
	if (number < 10) {
		s[0] = '0';
		s[1] = number + '0';
	}
	else {
		for (count = number, i = 0; count != 0; i++, count /= 10); // Подсчет количества
		for (i--; i >= 0; i--, number /= 10)	// Получение цифр числа 
			s[i] = number % 10 + '0';		// в обратном порядке
	}
	s[size] = '\0';
	return s;
}*/


/**
Метод проверяет корректность даты
\param day день
\param month месяц
\param year год
\return возвращает
0 - в случае корректности даты
1 - в случае ошибки (данные выходят за допустимый диапазон значений)
*/
bool CDate::CheckRangeDate(int d, int m, int y) {
	// почему бракуется 12/12/2012?
	int month30[] = { 4, 6, 9, 11 };
	int i;

	CheckInitTime();
	// что за условие и зачем? - а чтоб люди будущего не регистрировались
	if ((y > tm_now->tm_year + 1900) || (y == tm_now->tm_year + 1900 && m > tm_now->tm_mon + 1) ||
		((y == tm_now->tm_year + 1900) && (m == tm_now->tm_mon + 1) && (d > tm_now->tm_mday)))
		return false;
	// границы d, m, y
	if (d < 1 || d > 31 || m<1 || m>12 || y<1000 || y>9999)
		return false;
	// проверка верхней границы для февраля: високосный год - не более 29 дней, для невисокосного года - не более 28
	if (m == 2 && ((y % 4 != 0 && d > 28) || (y % 4 == 0 && d > 29)))
		return false;
	// проверка верхней границы для 30-дневных месяцев
	for (i = 0; i < 4; i++)
		if ((month30[i] == m) && (d > 30))
			return false;
	return true;
}
bool CDate::operator > (CDate & obj) {
	if (cdYear > obj.cdYear || 
		(cdYear == obj.cdYear && cdMonth > obj.cdMonth) || 
		(cdYear == obj.cdYear && cdMonth == obj.cdMonth && cdDay > obj.cdDay))
		return true;
	return false;
}
bool CDate::operator==(CDate & dat) {
	if (cdDay == dat.cdDay && cdMonth == dat.cdMonth && cdYear == dat.cdYear)
		return true;
	return false;
}
int CDate::diffDateInDay() {
	int delta;
	CDate now;

	delta = now.cdYear - cdYear;
	if (cdMonth > now.cdMonth || (cdDay > now.cdDay && cdMonth == now.cdMonth)) 
		// кооректируем дату, если dd или dd.mm в этом году еще не прошел
		delta -= 1;
	return delta;
}

CDate::CDate(){
	CheckInitTime();
	cdDay = tm_now->tm_mday;
	cdMonth = tm_now->tm_mon + 1;
	cdYear = 1900 + tm_now->tm_year;
}

CDate::CDate(int d, int m, int y): cdDay(d), cdMonth(m), cdYear(y){
	CheckInitTime();
}

CDate::~CDate(){
}

void CDate::CheckInitTime(){
	if (tm_now == NULL) {
		time_t t;
		tm_now = new tm();
		time(&t);
		localtime_s(tm_now, &t);
	}
}

std::ostream & operator << (std::ostream & cout, CDate & obj) {
	cout << std::setw(2) << std::setfill('0') << obj.cdDay << "/";
	cout << std::setw(2) << std::setfill('0') << obj.cdMonth << "/"
		<< std::setw(4) << obj.cdYear;
	return cout;
}
