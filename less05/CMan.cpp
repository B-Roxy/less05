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

CMan::CMan(string f, string i, string o, const CDate & dat, char *adr) : cmBirth(dat) {
	cm_f = f;
	cm_i = i;
	cm_o =o;
	//cm_adr == NULL;
	cm_adr = new char[strlen(adr) + 1];
	strcpy_s(cm_adr, strlen(adr) + 1, adr);
}

CMan::~CMan() { 
	if (cm_adr != NULL)
		delete cm_adr;
}

ostream & operator << (ostream & cout, CMan & obj) {
	cout << setfill(' ') << setw(20) << obj.cm_f << " " << obj.cm_i[0] << "." << obj.cm_o[0] << ".";
//	cout << obj.cmBirth;
//	cout << setfill(' ') << setw(36) << left << obj.cm_adr;
	cout << endl;
/*	cout << "������ ����������:" << endl;
	cout << "�������: " << obj.cm_f << endl;
	cout << "���: " << obj.cm_i << endl;
	cout << "��������: " << obj.cm_o << endl;
	cout << "���� ��������: ";
	cout << setfill('0') << setw(2) << obj.cm_d << ".";
	cout << setfill('0') << setw(2) << obj.cm_m << ".";
	cout << setfill('0') << setw(4) << obj.cm_y << endl;
	cout << "�����: " << obj.cm_adr << endl;*/
	return cout;
}