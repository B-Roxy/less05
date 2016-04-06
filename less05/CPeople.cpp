#include "CPeople.h"

/**
\brief Функция сравнивает dd.MM.yyyy двух структур
\param t1 - объект 1
\param t2 - объект 2
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
		cout << "Данных нет" << endl;
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
		
	if (size == 0)
		return;
	CDate dat(arPeople[0]->getDate());
	for (i = 1; i < size; i++) 
		if (dat > arPeople[i]->getDate())
			dat = arPeople[i]->getDate();
	cout << "Нашли:\n";
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
				// сортируем по фамилии
				if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) > 0) || 
					(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) < 0)) {
					swap(arPeople[i], arPeople[i + 1]);
					found++;
				}
				else {
					// иначе, если фамилии совпадают, сортируем по имени
					if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 && 
						 arPeople[i]->Compare(*arPeople[i + 1], 2) > 0) ||
						(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 && 
						 arPeople[i]->Compare(*arPeople[i + 1], 2) < 0)) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
					// если фамилия и имя совпадают, сортируем по отчеству
					if ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 &&
						arPeople[i]->Compare(*arPeople[i + 1], 2) == 0 && arPeople[i]->Compare(*arPeople[i + 1], 3) > 0) ||
						(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) == 0 &&
						 arPeople[i]->Compare(*arPeople[i + 1], 2) == 0 && arPeople[i]->Compare(*arPeople[i + 1], 3) < 0)) {
						swap(arPeople[i], arPeople[i + 1]);
						found++;
					}
				}
			}
			// сортируем по месту жительства и  по дате рождения
			if ((key == 2 || key == 3) && ((way == 1 && arPeople[i]->Compare(*arPeople[i + 1], key) >0) || 
				(way == 2 && arPeople[i]->Compare(*arPeople[i + 1], key) < 0))) {
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
		// считаем возраст человека
		avg += arPeople[i]->AgeMan();
	}
	avg /= size;
	return avg;
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