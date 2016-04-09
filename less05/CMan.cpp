#include "CMan.h"
/**
	Метод меняет местами указатели
	\param p1 объект1
	\param p2 объект2
	*/
void CMan::swap(CMan & obj){
	CMan temp = *this;
	*this = obj;
	obj = temp;
}

CMan::CMan() {
	cm_adr = NULL;
}

CMan::CMan(string f, string i, string o, const CDate & dat, const char *adr) : cm_Birth(dat) {
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
	cm_Birth = dat; // нужна перегрузка оператора присваивания?
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
	cout << "Полная информация:" << endl;
	cout << "Фамилия: " << cm_f << endl;
	cout << "Имя: " << cm_i << endl;
	cout << "Отчество: " << cm_o << endl;
	cout << "Дата рождения: ";
	cout << cm_Birth << endl;
	cout << "Адрес: " << cm_adr << endl;
}

int CMan::Compare(char * s, int key) {
	int res;
	switch (key) {
		case 1: {
			res = _strcmpi(cm_f.c_str(), s);
			break;
		}
		case 2: {
			res = _strcmpi(cm_i.c_str(), s);
			break;
		}
		case 3: {
			res = _strcmpi(cm_o.c_str(), s);
			break;
		}
		case 4: {
			res = _strcmpi(cm_adr, s);
			break;
		}
		case 5: {
			res = _strcmpi(cm_Birth.dateToChar(), s);
			break;
		}
	}
	return res;
}

int CMan::Compare(CMan & obj, int key) {
	int res;
	switch (key) {
		case 1: {
			res = cm_f.compare(obj.cm_f);
			break;
		}
		case 2: {
			res = cm_i.compare(obj.cm_i);
			break;
		}
		case 3: {
			res = cm_o.compare(obj.cm_o);
			break;
		}
		case 4: {
			res = _strcmpi(cm_adr, obj.cm_adr);
			break;
		}
		case 5: {
			res = _strcmpi(cm_Birth.dateToChar(),obj.cm_Birth.dateToChar());
			break;
		}
	}
	if (res > 0) res = 1;
	if (res < 0) res = -1;
	return res;
}

string CMan::getFam() {
	return cm_f;
}

string CMan::allData(char c) {
	c = (c == ' ' || c == '/') ? '|' : c;
	return cm_f + c + cm_i + c +cm_o + c + cm_Birth.dateToChar() + c + cm_adr + '\n';
}

void CMan::save(ofstream & os) {
	os << cm_f << "|" << cm_i << "|" << cm_o << "|";
	cm_Birth.save(os);
	os << "|" << cm_adr << endl;
}

void CMan::load(ifstream & is) {}

ostream & operator << (ostream & cout, CMan & obj) {
	cout << setfill(' ') << setw(22) << obj.cm_f << " " << obj.cm_i[0] << "." << obj.cm_o[0] << " ";
	cout << obj.cm_Birth << " ";
	cout << setfill(' ') << setw(36) << left << obj.cm_adr;
	cout << endl;
	return cout;
}

ofstream & operator << (ofstream & fout, CMan & obj) {
	fout << obj.cm_f << "|" << obj.cm_i << "|";
	return fout;
}