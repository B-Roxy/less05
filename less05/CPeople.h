#pragma once
#include "CMan.h"

// ������ �� swap �� ������� ������ CMan?
// �������� ����������� ������ ������ ���� � CMan, � �� � CPeople
// CompareStr - ��� ���� strcmp?
// ������ toChar ������ ���� � CMan
class CPeople{
	unsigned int size, maxSize;
	CMan **arPeople; 
	//int CheckExpression(CMan, CMan); // �������� � ��������� -1 0 1 � ������� � CMan
public:
	CPeople();
	~CPeople();
	void InsertMan(string, string, string, CDate, char *); 
	bool DeleteMan(int);
	void EditMan(int);
	void ViewMan(int);
	int GetSize();
//	void FindOldMan();
//	void Sort(char, int);
//	void Find(char *, int);
//	void FindByDate(int, int, int, int);
//	int AvarageAge();
	friend ostream & operator << (ostream &, CPeople &);
};

