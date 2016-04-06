#include "CPeople.h"

/**
\brief ������� ���������� dd.MM.yyyy ���� ��������
\param t1 - ������ 1
\param t2 - ������ 2
\return
0 - t1.dd/MM/yyyy == t2.dd/MM/yyyy
-1 - t1.dd/MM/yyyy < t2.dd/MM/yyyy
1 - t1.dd/MM/yyyy > t2.dd/MM/yyyy
*/
/*int CPeople::CheckExpression(CMan t1, CMan t2) {
	if (t1.cm_y < t2.cm_y ||
		(t1.cm_y == t2.cm_y && t1.cm_m < t2.cm_m) ||
		(t1.cm_y == t2.cm_y && t1.cm_m == t2.cm_m && t1.cm_d < t2.cm_d))
		return -1;
	if (t1.cm_y > t2.cm_y ||
		(t1.cm_y == t2.cm_y && t1.cm_m > t2.cm_m) ||
		(t1.cm_y == t2.cm_y && t1.cm_m == t2.cm_m && t1.cm_d > t2.cm_d))
		return 1;
	return 0;
}*/

CPeople::CPeople(){
	arPeople = NULL;
	maxSize = 2;
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
		arPeople = new CMan *[maxSize];
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

void CPeople::EditMan(int n, int key, string s){
	switch (key) {
	case 1: {
		arPeople[n]->setFam(s);
		break;
	}
	case 2: {
		arPeople[n]->setName(s);
		break;
	}
	case 3: {
		arPeople[n]->setPatr(s);
		break;
	}
	case 4: {
		arPeople[n]->setAdr(s.c_str());
		break;
	}
	case 5: {
		arPeople[n]->setBirth(CDate(atoi(s.substr(0,2).c_str()),atoi(s.substr(2,2).c_str()),atoi(s.substr(4,4).c_str())));
		break;
	}
	default:
		break;
	}
}

void CPeople::ViewMan(int n){
	(*arPeople[n]).ViewMan();
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
void CPeople::FindOldMan() {
	int i;
		
	if (size == 0)
		return;
	CDate dat(arPeople[0]->getDate());
	for (i = 1; i < size; i++) 
		if (dat > arPeople[i]->getDate())
			dat = arPeople[i]->getDate();
	cout << "�����:\n";
	for (i = 0; i < size; i++)
		if (arPeople[i]->getDate() == dat) {
			ViewMan(i);
			cout<<"--------\n";
		}
}


void CPeople::Sort(int key, int way){
	int found;

	do {
		found = 0;
		for (int i = 0; i < size - 1; i++) {
			if ( key == 1) {
				// ��������� �� �������
				if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) > 0) || 
					(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) < 0)) {
					swap(arPeople[i], arPeople[i + 1]);
					found++;
				}
				else {
					// �����, ���� ������� ���������, ��������� �� �����
					if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 && 
						 arPeople[i]->Compare(*arPeople[i + 1], 2) > 0) ||
						(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 && 
						 arPeople[i]->Compare(*arPeople[i + 1], 2) < 0)) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
					// ���� ������� � ��� ���������, ��������� �� ��������
					if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 &&
						arPeople[i]->Compare(*arPeople[i + 1], 2) == 0 && arPeople[i]->Compare(*arPeople[i + 1], 3) > 0) ||
						(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 &&
						 arPeople[i]->Compare(*arPeople[i + 1], 2) == 0 && arPeople[i]->Compare(*arPeople[i + 1], 3) < 0)) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
				}
			}
			// ��������� �� ����� ���������� �  �� ���� ��������
			if ((key == 2 || key == 3) && ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) >0) || 
				(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) < 0))) {
				swap(arPeople[i], arPeople[i + 1]);
				found++;
			}
		}
	} while (found != 0);
}

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
void CPeople::Find(char * s, int key){
	for (int i = 0; i < size; i++) 
		if (arPeople[i]->Compare(s, key) == 0)
			ViewMan(i);
}

/**
	������� ������������ ������� �������
	\return ������� �������
*/
int CPeople::AvarageAge(){
	int i = 0;
	long avg = 0;
	
	for (i; i < size; i++) {
		// ������� ������� ��������
		avg += arPeople[i]->AgeMan();
	}
	avg /= size;
	return avg;
}

ostream & operator << (ostream & cout, CPeople & obj) {
	cout << "+" << setw(78) << setfill('-') << "+" << endl;
	cout << "|�  |�������              �.�.|���� ����.|";
	cout << setfill(' ') << setw(36) << left << "�����" << "|" << endl;
	cout << "+" << setw(77) << setfill('-') << "+" << endl;
	for (int i = 0; i < obj.size; i++) {
		cout << setw(4) << setfill(' ') << right << i + 1 
			<< *obj.arPeople[i];
	}
	if (obj.size == 0)
		cout << left << "������� ���" << endl;
	else {
		cout << setw(78) << setfill('-') << "-" << endl;
		cout << "�����: " << obj.size << endl;
	}
	return cout;
}