#include<iostream>
#include <fstream>
#include<string>
#include<windows.h>
#include<iomanip>


using namespace std;
class MyScreen
{
private:
	HANDLE screen;
public:
	MyScreen()
	{
		screen = GetStdHandle(STD_OUTPUT_HANDLE);

	}
	MyScreen(HANDLE s)
	{
		screen = s;
	}
	void placeCursor(int row, int col);
};
void MyScreen::placeCursor(int row, int col)
{
	COORD position;
	position.Y = row;
	position.X = col;

	SetConsoleCursorPosition(screen, position);
}

class Team
{
public:

	string team_name = " ";
	int    lose_count;
	int    win_count;
	string city = " ";
	int year = 0;
};

int search_for_team(Team *p_teams[], Team search, int num)
{

	for (int i = 0; i < num; i++)
	{
		if (p_teams[i]->team_name == search.team_name)
		{
			return i;
		}
	}

	return -1;
}

int openData(Team *arr[], int &num, string lose_team[], string win_team[], int year[])
{
	
	Team c;
	int count = 0;
	int max = 1000;
	char line[80];
	char space = ' ';
	ifstream dataIn;

	dataIn.open("team.txt");

	if (!dataIn.is_open())
	{
		cout << "Error opening the data file.\n";
	}

	while (!dataIn.eof() && (count < max))
	{

		{
			dataIn.getline(line, 80);

			size_t where = 0;

			c.year =  stoi(line, &where);
		
			year[num] = c.year;
			//where = 5;
			c.team_name = "";
			c.city = "";

			while (line[where] == ',')
			{
				where++;
			}
			while (line[where] != ' ')
			{
				c.city += line[where];
				where++;
			}
			if (c.city == "Los" || c.city == "New" || c.city == "San" || c.city == "Kansas" || c.city == "St." || c.city == "Tampa")
			{
				where++;
				c.city += space;
				while (line[where] != ' ')
				{
					c.city += line[where];
					where++;
				}
			}
			while (line[where] == ' ')
			where++;

			while (line[where] != ',')
			{

				c.team_name += line[where];
				where++;
			}

			if (c.team_name[c.team_name.length() - 1] == ' ')
				c.team_name = c.team_name.substr(0, c.team_name.length() - 1);
			if (c.team_name[0] == ' ')
				c.team_name = c.team_name.substr(1);

			win_team[num] = c.team_name;
			int found_index = search_for_team(arr, c, count);

			if (found_index >= 0)
			{
				arr[found_index]->win_count++;
			}
			else
			{
				arr[count] = new Team();
				arr[count]->team_name = c.team_name;
				arr[count]->city = c.city;
				arr[count]->win_count = 1;
				arr[count]->lose_count = 0;
				count++;
			}

		
			c.team_name = "";
			c.city = "";
			c.year = 0;
			while (line[where] == ' ')
			{

				where++;
			}
			where++;

			while (line[where] != ' ')
			{
				c.city += line[where];
				where++;
			}
			if (c.city == "Los" || c.city == "New" || c.city == "San" || c.city == "Kansas" || c.city == "St." || c.city == "Tampa")
			{

				where++;
				c.city += space;

				while (line[where] != ' ')
				{
					c.city += line[where];
					where++;
				}

			}


			while (line[where] != NULL)
			{

				c.team_name += line[where];
				where++;
			}

			if (c.team_name[c.team_name.length() - 1] == ' ')
				c.team_name = c.team_name.substr(0, c.team_name.length() - 1);

			if (c.team_name[0] == ' ')
				c.team_name = c.team_name.substr(1);

			lose_team[num] = c.team_name;
			found_index = search_for_team(arr, c, count);


			if (found_index >= 0)
			{
				arr[found_index]->lose_count++;
			}

			else
			{

				Team temp = c;

				arr[count] = new Team(temp);
				arr[count]->team_name = c.team_name;
				arr[count]->win_count = 0;
				arr[count]->lose_count = 1;
				count++;
			}
			

		}
		num++;
	}
	dataIn.close();

	
	return count;

}



int getChoice()
{
	int c;
	cin >> c;

	while (c < 1 && c > 5)
	{
		cout << "Try again\n";
		cin >> c;
	}
	return c;
}

void menu()
{

	cout << "			WORLD SERIES";
	cout << "\n*******************************************************************";
	cout << endl;

	cout << "Menu:\n"
		<< "1. Team with one or more win\n"
		<< "2. Team with one or more lost\n"
		<< "3. Team that has played in the world series but never win\n"
		<< "4. Team that has won a world series and never lost\n"
		<< "5. Years Played\n"
		<< "6. Decade Results\n"
		<< "exit (0)";
}
void sort_win(Team *arr[], int num)
{
	int start;
	int found;

	for (start = 0; start < num; start++)
	{
		found = start;
		for (int idx = start + 1; idx < num; idx++)
		{
			if (arr[idx]->win_count > arr[found]->win_count)
			{
				found = idx;
			}

		}
		if (found != start)
		{
			Team *temp;
			temp = arr[start];
			arr[start] = arr[found];
			arr[found] = temp;

		}

	}
}

void sort_lose(Team *arr[], int num)
{
	int start;
	int found;

	for (start = 0; start < num; start++)
	{
		found = start;
		for (int idx = start + 1; idx < num; idx++)
		{
			if (arr[idx]->lose_count < arr[found]->lose_count)
			{
				found = idx;
			}

		}
		if (found != start)
		{
			Team *temp;
			temp = arr[start];
			arr[start] = arr[found];
			arr[found] = temp;

		}

	}
}
void display_lose(Team *arr[], int count)
{
	MyScreen scr;
	menu();
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";
	cout << "Teams with one or more world series lost\n";
	cout << "\n Team list    losses  \n";
	cout << "--------------------------------\n";
	for (int i = 0; i < count; i++)
	{
		if (arr[i]->lose_count != 0)
		{
			cout << left << fixed << setw(15) << arr[i]->team_name << fixed << setw(10) << arr[i]->lose_count << endl;
		}
	}

}

void display_wins(Team *arr[], int count)
{
	MyScreen scr;
	menu();
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";
	cout << "Teams with one or more world series win\n";
	cout << "\nTeam list     wins  \n";
	cout << "--------------------------\n";
	for (int i = 0; i < count; i++)
	{
		if (arr[i]->win_count != 0)
		{
			cout << left << fixed << setw(15) << arr[i]->team_name << fixed << setw(10) << arr[i]->win_count << endl;
		}
	}
}

void no_loss(Team *arr[], int num)
{
	MyScreen scr;
	int start;

	bool none = true;
	menu();
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";
	cout << "These are teams that has played in the world and never lost.\n\n";
	cout << " Team names  wins   \n";
	cout << "-----------------------------\n";
	for (start = 0; start < num; start++)

		if (arr[start]->lose_count == 0)
		{
			cout << left << fixed << setw(15) << arr[start]->team_name << fixed << setw(20) << arr[start]->win_count << endl;
			none = false;
		}
	if (none)
		cout << "None found.\n";
}
void no_wins(Team *arr[], int num)
{
	MyScreen scr;
	int start;

	bool none = true;
	menu();
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";
	cout << "These are teams that has played in the world but never win.\n\n";
	cout << " Team names   losses   \n";
	cout << "----------------------------------------\n";
	for (start = 0; start < num; start++)

		if (arr[start]->win_count == 0)
		{
			cout << left << fixed << setw(15) << arr[start]->team_name << fixed << setw(20) << arr[start]->lose_count << endl;
			none = false;
		}
	if (none)
		cout << "None found.\n";
}

void search_year(Team *arr[], int &num, string lose_team[], string win_team[], int year[])
{

	MyScreen scr;
	
	string team;
	menu();
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";

	cout << "Enter team name: ";
	while (team.length()==0) {
		getline(cin, team);
	}

		
	cout << "\n  Year         Winner          Loser\n";

	cout << "----------------------------------------\n";
	
	for (int start = 0; start < num; start++)

	{
		if (team == win_team[start])
		{
			cout << left << fixed << setw(15) << year[start] << left << fixed << setw(15) << win_team[start] << left << fixed << setw(15) << lose_team[start] << endl;
			
		}
		if (team == lose_team[start])
		{
			cout << left << fixed << setw(15) << year[start] << left << fixed << setw(15) << win_team[start] << left << fixed << setw(15) << lose_team[start] << endl;
			
		}
	}

	cout << "\n		Press enter key";
}
void search_decade(Team *arr[], int &num, string lose_team[], string win_team[], int year[])
{
	MyScreen scr;
	int decade;
	bool none = true;
	menu();
	int add = 10;
	scr.placeCursor(12, 0);
	cout << "*******************************************************************\n";

	cout << "Enter decade (1900-2017): ";
	cin >> decade;

	cout << "  Year         Winner          Loser\n";
	cout << "----------------------------------------\n";
	if (decade > 1899 && decade < 2018)
	{
		if (decade == 1900)
		{
			for (int i = 0; i < 3; i++)
			{
				cout << left << fixed << setw(15) << decade + i << left << fixed << setw(15) << "----" << left << fixed << setw(15) << "---" << endl;
			}

			for (int i = 0; i < 6; i++)
			{
				cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;

			}
		}
		else if (decade == 1901)
		{
			for (int i = 0; i < 2; i++)
			{
				cout << left << fixed << setw(15) << decade + i << left << fixed << setw(15) << "----" << left << fixed << setw(15) << "---" << endl;
			}

			for (int i = 0; i < 7; i++)
			{
				cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;

			}
		}
		else if (decade == 1902)
		{
			for (int i = 0; i < 1; i++)
			{
				cout << left << fixed << setw(15) << decade + i << left << fixed << setw(15) << "----" << left << fixed << setw(15) << "---" << endl;
			}

			for (int i = 0; i < 8; i++)
			{
				cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;

			}
		}
		else if (decade == 1904 || decade==1994)
		{
			for (int start = 0; start < num; start++)
			{
				if (year[start] == decade + 1)
				{
					cout << left << fixed << setw(15) << decade << left << fixed << setw(15) << "----" << left << fixed << setw(15) <<"---" << endl;
					for (int i = start; i < start + add - 1; i++)
					{
						cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;
					}
				}
			}
		}
			
			for (int start = 0; start < num; start++)
			{
				if (decade == year[start])
				{
					for (int i = start; (i < start + add) && (i < num); i++)
					{
						if (year[i] == 1903 || year[i] == 1993)
						{
							cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;
							i++;
							cout << left << fixed << setw(15) << "----" << left << fixed << setw(15) << "----" << left << fixed << setw(15) << "----" << endl;

							add -= 1;

						}
						cout << left << fixed << setw(15) << year[i] << left << fixed << setw(15) << win_team[i] << left << fixed << setw(15) << lose_team[i] << endl;
					
					}
				}
				
			}

		
	}
	else
		cout << "None found";

	
}

int main()
{
	string lose_team[1000];
	string win_team[1000];
	Team *p_contain[1000];
	int year[1000];
	Team c;
	int count = 0;
	MyScreen scr;
	int choice = 0;
	int raw_count = 0;
	count = openData(p_contain, raw_count, lose_team, win_team, year);
	menu();
	cout << "\nCommand: ";
	choice = getChoice();

	while (choice != 0)
	{
		if (choice == 1)
		{
			system("cls");
			sort_win(p_contain, count);
			display_wins(p_contain, count);
		}
		if (choice == 2)
		{
			system("cls");
			sort_lose(p_contain, count);
			display_lose(p_contain, count);

		}
		if (choice == 3)
		{
			system("cls");
			no_wins(p_contain, count);
		}
		if (choice == 4)
		{
			system("cls");
			no_loss(p_contain, count);
		}
		if (choice == 5)
		{
			system("cls");
			search_year(p_contain, raw_count, lose_team, win_team, year);
		}
		if (choice == 6)
		{
			system("cls");
			search_decade(p_contain, raw_count, lose_team, win_team, year);
		}

		cin.ignore();
		scr.placeCursor(10, 0);
		cout << "Command: ";
		choice = getChoice();

		
	}


	return 0;
}
