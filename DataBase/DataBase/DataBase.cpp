#include <iostream>
#include "Player.h"
#include "DataBaseFunctions.h"
#include <fstream>
using namespace std;

//default array
static Player player[4];

int main()
{
	//adding variables inside of a static array called player
	strcpy_s(player[0].playerName, "justin");
	strcpy_s(player[0].highScore, "10000");

	strcpy_s(player[1].playerName, "igor");
	strcpy_s(player[1].highScore, "5000");

	strcpy_s(player[2].playerName, "jay");
	strcpy_s(player[2].highScore, "20000");

	strcpy_s(player[3].playerName, "len");
	strcpy_s(player[3].highScore, "80000");

	//creating instance of databaseFunctions
	DataBaseFunctions databaseFunctions;



	fstream fin;
	fin.open("player.dat", ios::in | ios::binary);
	//if no file save already exist create one and store default values inside of dynamic array sort and then write the whole file to txt file
	if (fin.fail())
	{
		for (int i = 0; i < 4; i++)
		{
			databaseFunctions.players[i] = player[i];
		}
		databaseFunctions.BubbleSort();
		databaseFunctions.WriteToBin(ios::out);
	}
	//get the value of size and load all saved data into players array
	else
	{
		fin.close();
		databaseFunctions.GetValueOfSizeFromFile();
		databaseFunctions.LoadSavedData();
	}
	fin.close();


	bool play = true; //while loop condition
	int choice;		  //switch statment entry

	while (play == true)
	{
		cout << "1. View\n2. Add\n3. Search\n4. Edit data\n5. Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//VIEW sort array, loop players array and print contents
		{
			system("cls");
			databaseFunctions.BubbleSort();
			for (int i = 0; i < databaseFunctions.size; i++)
			{
				cout << "Player name: " << databaseFunctions.players[i].playerName << "		" << "HighScore: " << databaseFunctions.players[i].highScore << endl;
			}
			system("pause");
			system("cls");
			break;
		}

		case 2:		//ADD add new player to players array
		{
			system("cls");
			databaseFunctions.AddData();
			system("cls");
			cout << "Player has been added" << endl;
			system("pause");
			system("cls");
			break;
		}

		case 3:		//SEARCH sort players array aplhabetically, use binary search to find where input is in array if exist. cout element in players array at that pos
		{
			system("cls");
			char playerChoice[10];
			cout << "type name youd like to search for" << endl;
			cin >> playerChoice;
			databaseFunctions.BubbleSort();

			int result = databaseFunctions.BinarySearch(databaseFunctions.players, 0, databaseFunctions.size - 1, playerChoice);
			cout << "Player name: " << databaseFunctions.players[result].playerName << "		" << "HighScore: " << databaseFunctions.players[result].highScore << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4:		//EDIT DATA sorts array alphabetically, calls edit function to change values of a player to new values
		{
			system("cls");
			databaseFunctions.BubbleSort();
			databaseFunctions.EditData();
			system("cls");
			cout << "data has been edited" << endl;
			system("pause");
			system("cls");
			break;
		}

		case 5:		//EXIT  breaks of out while loop
		{
			play = false;
			break;
		}

		default:	//ERROR CHECK IF INCORRECT INPUT
		{
			cout << "incorrect input" << endl;
			//clears buffer
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			break;
		}

		}
	}
}

