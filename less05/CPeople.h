#pragma once
#include "CMan.h"

// Почему бы swap не сделать внутри CMan?
// Проверка коррекности данных должна быть в CMan, а не в CPeople
// CompareStr - чем плох strcmp?
// Методы toChar должны быть в CMan
class CPeople{
	unsigned int size, maxSize;
	CMan **arPeople; 
public:
	CPeople();
	~CPeople();
	void InsertMan(string, string, string, CDate, char *); 
	bool DeleteMan(int);
	void EditMan(int, int, string);
	void ViewMan(int);
	int GetSize();
	void FindOldMan();
	void Sort(int, int);
	void Find(char *, int);
	int AvarageAge();
	friend ostream & operator << (ostream &, CPeople &);
};

