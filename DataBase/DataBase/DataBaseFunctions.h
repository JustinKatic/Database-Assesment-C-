#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"
using namespace std;


class DataBaseFunctions
{
public:

	Player* players;
	
	int size = 4;
	DataBaseFunctions();
	~DataBaseFunctions();

	void WriteToBin(ios_base::openmode type);
	void WriteToBinOnce(int FilePos);
	//void LoadBin();

	void LoadSavedData();

	void AddData();
	void EditData();
	void Resize();

	void BubbleSort();


	int BinarySearch(Player* players, int start_index, int end_index, char searchingFor[]);

	void GetValueOfSizeFromFile();

	void MakeLettersSmall(char name[10]);

};


