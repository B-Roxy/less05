#include "CPeople.h"

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
		cout << "Данных нет" << endl;
}

void CPeople::InsertMan(string fam, string name, string patr, CDate dat, const char *adr){
	if (size == 0)
		arPeople = new CMan *[maxSize];
	if (size == maxSize) {
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
	for (int i = indx; i < size - 1; i++)
		arPeople[i] = arPeople[i + 1];
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
	Метод возвращает количество записей в массиве
	\return 
*/
int CPeople::GetSize(){
	return size;
}

/**
*	Поиск человека в массиве объектов с минимальным значением даты
*/
void CPeople::FindOldMan() {
	int i;
	vector<int> indxs;
		
	if (size == 0)
		return;
	CDate dat(arPeople[0]->getDate());
	indxs.push_back(0);
	for (i = 1; i < size; i++) 
		if (dat < arPeople[i]->getDate()) {
			indxs.clear();
			dat = arPeople[i]->getDate();
			indxs.push_back(i);
		}
		else if (dat == arPeople[i]->getDate())
			indxs.push_back(i);
			
	cout << "Нашли:\n";
	for (i = 0; i < indxs.size(); i++){
		ViewMan(indxs[i]);
		cout<<"--------\n";
	}
}

void CPeople::Sort(int key, int way, int left = 0, int right = -1){ // way = 1 - возрастание, -1 - убывание
	int found;
	map<string, int> duplicate; 
	 
	if (right == -1)
		right = size;
	do {
		found = 0;
		for (int i = left, res; i < right - 1; i++) {
			res = arPeople[i]->Compare(*arPeople[i + 1], key);
			if (way == res) {
				swap(arPeople[i], arPeople[i + 1]);
				found++;
			}
		}
	} while (found != 0);
}

/**
	Метод поиска в массиве объектов с заданным значением выбранного поля или с наиболее близким ему значением
	\param * s строка поиска
	\param key ключ поиска, принимает значения:
		1 - по фамилии
		2 - по имени
		3 - по отчеству
		4 - по адресу
		5 - по дате рождения
*/
void CPeople::Find(char * s, int key){
	for (int i = 0; i < size; i++) 
		if (arPeople[i]->Compare(s, key) == 0)
			ViewMan(i);
}

/**
	Функция подсчитывает средний возраст
	\return средний возраст
*/
int CPeople::AvarageAge(){
	int i = 0;
	long avg = 0;
	
	for (i; i < size; i++) {
		// считаем сумму лет
		avg += arPeople[i]->AgeMan();
	}
	avg /= size;
	return avg;
}

void CPeople::inTxt(string fname) {
	ofstream ftxt;

	if (size == 0) {
		cout << "Записей нет. Запись не возможна" << endl;
		return;
	}

	ftxt.open(fname, ios::in);
	if (ftxt.is_open()) {
		ftxt.close();
		char f;
		cout << "Такой файл существует." << endl;
		do {
			cout << "Перезаписать - Y/ дописать - N: ";
			cin >> f;
		} while (f != 'Y' && f != 'y' && f != 'N' && f != 'n');
		if (f == 'Y' || f == 'y')
			ftxt.open(fname);
		if (f == 'N' || f == 'n')
			ftxt.open(fname, ios::app);
	}
	else 
		ftxt.open(fname);
	save(ftxt);
	ftxt.close();
	cout << "Сохранение закончено" << endl;
}

void CPeople::fromTxt(string fname) {
	ifstream ftxt;
	
	ftxt.open(fname);
	load(ftxt);
}

void CPeople::inBnry(string fname) {
	ofstream fbnr;

	if (size == 0) {
		cout << "Записей нет. Запись не возможна" << endl;
		return;
	}

	fbnr.open(fname, ios::binary|ios::in);
	
	if (fbnr.is_open()) {
		fbnr.close();
		char f;
		cout << "Такой файл существует." << endl;
		do {
			cout << "Перезаписать - Y/ дописать - N: ";
			cin >> f;
		} while (f != 'Y' && f != 'y' && f != 'N' && f != 'n');
		if (f == 'Y' || f == 'y')
			fbnr.open(fname, ios::binary);
		if (f == 'N' || f == 'n')
			fbnr.open(fname, ios::app|ios::binary);
	}
	else
		fbnr.open(fname, ios::binary);
	saveBNR(fbnr);
	fbnr.close();
	cout << "Запись закончена" << endl;
}

void CPeople::save(ofstream & os) {
	os << size << endl;
	for (int i = 0; i < size; i++)
		arPeople[i]->save(os);
}

void CPeople::load(ifstream & is) {
	string fam, name, patr, dat, adr;
	int count, d, m, y;

	is >> count;
	is.ignore();
	for (int i = 0; i < count; i++) {
		getline(is, fam, '|');
		getline(is, name, '|');
		getline(is, patr, '|');
		getline(is, dat, '|');
		getline(is, adr);
		InsertMan(fam, name, patr, CDate(stoi(dat.substr(0,2)), stoi(dat.substr(3,2)), stoi(dat.substr(6,4))), adr.c_str());
	}
	size = count;
	cout << "Загрузка закончена" << endl;
	is.close();
}

void CPeople::saveBNR(ofstream & os) {
	for (int i = 0; i < size; i++)
		arPeople[i]->saveBNR(os);
}

void CPeople::loadBNR(ifstream & is) {
	int sz, d, m, y;
	char *fam, *name, *patr, *adr;
	
	while (is.read((char*)&sz, sizeof(sz)) && !is.eof()) {
		fam = new char[sz];
		is.read(fam, sz);
		is.read((char*)&sz, sizeof(sz));
		name = new char[sz];
		is.read(name, sz);
		is.read((char*)&sz, sizeof(sz));
		patr = new char[sz];
		is.read(patr, sz);
		is.read((char*)&d, sizeof(d));
		is.read((char*)&m, sizeof(m));
		is.read((char*)&y, sizeof(y));
		is.read((char*)&sz, sizeof(sz));
		adr = new char[sz];
		is.read(adr, sizeof(sz));
		InsertMan(fam, name, patr, CDate(d, m, y), adr);
		cout << fam << ' ' << name << ' ' << patr << ' ' << d << '/' << m << '/' << y << ' ' << adr << endl;
		delete fam;
		delete name;
		delete patr;
		delete adr;
	}
}

void CPeople::fromBnry(string fname) {
	ifstream fbnr;

	fbnr.open(fname, ios::binary);
	loadBNR(fbnr);
	fbnr.close();
}

ostream & operator << (ostream & cout, CPeople & obj) {
	cout << "+" << setw(78) << setfill('-') << "+" << endl;
	cout << "|№  |Фамилия              И.О.|Дата рожд.|";
	cout << setfill(' ') << setw(36) << left << "Адрес" << "|" << endl;
	cout << "+" << setw(77) << setfill('-') << "+" << endl;
	for (int i = 0; i < obj.size; i++) {
		cout << setw(4) << setfill(' ') << right << i + 1 
			<< *obj.arPeople[i];
	}
	if (obj.size == 0)
		cout << left << "Записей НЕТ" << endl;
	else {
		cout << setw(78) << setfill('-') << "-" << endl;
		cout << "Всего: " << obj.size << endl;
	}
	return cout;
}