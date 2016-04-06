#include "CPeople.h"

/**
\brief ������� ���������� dd.MM.yyyy ���� ��������
\param t1 - ������ 1
\param t2 - ������ 2
\return
0 - t1.dd/MM/yyyy == t2.dd/MM/yyyy
1 - t1.dd/MM/yyyy < t2.dd/MM/yyyy
2 - t1.dd/MM/yyyy > t2.dd/MM/yyyy
*/
/*int CPeople::CheckExpression(CMan t1, CMan t2) {
	if (t1.cm_y < t2.cm_y ||
		(t1.cm_y == t2.cm_y && t1.cm_m < t2.cm_m) ||
		(t1.cm_y == t2.cm_y && t1.cm_m == t2.cm_m && t1.cm_d < t2.cm_d))
		return 1;
	if (t1.cm_y > t2.cm_y ||
		(t1.cm_y == t2.cm_y && t1.cm_m > t2.cm_m) ||
		(t1.cm_y == t2.cm_y && t1.cm_m == t2.cm_m && t1.cm_d > t2.cm_d))
		return 2;
	return 0;
}*/

CPeople::CPeople(){
	arPeople = NULL;
	maxSize = 10;
}

CPeople::~CPeople(){
	if (size > 0) {
		for (int i = 0; i < size; i++)
			delete arPeople[i];
		delete[] arPeople;
		size = 0;
	}
	else
		cout << "������ ���" << endl;
}

void CPeople::InsertMan(string fam, string name, string patr, CDate dat, char *adr){
	if (size == 0)
		arPeople = new CMan * [maxSize];
	if (size == maxSize - 1) {
			maxSize *= 2;
			CMan **t_obj = new CMan *[maxSize];
			for (int i = 0; i < size; i++)
				t_obj[i] = arPeople[i];
			delete[] arPeople;
			arPeople = t_obj;
	}
	arPeople[size] = new CMan(fam, name, patr, dat, adr);
	size++;
}

bool CPeople::DeleteMan(int indx){
	CMan **t_obj = new CMan *[size - 1];
	for (int i = 0; i < indx; i++)
		t_obj[i] = arPeople[i];
	for (int i = indx + 1; i < size; i++)
		t_obj[i - 1] = arPeople[i];
	delete[] arPeople;
	arPeople = t_obj;
	size--;
	return true;
}

void CPeople::EditMan(int){
}

void CPeople::ViewMan(int n){
	cout << arPeople[n];
	cout << endl;
}
/**
	����� ���������� ���������� ������� � �������
	\return 
*/
int CPeople::GetSize(){
	return size;
}

/**
*	����� �������� � ������� �������� � ����������� ��������� ����
*/
/*void CPeople::FindOldMan() {
	int i, d, m, y;
	
	d = arPeople[0];
	m = arPeople[0].cm_m;
	y = arPeople[0].cm_y;
	for (i = 1; i < size; i++) {
		if (y > arPeople[i].cm_y || 
			(y == arPeople[i].cm_y && m > arPeople[i].cm_m) || 
			(y == arPeople[i].cm_y && m == arPeople[i].cm_m && d > arPeople[i].cm_d)) {
			d = arPeople[i].cm_d;
			m = arPeople[i].cm_m;
			y = arPeople[i].cm_y;
		}
	}
	for (i = 0; i < size; i++)
		if ((arPeople + i)->cm_d == d && (arPeople + i)->cm_m == m && (arPeople + i)->cm_y == y)
			cout << arPeople + i;
}*/
/*
void CPeople::Sort(char c, int way){
	int found;

	do {
		found = 0;
		for (int i = 0; i < size - 1; i++) {
			if (c == 'f') {
				// ��������� �� �������
				if ((way == 1 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) > 0)) || 
					(way == 2 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) < 0))) {
					swap(arPeople[i], arPeople[i + 1]);
					found++;
				}
				else {
					// �����, ���� ������� ���������, ��������� �� �����
					if ((way == 1 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) == 0) && 
						 (_strcmpi(arPeople[i].cm_i, arPeople[i + 1].cm_i) > 0)) ||
						(way == 2 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) == 0) && 
						 (_strcmpi(arPeople[i].cm_i, arPeople[i + 1].cm_i) < 0))) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
					// ���� ������� � ��� ���������, ��������� �� ��������
					if ((way == 1 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) == 0) &&
						(_strcmpi(arPeople[i].cm_i, arPeople[i + 1].cm_i) == 0) && (_strcmpi(arPeople[i].cm_o, arPeople[i + 1].cm_o) > 0)) ||
						(way == 2 && (_strcmpi(arPeople[i].cm_f, arPeople[i + 1].cm_f) == 0) &&
							(_strcmpi(arPeople[i].cm_i, arPeople[i + 1].cm_i) == 0) && (_strcmpi(arPeople[i].cm_o, arPeople[i + 1].cm_o) < 0))) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
				}
			}
			// ��������� �� ����� ����������
			if (c == 'a' && ((way == 1 && (strcmp(arPeople[i].cm_adr, arPeople[i + 1].cm_adr) >0)) || 
				(way == 2 && (strcmp(arPeople[i].cm_adr, arPeople[i + 1].cm_adr) < 0)))) {
				swap(arPeople[i], arPeople[i + 1]);
				found++;
			}
			// ��������� �� ���� ��������
			if (c == 'd' && ((way == 1 && (CheckExpression(arPeople[i], arPeople[i + 1]) == 1)) || 
				(way == 2 && (CheckExpression(arPeople[i], arPeople[i + 1]) == 2)))) {
				swap(arPeople[i], arPeople[i + 1]);
				found++;
			}
		}
	} while (found != 0);
	cout << arPeople;
}*/
/**
	����� ������ � ������� �������� � �������� ��������� ���������� ���� ��� � �������� ������� ��� ���������
	\param * s ������ ������
	\param key ���� ������, ��������� ��������:
		1 - �� �������
		2 - �� �����
		3 - �� ��������
		4 - �� ������
		5 - �� ���� ��������
*/
/*void CPeople::Find(char * s, int key){
	double *delta, min_delta = DBL_MAX;
	// �������� ���� ������ ��� ������� delta
	delta = new double[size];
	// ��� ������ ������� ��������� delta ������ ������ �
	for (int i = 0; i < size; i++) {
		switch (key) {
			case 1: {
				// �������
				delta[i] = CompareStr(arPeople[i].cm_f, s);
				break;
			}
			case 2: {
				// �����
				delta[i] = CompareStr(arPeople[i].cm_i, s);
				break;
			}
			case 3: {
				// ��������
				delta[i] = CompareStr(arPeople[i].cm_o, s);
				break;
			}
			case 4: {
				// ������
				delta[i] = CompareStr(arPeople[i].cm_adr, s);
				break;
			}
			case 5: {
				// ���� �������� � ��������� ����
				delta[i] = CompareStr(dateToChar(arPeople[i].cm_y, arPeople[i].cm_m, arPeople[i].cm_d), s);
				break;
			}
			default: break;
		} /// end switch
		// �������� ���������� delta
		if (min_delta > delta[i])
			min_delta = delta[i];
	} /// end for
	// ������� ������ � ���������� delta
	for (int i = 0; i < size; i++)
		if (delta[i] == min_delta) {
			cout << "-------";
			cout << arPeople[i];
		}
	delete[] delta;
}*/
/**
	����� ������ �� ���� ��������
	\param d 
	\param m
	\param y
	\param key
*/
/*void CPeople::FindByDate(int d, int m, int y, int key){
	char s[9];
	strcpy_s(s, 9, dateToChar(y, m, d));
	Find(s, key);
}*/
/**
	������� ������������ ������� ��������
	\param *t ��������� �� ������ ��������
	\param size ���������� �������� � �������
	\return ������� �������
*/
/*int CPeople::AvarageAge(){
	int i = 0;
	long avg = 0;
	
	for (i; i < size; i++) {
		// ������� ������� ��������
		avg += tm_now.tm_year + 1900 - (arPeople + i)->cm_y;
		// ������������ �������, ���� �� � ���� ���� ��� �� ����
		if ((arPeople[i].cm_m >(tm_now.tm_mon + 1)) || 
			(arPeople[i].cm_d > tm_now.tm_mday && arPeople[i].cm_m == (tm_now.tm_mon + 1))) {
			avg -= 1;
		}
	}
	avg /= size;
	return avg;
}*/

ostream & operator << (ostream & cout, CPeople & obj) {
	cout << "+" << setw(78) << setfill('-') << "+" << endl;
	cout << "|�  |�������              �.�.|���� ����.|";
	cout << setfill(' ') << setw(36) << left << "�����" << "|" << endl;
	cout << "+" << setw(77) << setfill('-') << "+" << endl;
	for (int i = 0; i < obj.size; i++) 
		cout << obj.arPeople[i];
	if (obj.size == 0)
		cout << left << "������� ���" << endl;
	else {
		cout << setw(78) << setfill('-') << endl;
		cout << "�����: " << obj.size << endl;
	}
	return cout;
}