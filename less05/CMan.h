#pragma once

#include <string>
#include "CDate.h"
using namespace std;

class CMan {
	string cm_f;  // �������
	string cm_i; // ���
	string cm_o; // ��������
	CDate cm_Birth; // ���� ��������
	char *cm_adr; // �����
		
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
	friend ostream & operator << (ostream & cout, CMan & obj);
};