#pragma once

#include <string>
#include "I_File.h"
#include "CDate.h"
using namespace std;

class CMan : public I_File{
	string cm_f;  // �������
	string cm_i; // ���
	string cm_o; // ��������
	CDate cm_Birth; // ���� ��������
	char *cm_adr; // �����
		
	void swap(CMan &); 
public:
	CMan();
	CMan(string, string, string, const CDate &, const char *);
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
	string getFam();
	string allData(char);
	void save(ofstream& os);
	void load(ifstream& is);
	//int CheckExpression(CMan &); // �������� � ��������� -1 0 1 � ������� � CMan
	friend ostream & operator << (ostream & cout, CMan & obj);
	friend ofstream & operator << (ofstream & fout, CMan & obj);
};