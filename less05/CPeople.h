#pragma once
#include "CMan.h"
#include <fstream>
#include <vector>
#include <map>

class CPeople: public I_File{
	unsigned int size, maxSize;
	CMan **arPeople; 
public:
	CPeople();
	~CPeople();
	void InsertMan(string, string, string, CDate, const char *); 
	bool DeleteMan(int);
	void EditMan(int, int, string);
	void ViewMan(int);
	int GetSize();
	void FindOldMan();
	void Sort(int, int, int left = 0, int right = -1);
	void Find(char *, int);
	int AvarageAge();
	void inTxt(string);
	void fromTxt(string);
	void inBnry(string);
	void save(ofstream& os);
	void load(ifstream& is);
	void saveBNR(ofstream& os);
	void loadBNR(ifstream& is);
	void fromBnry(string);
	friend ostream & operator << (ostream &, CPeople &);
};

