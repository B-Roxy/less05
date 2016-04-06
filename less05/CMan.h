#pragma once

#include <string>
#include "CDate.h"
using namespace std;

class CMan {
	string cm_f;  // �������
	string cm_i; // ���
	string cm_o; // ��������
	CDate cmBirth; // ���� ��������
	char *cm_adr; // �����
		
	void swap(CMan &); // ������� � CMan
public:
	CMan();
	CMan(string, string, string, const CDate &, char *);
	~CMan();
	friend ostream & operator << (ostream & cout, CMan & obj);
};