#pragma once

#include <string>
#include "CDate.h"
using namespace std;

class CMan {
	string cm_f;  // фамили€
	string cm_i; // им€
	string cm_o; // отчество
	CDate cmBirth; // дата рождени€
	char *cm_adr; // адрес
		
	void swap(CMan &); // вынести в CMan
public:
	CMan();
	CMan(string, string, string, const CDate &, char *);
	~CMan();
	friend ostream & operator << (ostream & cout, CMan & obj);
};