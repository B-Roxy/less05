#include "CMan.h"
/**
	����� ������ ������� ���������
	\param p1 ������1
	\param p2 ������2
	*/
void CMan::swap(CMan & obj){
	CMan temp = *this;
	*this = obj;
	obj = temp;
}

CMan::CMan() {
	cm_adr = NULL;
}

CMan::CMan(string f, string i, string o, const CDate & dat, char *adr) : cm_Birth(dat) {
	cm_f = f;
	cm_i = i;
	cm_o =o;
	cm_adr = new char[strlen(adr) + 1];
	strcpy_s(cm_adr, strlen(adr) + 1, adr);
}

CMan::~CMan() { 
	if (cm_adr != NULL)
		delete cm_adr;
}

void CMan::setFam(string s) {
	cm_f = s;
}

void CMan::setName(string s) {
	cm_i = s;
}

void CMan::setPatr(string s) {
	cm_o = s;
}

void CMan::setBirth(CDate & dat) {
	cm_Birth = dat; // ����� ���������� ��������� ������������?
}

void CMan::setAdr(const char * s) {
	delete cm_adr;
	cm_adr = new char[strlen(s) + 1];
	strcpy_s(cm_adr, strlen(s) + 1, s);
}

CDate CMan::getDate() {
	return cm_Birth;
}

int CMan::AgeMan() {
	return cm_Birth.diffDateInDay();
}

void CMan::ViewMan() {
	cout << "������ ����������:" << endl;
	cout << "�������: " << cm_f << endl;
	cout << "���: " << cm_i << endl;
	cout << "��������: " << cm_o << endl;
	cout << "���� ��������: ";
	cout << cm_Birth << endl;
	cout << "�����: " << cm_adr << endl;
}

ostream & operator << (ostream & cout, CMan & obj) {
	cout << setfill(' ') << setw(20) << obj.cm_f << " " << obj.cm_i[0] << "." << obj.cm_o[0] << " ";
	cout << obj.cm_Birth << " ";
	cout << setfill(' ') << setw(36) << left << obj.cm_adr;
	cout << endl;
	return cout;
}