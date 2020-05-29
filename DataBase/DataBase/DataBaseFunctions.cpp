#include "DataBaseFunctions.h"
#include <string>

//constructor creats a new players dynamic array 
DataBaseFunctions::DataBaseFunctions()
{
	players = new Player[size];
}
//deconstructor deletes players variable at end of program
DataBaseFunctions::~DataBaseFunctions()
{
	delete players;
}

//writes to file player.dat in binary overwrites old file and creates a new one each time with all the elements of players[] inside it
void DataBaseFunctions::WriteToBin(ios_base::openmode type)
{
	fstream fout;
	fout.open("player.dat", type | ios::binary);
	if (fout.good())
	{
		for (int i = 0; i < size; i++)
		{
			fout.write((char*)&players[i], sizeof(Player));		//writeing each players into txtfile
		}
		cout << "file written" << endl;
	}
	fout.close();
}
//writes to file player.dat in binary only if file already exists
//writes in the position in txtfile specified by filepos para e.g if filepos was 5 itd write the 5th line in txt file and we feed in the array pos		
void DataBaseFunctions::WriteToBinOnceEdit(int FilePos, int arrayPos)
{
	fstream fout;
	fout.open("player.dat", ios::out | ios::_Nocreate | ios::binary);
	if (fout.good())
	{
		fout.seekp(sizeof(Player) * FilePos, ios::beg);
		fout.write((char*)&players[arrayPos], sizeof(Player));
		cout << "file written" << endl;
	}
	fout.close();
}

//writes to file player.dat in binary only if file already exists
//writes in the position in txtfile specified by filepos para e.g if filepos was 5 itd write the 5th line in txt file		
void DataBaseFunctions::WriteToBinOnce(int FilePos)
{
	fstream fout;
	fout.open("player.dat", ios::out | ios::_Nocreate | ios::binary);
	if (fout.good())
	{
		fout.seekp(sizeof(Player) * FilePos, ios::beg);
		fout.write((char*)&players[FilePos], sizeof(Player));
		cout << "file written" << endl;
	}
	fout.close();
}
//reads data from player.dat txtfile. places data read in txt file into players[] dynamic array 
void DataBaseFunctions::LoadSavedData()
{
	fstream fin;
	fin.open("player.dat", ios::in | ios::binary);
	if (fin.good())
	{
		Player* readPlayers = new Player[size];
		Player* originalContent = players;
		for (int i = 0; i < size && fin.good() && fin.peek() != EOF; i++)
		{
			fin.read((char*)&readPlayers[i], sizeof(Player));			//reads values at players[i]
		}
		players = readPlayers;
		delete[] originalContent;										//deleting memory adress of the original version of players
	}
	fin.close();
}

//adds data to players[] array  
void DataBaseFunctions::AddData()
{
	char name[10];
	char highScore[10];
	bool isNumber = false;


	cout << "enter players name you would like to add must have more then 3 chars and less then 10" << endl;
	cin >> name;
	//while  size of chars in name is > 10 or < 3 do while loop - ERROR INPUT CHECKING
	while (strlen(name) > 10 || strlen(name) < 3)
	{
		cout << "name is incorrect format please enter 3 value min or 10 max" << endl;
		cin >> name;
	}
	MakeLettersSmall(name);		//makes input tolower case


	cout << "enter players highscore you would like to add 10 char limit " << endl;
	cin >> highScore;
	while (strlen(highScore) > 10 || strlen(highScore) < 1 || isNumber == false)
	{
		for (int i = 0; i < strlen(highScore); i++)		
		{
			if (!isdigit(highScore[i]))		//checking if each element in highscore is a number
			{
				isNumber = false;
			}
			else
			{
				isNumber = true;
			}
		}
		if (isNumber == false)
		{
			cout << "enter a digit number" << endl;
			cin >> highScore;
		}
	}
	Resize();	//reisize array so we can store 1 more element inside of players array
	Player newPlayer;		//create a variabel to store values inside of
	strcpy_s(newPlayer.playerName, name);		//copy name user inputted inside of the variable
	strcpy_s(newPlayer.highScore, highScore);	//copy highscore user inputted inside of the variable
	newPlayer.id = size -1;
	//newPlayer.id = size;
	players[size - 1] = newPlayer;		//put variable inside of players array. size - 1 because a array starts at element 0 
	//BubbleSort();
	//WriteToBin(ios::out);
	WriteToBinOnce(size - 1);			//write to txt file only writing this value that has changed and not whole array
}

//Edit a value inside of players[] array and changes its values to new ones
void DataBaseFunctions::EditData()
{
	char playerChoice[10];	
	char name[10];
	char highScore[10];
	bool isNumber = false;

	cout << "type name youd like to edit" << endl;
	cin >> playerChoice;

	int result = BinarySearch(players, 0, size - 1, playerChoice);		//using binary search to find where in array the user input is located 
	if (result != -1)		//if found a match do following
	{
		cout << "enter a new name" << endl;
		cin >> name;
		//while  size of chars in name is > 10 or < 3 do while loop - ERROR INPUT CHECKING
		while (strlen(name) > 10 || strlen(name) < 3)
		{
			cout << "name is incorrect format please enter 3 value min or 10 max" << endl;
			cin >> name;
		}
		MakeLettersSmall(name);		//makes input tolower case

		cout << "enter a new highScore" << endl;
		cin >> highScore;
		while (strlen(highScore) > 10 || strlen(highScore) < 1 || isNumber == false)
		{
			for (int i = 0; i < strlen(highScore); i++)
			{
				if (!isdigit(highScore[i]))		//checking if each element in highscore is a number
				{
					isNumber = false;
				}
				else
				{
					isNumber = true;
				}
			}
			if (isNumber == false)
			{
				cout << "enter a digit number" << endl;
				cin >> highScore;
			}
		}

		Player newPlayer;							//copy name user inputted inside of the variable
		strcpy_s(newPlayer.playerName, name);		//copy name user inputted inside of the variable
		strcpy_s(newPlayer.highScore, highScore);	//copy highscore user inputted inside of the variable
		newPlayer.id = players[result].id;
		
		players[result] = newPlayer;				//put variable inside of players array. result being the binary search result		

		WriteToBinOnceEdit(players[result].id, result);					//write to txt file only writing this value that has changed and not whole array
	}
	else
	{
		cout << "incorrect input" << endl;
	}
}

//resize array to increase in size by 1 recreating array adding values from 1 array to another with 1 extra element 
void DataBaseFunctions::Resize()
{
	int newSize = size + 1;
	Player* tempArray = new Player[newSize];
	Player* originalContent = players;
	memcpy(tempArray, players, size * sizeof(Player));		//copying elements from 1 array to new one
	size = newSize;											//increasing values of size by 1
	players = tempArray;									//changing name of temp array back to players
	delete[] originalContent;								//deleting memory adress of the original version of players
}


//sorts elements inside of players[] array alphabetically  
void DataBaseFunctions::BubbleSort()
{
	if (size <= 1)
	{
		return;
	}
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;

		for (int i = 0; i < size - 1; i++)
		{
			if (strcmp(players[i].playerName, players[i + 1].playerName) == 1)	//if first string comes after second string swap
			{
				Player tmp = players[i];

				//swapping
				tmp = players[i];
				players[i] = players[i + 1];		
				players[i + 1] = tmp;			
				sorted = false;
				
			}
		}
	}
}

//returning the position of searchinf for parmeter in players[] array and returns its int position if cant find value return -1 meaning couldnt find
int DataBaseFunctions::BinarySearch(Player* players, int start_index, int end_index, char searchingFor[])
{
	while (start_index <= end_index)
	{
		int middlePoint = (start_index + end_index) / 2;

		if (strcmp(players[middlePoint].playerName, searchingFor) == 0)			//return middle point if found match
			return middlePoint;

		if (string(searchingFor) < string(players[middlePoint].playerName))		//if searching for < middlepoint  middle point - 1
			end_index = middlePoint - 1;

		else
			start_index = middlePoint + 1;										//if searching for > middlepoint  middle point + 1
	}
	return -1;																	//no match? return -1
}

//looking at player.dat txtfile and working out how many elements of sizeof(player)exists inside and using the number to change the value of size
//size used to keep track of players[size] after exiting and opening project 
void DataBaseFunctions::GetValueOfSizeFromFile()
{
	fstream fin;
	fin.open("player.dat", std::ios::in | std::ios::binary | std::ios::ate);
	size = fin.tellg() / sizeof(Player);
	fin.close();
}

//loops through to given array name from parameter and changes each char to a lowercase char
void DataBaseFunctions::MakeLettersSmall(char name[10])
{
	for (int i = 0; i < 10; i++)
	{
		name[i] = tolower(name[i]);
	}
}




