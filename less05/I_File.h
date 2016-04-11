#pragma once
#include <fstream>
//using namespace std;

class I_File{ 
	virtual void save(std::ofstream& os)=0;
	virtual void load(std::ifstream& is)=0;
	virtual void saveBNR(std::ofstream& os)=0;
	virtual void loadBNR(std::ifstream& is)=0;
};