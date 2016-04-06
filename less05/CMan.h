#pragma once

#include <string>
#include "CDate.h"
using namespace std;

class CMan {
	string cm_f;  // фамилия
	string cm_i; // имя
	string cm_o; // отчество
	CDate cm_Birth; // дата рождения
	char *cm_adr; // адрес
		
	void swap(CMan &); 
public:
	CMan();
	CMan(string, string, string, const CDate &, char *);
	~CMan();
	void setFam(string);
	void setName(string);
	void setPatr(string);
	void setBirth(CDate &);
	void setAdr(const char *);
	CDate getDate();
	int AgeMan();
	void ViewMan();
	int Compare(char *, int);
	int Compare(CMan &, int);
	//int CheckExpression(CMan &); // Привести к стандарту -1 0 1 и вынести в CMan
	friend ostream & operator << (ostream & cout, CMan & obj);
};