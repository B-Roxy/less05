#include "CDate.h"

tm *CDate::tm_now = NULL;

/**
����� ����������� ���� � ��������� ������������� dd/MM/yyyy
\param y ���
\param m �����
\param d ����
\return ��������� �� ������
*/
char * CDate::dateToChar() {
	char *str;
	char *buffer;
	str = new char[11];
	str[0] = '\0';
	buffer = intToChar(cdDay, 2);
	strcat_s(str, 11, buffer);
	strcat_s(str, 11, "/");
	buffer = intToChar(cdMonth, 2);
	strcat_s(str, 11, buffer);
	strcat_s(str, 11, "/");
	buffer = intToChar(cdYear, 4);
	strcat_s(str, 11, buffer);
	return str;
}

/**
����� ����������� ����� � ������.
\param number �����
\param size �����������
� ������, ���� ����� ������� �� ������ �������, ��������� � ������ ������ 0
\return ��������� �� ������
*/
char * CDate::intToChar(int number, int size) {
	int i, count;
	char *s;

	s = new char[size + 1];
	if (number < 10) {
		s[0] = '0';
		s[1] = number + '0';
	}
	else {
		for (count = number, i = 0; count != 0; i++, count /= 10); // ������� ����������
		for (i--; i >= 0; i--, number /= 10)	// ��������� ���� ����� 
			s[i] = number % 10 + '0';		// � �������� �������
	}
	s[size] = '\0';
	return s;
}

/**
����� ��������� ������������ ����
\param day ����
\param month �����
\param year ���
\return ����������
	true - � ������ ������������ ����
	false - � ������ ������ (������ ������� �� ���������� �������� ��������)
*/
bool CDate::CheckRangeDate(int d, int m, int y) {
	int month30[] = { 4, 6, 9, 11 };
	int i;
	CDate now;

	CheckInitTime();
	// ��� �� ������� � �����? - � ���� ���� �������� �� ����������������
	if ((y > now.cdYear) || (y == now.cdYear && m > now.cdMonth) ||
		(y == now.cdYear && m == now.cdMonth && d > now.cdDay))
		return false;
	// ������� d, m, y
	if (d < 1 || d > 31 || m<1 || m>12 || y<1000 || y>9999)
		return false;
	// �������� ������� ������� ��� �������: ���������� ��� - �� ����� 29 ����, ��� ������������� ���� - �� ����� 28
	if (m == 2 && ((y % 4 != 0 && d > 28) || (y % 4 == 0 && d > 29)))
		return false;
	// �������� ������� ������� ��� 30-������� �������
	for (i = 0; i < 4; i++)
		if ((month30[i] == m) && (d > 30))
			return false;
	return true;
}
bool CDate::operator < (CDate & obj) {
	return (cdYear < obj.cdYear || (cdYear == obj.cdYear && cdMonth < obj.cdMonth) || 
			(cdYear == obj.cdYear && cdMonth == obj.cdMonth && cdDay < obj.cdDay));
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
		// ������������ ����, ���� dd ��� dd.mm � ���� ���� ��� �� ������
		delta -= 1;
	return delta;
}

void CDate::save(std::ofstream & os) {
	os << dateToChar() << "|";
}

void CDate::load(std::ifstream & is) {
	char c;
	is >> cdDay >> c >> cdMonth >> c >> cdYear >> c;  
}

void CDate::saveBNR(std::ofstream & os) {
	os.write((char*)&cdDay, sizeof(cdDay));
	os.write((char*)&cdMonth, sizeof(cdMonth));
	os.write((char*)&cdYear, sizeof(cdYear));
}

void CDate::loadBNR(std::ifstream & is) {
	is.read((char*)&cdDay, sizeof(cdDay));
	is.read((char*)&cdMonth, sizeof(cdMonth));
	is.read((char*)&cdYear, sizeof(cdYear));
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
	std::cout.setf(std::ios::right);
	cout << std::setfill('0') << std::setw(2) << obj.cdDay << "/";
	cout << std::setfill('0') << std::setw(2) << obj.cdMonth << "/"
		<< std::setw(4) << obj.cdYear;
	return cout;
}
