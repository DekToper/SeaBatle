#include <iostream>
#include <time.h>
#include <windows.h>
#include <shlobj.h>
#include <conio.h>
#include <chrono>

#include "Audiere/include/audiere.h"
#define PAUSE system("pause");
#pragma comment (lib, "winmm.lib")

struct player
{
	char result[4] = {' '};
	char name[10] = {' '};
	char party[10] = {' '};
};

void statistic(int choice, int win);
void line(int a,int b,int c,int d);
void print_simvol(int first_simvol);
void print_arena_table(int &t_index, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10]);
void bot_attack(char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool &pooh,char element);
int main(int);
void play_grounds(int,int, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], char);
void main_menu(int);
void size_sheep(int &size, int pos_y, int pos_x, int &first_x, char arrs[10][10]);
void new_pos(int &pos_x, int &pos_y, bool random, bool bot, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], bool,char &element);
void standart_quantity(bool &standart, int &x4_quantity, int &x3_quantity, int &x2_quantity, int &x1_quantity);
using namespace std;


bool lose(char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10])
{
	int k = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (myplay_ground[i][j] == 'X')
			{
				k++;
			}
		}
    }
	if (k == 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void next(int size,int pos_y,int pos_x,int first_x, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool &pooh, char element)
{
	audiere::AudioDevicePtr device = audiere::OpenDevice();
	int ops = 0;
	int ops1 = 0;
	bool destroy = false;
	srand(time(0));
	play_grounds(0, 0 , arr, myplay_ground, bot_arr, play_ground, ' ');
	Sleep(800);
	next_x = pos_x;
	while (true)
	{
		int k = rand() % 2;
		if (destroy == false)
		{
			if (k == 0)
			{
				if (myplay_ground[pos_y][next_x + 1] != 'X')
				{
					next_x++;
				}
				else if (myplay_ground[pos_y][next_x - 1] != 'X')
				{
					next_x--;
				}
				go = true;
			}
			else
			{
				if ( myplay_ground[pos_y][next_x - 1] != 'X')
				{
					next_x--;
				}
				else
				{
					next_x++;
				}
				go = true;
			}
		}
		if (arr[pos_y][next_x] == char(219))
		{
			pooh = true;
			first_x = pos_x;
			setlocale(0, "");
			audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

			sound->play();
			cout << "\t\tПопадание!!!";
			Sleep(1500);
			setlocale(0, "C");
			myplay_ground[pos_y][next_x] = 'X';
			size_sheep(size, pos_y, pos_x, first_x, arr);
			for (int i = 0; i < size; i++)
			{
				if (myplay_ground[pos_y][first_x + i] == 'X')
				{
					destroy = true;
				}
				else
				{
					destroy = false;
					break;
				}
			}
			if (destroy == true)
			{
				audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

				sound->play();
				setlocale(0, "");
				cout << "\n\t\t\tУничтожен!!!";
				Sleep(1500);
				setlocale(0, "C");
				for (int j = pos_y - 1; j < pos_y + 2; j++)
				{
					for (int i = first_x - 1; i < first_x + size + 1; i++)
					{
						if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
						{
							myplay_ground[j][i] = char(177);
							if ((j == pos_y && i >= first_x && i != first_x + size) && arr[j][i] == char(219))
							{
								myplay_ground[j][i] = 'X';
							}
						}
					}
				}
			}
		}
		else
		{
			if (myplay_ground[pos_y][next_x] == char(177))
			{
				if (ops1 != 2)
				{
					if (next_x < first_x)
					{
						ops = 1;
					}
					else
					{
						ops = 0;
					}
				}
				
					
					if (ops == 1)
					{
						ops1 = 2;
						next_x++;
					}
					else
					{
						ops1 = 2;
						next_x--;

					}
				
			}
			else
			{
				
				audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/water.wav", true);

				sound->play();
				pooh = false;
				myplay_ground[pos_y][next_x] = char(177);
				setlocale(0, "");
				cout << "\t\tПромах!!!";
				Sleep(1500);
				setlocale(0, "C");
			}
		}
		play_grounds(0, 0 , arr, myplay_ground, bot_arr, play_ground,' ');
		Sleep(800);
		if (destroy == true)
		{
			go = false;
			bot_attack(arr, myplay_ground, bot_arr, play_ground, next_x,
				next_y,
				go,
				miss,
				pooh,
				element);
			break;
		}
		if (pooh == false)
		{
		
			go = true;
			if (next_x < first_x)
			{
				ops = true;
			}
			else
			{
				ops = false;
			}
			while (true)
			{
				next_y = pos_y;
				if (ops == true)
				{
					next_x++;
					if (myplay_ground[pos_y][next_x] != 'X' && arr[pos_y][next_x] == char(219))
					{
						break;
					}
				}
				else
				{
					next_x--;
					if (myplay_ground[pos_y][next_x] != 'X' && arr[pos_y][next_x] == char(219))
					{
						break;
					}

				}
			}
			break;
		}
		else
		{
			
		}
	}
	
}

void size_sheep(int &size,int pos_y,int pos_x,int &first_x,char arrs[10][10])
{
	bool end_plus = false;
	bool end_mines = false;
	size = 1;
	for (int i = 1; i < 4; i++)
	{
		if (arrs[pos_y][pos_x - i] == char(219) && end_plus == false )
		{
			size++;
			first_x = pos_x - i;
		}
		else
		{
			end_plus = true;
		}
		if (arrs[pos_y][pos_x + i] == char(219) && end_mines == false ) 
		{
			size++;
		}
		else
		{
			end_mines = true;
		}

	}
}

void bot_attack(char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool &pooh, char element)
{
	srand(time(0));
	int k_x = 0;
	int k_y = 0;
	int size = 1;
	int L_R = 0;
	bool all = true;
	audiere::AudioDevicePtr device = audiere::OpenDevice();
	bool destroy = false;

	if (go == true)
	{
		k_x = next_x;
		k_y = next_y;
		go = false;
	}
	else
	{
		new_pos(k_x, k_y, true, true , arr, myplay_ground, bot_arr, play_ground,true,element);
	}

	

	int first_x = k_x;
	
		if (arr[k_y][k_x] == char(219))
		{
			setlocale(0, "");
			audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

			sound->play();
			cout << "\t\tПопадание!!!";
			Sleep(1500);
			setlocale(0, "C");
			all = false;
			myplay_ground[k_y][k_x] = 'X';
			size_sheep(size, k_y, k_x, first_x, arr);
			for (int i = 0; i < size; i++)
			{
				if (myplay_ground[k_y][first_x + i] == 'X')
				{
					destroy = true;
					all = true;
				}
				else
				{
					destroy = false;
					break;
				}
			}
			if (destroy == true)
			{
				setlocale(0, "");
				audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

				sound->play();
				cout << "\n\t\t\tУничтожен!!!";
				Sleep(1500);
				setlocale(0, "C");

				for (int j = k_y - 1; j < k_y + 2; j++)
				{
					for (int i = first_x - 1; i < first_x + size + 1; i++)
					{
						if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
						{
							myplay_ground[j][i] = char(177);
							if ((j == k_y && i >= first_x && i != first_x + size) && arr[j][i] == char(219))
							{
								myplay_ground[j][i] = 'X';
							}
						}
					}
				}
			
			}
			else
			{
				next(size, k_y, k_x,first_x , arr, myplay_ground, bot_arr, play_ground, next_x,
					next_y,
					go,
					miss,
					pooh,
					element);

			}
		
		}
		else
		{
			setlocale(0, "");
			audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/water.wav", true);

			sound->play();
			cout << "\t\tПромах!!!";
			Sleep(1500);
			setlocale(0, "C");
			myplay_ground[k_y][k_x] = char(177);
		}
	
	

}


bool end_game(char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10])
{
	int kols = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (play_ground[i][j] == 'X')
			{
				kols++;
			}
		}
	}
	if (kols == 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void new_pos(int &pos_x, int &pos_y, bool random, bool bot, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], bool in_zone, char &element)
{
	
	srand(time(0));
	if (random == false)
	{
		pos_x = 0;
		pos_y = 0;
		
		while (true)
		{
			if (play_ground[pos_y][pos_x] == char(177) || play_ground[pos_y][pos_x] == 'X')
			{
				pos_x++;
				if (pos_x > 9)
				{
					pos_x = 0;
					pos_y++;
				}
			}
			else
			{
				break;
			}
			
		}
	}
	else
    {
		while (true)
		{
			pos_x = rand() % 10;
			pos_y = rand() % 10;
			if (bot == true)
			{
				if (myplay_ground[pos_y][pos_x] != char(177) && myplay_ground[pos_y][pos_x] != 'X')
				{
					break;
				}
				
			}
			else
			{
				if (play_ground[pos_y][pos_x] != char(177) && play_ground[pos_y][pos_x] != 'X')
				{
					break;
				}
			}
		}
	}
		
	
}

void fire(int pos_x,int pos_y, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool &pooh)
{
	audiere::AudioDevicePtr device = audiere::OpenDevice();
	int k_x = 0;
	int k_y = 0;
	int first_x = 0;
	int size = 1;
	bool destroy = false;
	if (bot_arr[pos_y][pos_x] == char(219))
	{
		play_ground[pos_y][pos_x] = 'X'; 
		setlocale(0, "");
		audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

		sound->play();
		cout << "\n\t\t\tПопадание!!!";
		Sleep(1500);
		setlocale(0, "C");
		first_x = pos_x;
		size_sheep(size, pos_y, pos_x, first_x,bot_arr);
		
			for (int i = 0; i < size; i++)
			{
				if (play_ground[pos_y][first_x + i] == 'X')
				{
					destroy = true;
				}
				else
				{
					destroy = false;
					break;
				}
		    }
			if (destroy == true)
			{
				setlocale(0, "");
				audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/boom2.wav", true);

				sound->play();
				cout << "\n\t\t\tУничтожено!!!";
				Sleep(1500);
				setlocale(0, "C");
				for (int j = pos_y - 1; j < pos_y + 2; j++)
				{
					for (int i = first_x - 1; i < first_x + size + 1; i++)
					{
						if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
						{
							play_ground[j][i] = char(177);
							if ((j == pos_y && i >= first_x && i != first_x + size) && bot_arr[j][i] == char(219))
							{
								play_ground[j][i] = 'X';
							}
						}
					}
				}
				
			}
		
	}
	else
	{
		play_ground[pos_y][pos_x] = char(177);
		miss = true;
		setlocale(0, "");
		audiere::OutputStreamPtr sound = audiere::OpenSound(device, "C:/Users/Діма/source/repos/Project166/Project166/Sounds/water.wav", true);

		sound->play();
		cout << "\n\t\t\tПромах!!!";
		Sleep(1500);
		setlocale(0, "C");
	}

}


void start_fight(char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool pooh)
{
	PlaySound(NULL,NULL,NULL);
	PlaySound("C:/Users/Діма/source/repos/Project166/Project166/Sounds/mix2.wav", NULL, SND_FILENAME | SND_ASYNC);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int pos_x = 0;
	int pos_y = 0;
	int end = 0;
	char element = ' ';
	int choice = 0;
	while (true)
	{
		
		play_grounds(pos_x, pos_y, arr, myplay_ground, bot_arr, play_ground,element);

		setlocale(0, "");
		cout << "Ваш ход(R-рандомная позиция): ";
		setlocale(0, "C");
		end = _getch();
		choice = _getch();
		if (choice == 72)
		{
			if (pos_y - 1 >= 0)
			{
				pos_y--;
				if (play_ground[pos_y][pos_x] == char(177))
				{
					element = char(177);

				}
				else
					element = ' ';
			}
		}
		else if (choice == 80)
		{
			if (pos_y + 1 <= 9)
			{
				pos_y++;
				if (play_ground[pos_y][pos_x] == char(177))
				{
					element = char(177);

				}
				else
					element = ' ';
			}
		}
		else if (choice == 77)
		{
			if (pos_x + 1 <= 9 )
			{
				pos_x++;
				if (play_ground[pos_y][pos_x] == char(177))
				{
					element = char(177);

				}
				else
					element = ' ';
			}
		}
		else if (choice == 75)
		{
			if (pos_x - 1 >= 0)
			{
				pos_x--;
				if (play_ground[pos_y][pos_x] == char(177))
				{
					element = char(177);

				}
				else
					element = ' ';
			}
		}
		else if (end == 13)
		{
			
				fire(pos_x, pos_y, arr, myplay_ground, bot_arr, play_ground,next_x,
					next_y,
					go,
					miss,
					pooh);
				new_pos(pos_x, pos_y, false, false, arr, myplay_ground, bot_arr, play_ground,true,element);
				play_grounds(pos_x, pos_y, arr, myplay_ground, bot_arr, play_ground,element);
				if (end_game(arr, myplay_ground, bot_arr, play_ground))
				{
				
					play_grounds(pos_x, pos_y, arr, myplay_ground, bot_arr, play_ground,element);
					cout << "You win!";
					_getch();
					_getch();
					statistic(1, 1);
					main(0);
				}
			
				if (miss == true)
				{
					setlocale(0, "");
					cout << "Ходит бот: ";
					setlocale(0, "C");
						Sleep(1500);
					bot_attack(arr, myplay_ground, bot_arr, play_ground, next_x,
						next_y,
						go,
						miss,
						pooh,
						element);
					if (lose(arr, myplay_ground, bot_arr, play_ground))
					{
						cout << "You lose!";
						statistic(1, 0);
						_getch();
						_getch();
						main(0);
					}
					miss = false;
				}
		}
		else if (end == int('r'))
		{
			new_pos(pos_x, pos_y,true, false, arr, myplay_ground, bot_arr, play_ground,true,element);
		}
	}
	
}



void play_grounds(int pos_x,int pos_y,char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10],char simvol)
{

	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("mode con cols=60 lines=28");
	int number = 0;
	bool lines = false;
	bool arena_lines = true;
	int first_simvol = 196;
	int second_simvol = 194;

	int else_first_simvol = 179;
	int else_second_simvol = 180;
	cout << endl << endl << endl;
	cout << "   A B C D E F G H I J           A B C D E F G H I J\n";
	

	for (int j = 0; j < 2; j++)
	{
		cout << "  ";
		cout << char(218);
		for (int i = 0; i < 19; i++)
		{
			if (i % 2 == 0)
			{
				cout << char(196);
			}
			else
			{
				cout << char(194);
			}
		}
		cout << char(191);
		if (j == 0)
			cout << "       ";
		else
			cout << endl;
	}
	

	first_simvol = 179;
	second_simvol = 195;
	int z = 0;

	for (int i = 0; i < 19; i++)
	{
		
			if (first_simvol == 179)
			{
				number++;
			}

			for (int k = 0; k < 2; k++)
	     {
				if (first_simvol == 179)
				{
					cout << number;
					if (number != 10)
						cout << " ";
				}

			cout << char(first_simvol);
			if (i % 2 == 0)
			{
				for (int j = 0; j < 10; j++)
				{
					if (k == 0)
						cout << myplay_ground[z][j];
					else
					{
						if(pos_x == j && pos_y == z && play_ground[z][j] != char(177) && play_ground[z][j] != 'X')
						{
							play_ground[z][j] = '*';
							SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 4));
						}
						if (play_ground[z][j] == char(177))
						{
							SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 8));
						}
						if (play_ground[z][j] == 'X')
						{
							SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 4));
						}

						cout << play_ground[z][j];
						SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
						if (play_ground[z][j] == '*')
							play_ground[z][j] = simvol;
					}
					if (j != 9)
						cout << char(179);
				}
				if(k == 1)
				z++;
			}
			else
			{
				for (int j = 0; j < 10; j++)
				{
					cout << char(196);
					if (j != 9)
					{
						cout << char(197);
					}
				}
			}
			cout << char(else_first_simvol);
			if (k == 0)
			{
				if (first_simvol == 179)
				{
					cout << "     ";
				}
				else
				{
					cout << "         ";
				}
			}
			else
				cout << endl;

			if (first_simvol == 179)
			{
				cout << "  ";

			}
	    }
			swap(first_simvol, second_simvol);
			swap(else_first_simvol, else_second_simvol);

			
		
	}

	
	for (int k = 0; k < 2; k++)
	{
		first_simvol = 196;
		second_simvol = 193;
		cout << char(192);
		for (int i = 0; i < 19; i++)
		{
			print_simvol(first_simvol);
			swap(first_simvol, second_simvol);
		}

		cout << char(217);
		if (k == 0)
			cout << "         ";
		else
			cout << endl;
	}

}
void place_bot_tank(char b_arr[10][10])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			b_arr[i][j] = ' ';
		}
	}
	srand(time(0));
	
	int x_k;
	bool can = true;
	int y_k;
	int size = 0;
	bool end = false;
	int sheeps[5] = { 0,4,3,2,1 };
	for (int k = 0; k < 12; k++)
	{
	
		while (true)
		{
			size = 1 + rand() % 4;
			if (sheeps[size] > 0)
			{
				break;
			}
			for (int i = 0; i < 5; i++)
			{
				if (sheeps[i] == 0)
				{
					end = true;
				}
				else
				{
					end = false;
					break;
				}
			}
			if (end == true)
			{
				break;
			}
		}

		while (true)
		{
			if (end == true)
			{
				break;
			}
			x_k = rand() % (10 - size);
			y_k = rand() % 10;
			for (int j = y_k - 1; j < y_k+2; j++)
			{
		for (int i = x_k - 1; i < x_k+size+1; i++)
				{
					if (b_arr[j][i] == char(219))
					{
						can = false;
					}
				}
			}
			if (can == false)
			{
				can = true;
			}
			else
			{
				for (int i = x_k; i < x_k+size; i++)
				{
					b_arr[y_k][i] = char(219);
				
				}
				sheeps[size]--;
				break;
			}
		}

	}


}




void place_tank(int &t_index,int sheeps[5], char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10])
{
	srand(time(0));
	bool can = true;
	int i_t = 0;
	int j_t = 0;
	bool next = true;

	setlocale(0, "C");

	int size = 0;

	
	if (t_index == 1)
	{
		size = 4;
	}
	else if (t_index == 2)
	{
		size = 3;
	}
	else if (t_index == 3)
	{
		size = 2;
	}
	else if (t_index == 4)
	{
		size = 1;
	
	}
	

	

	if (sheeps[size] != 0)
	{
		while (true)
		{

			for (int i = i_t; i < i_t + 3; i++)
			{
				for (int j = j_t; j < j_t + (size + 2); j++)
				{
					if (arr[i][j] == char(219))
					{
						if (i_t + 2 < 10 || i_t + 3 < 10 )
						{
							i_t += 2;
							if (arr[i_t - 1][j_t] == char(219))
							{
								i_t++;
							}

						}
						else
						{
							i_t = 0;
							j_t += (size + 2);
						}
						can = false;
						break;
					}
					if (arr[i_t + 1][j_t - 1] == char(219))
					{
						i_t++;
					}

					if (arr[i_t - 1][j_t - 1] == char(219))
					{
						i_t++;
					}
				}
				if (can == false)
				{
					break;
				}

			}
			if (can == false)
			{
				can = true;
			}
			else
			{

				if (arr[i_t][j_t - 1] == char(219))
				{
					j_t++;
				}

				for (int i = 0; i < size; i++)
					{
					for (int i = -1; i < size + 1; i++)
					{
						if (arr[i_t - 1][j_t + i] == char(219))
						{
							can = false;
							i_t++;
							break;
							
						}
					}
					if (can == true)
						arr[i_t][j_t + i] = char(219);
					else
						break;
					}
				if(can == true)
					break;
				
			}
		}
		sheeps[size]--;

		char routate = 0;
		print_arena_table(t_index, arr, myplay_ground, bot_arr, play_ground);
		while (routate != 13)
		{
			cout << "Muve(< v ^ >):";
			routate = _getch();
			int muve = _getch();
			


				bool rout = true;

				if (muve == 72)
				{
					if (i_t - 1 != -1)
					{
						if (i_t - 1 != 0)
						{
							for (int i = -1; i < size + 1; i++)
							{
								if (arr[i_t - 2][j_t + i] == char(219))
								{
									next = false;
								}
							}
						}
						if (next == false)
						{
							next = true;
						}
						else
						{
							for (int i = 0; i < size; i++)
							{
								arr[i_t][j_t + i] = ' ';
								arr[i_t - 1][j_t + i] = char(219);
							}
							i_t--;
						}

					}


				}
				else if (muve == 80)
				{
					if (i_t + 1 != 10)
					{
						if (i_t + 1 != 9)
						{
							for (int i = -1; i < size + 1; i++)
							{
								if (arr[i_t + 2][j_t + i] == char(219))
								{
									next = false;
								}
							}
						}
						if (next == false)
						{
							next = true;
						}
						else
						{
							for (int i = 0; i < size; i++)
							{
								arr[i_t][j_t + i] = ' ';
								arr[i_t + 1][j_t + i] = char(219);
							}
							i_t++;
						}

					}

				}
				else if (muve == 77)
				{
					if (j_t + 1 != 10)
					{
						if (j_t + 1 != 9)
						{
							for (int i = -1; i < 2; i++)
							{
								if (arr[i_t + i][j_t + size+1] == char(219))
								{
									next = false;
								}
							}
						}
						if (next == false)
						{
							next = true;
						}
						else
						{

								arr[i_t][j_t] = ' ';
								arr[i_t][j_t + size] = char(219);

							j_t++;
						}

					}

				}
				else if (muve == 75)
				{
					if (j_t - 1 != -1)
					{
						if (j_t - 1 != 0)
						{
							for (int i = -1; i < 2; i++)
							{
								if (arr[i_t + i][j_t - 2] == char(219))
								{
									next = false;
								}
							}
						}
						if (next == false)
						{
							next = true;
						}
						else
						{

							arr[i_t][j_t + size-1] = ' ';
							for(int i = -1; i < size - 1; i++)
							arr[i_t][j_t + i] = char(219);

							j_t--;
						}

					}

				}



			print_arena_table(t_index, arr, myplay_ground, bot_arr, play_ground);
		}
	}
}

void print_arena_table(int &tank_index, char arr[10][10], char myplay_ground[10][10], char bot_arr[10][10], char play_ground[10][10])
{
	int number = 1;
	bool lines = false;
	bool arena_lines = true;
	int first_simvol = 196;
	int second_simvol = 194;

	int else_first_simvol = 179;
	int else_second_simvol = 180;
	system("cls");
	
	
	cout << endl << endl << endl;
	cout << "   A B C D E F G H I J \n  ";
	cout << char(218);
	
	for (int i = 0; i < 19; i++)
	{
		if (i % 2 == 0)
		{
			cout << char(196);
		}
		else
		{
			cout << char(194);
		}
	}
	cout << char(191) << endl;

	first_simvol = 179;
	second_simvol = 195;
	int z = 0;
	for (int i = 0; i < 19; i++)
	{
		
		if (first_simvol == 179)
		{
			cout << number;
			if(number != 10)
			cout << " ";
			number++;
		}
		cout << char(first_simvol);
		if (i % 2 == 0)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << arr[z][j];
				if (j != 9)
					cout << char(179);
			}
			z++;
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				cout << char(196);
				if (j != 9)
				{
					cout << char(197);
				}
			}
		}
		cout << char(else_first_simvol);
		cout << endl;
		if (first_simvol == 179)
		{
			cout << "  ";

		}
		swap(first_simvol, second_simvol);
		swap(else_first_simvol, else_second_simvol);
	}

	first_simvol = 196;
	second_simvol = 193;

	cout << char(192);
	for (int i = 0; i < 19; i++)
	{
		print_simvol(first_simvol);
		swap(first_simvol, second_simvol);
	}

	cout << char(217) << endl;

	int x4_quantity;
	int x3_quantity;
	int x2_quantity;
	int x1_quantity;
	bool standart = true;
	if (standart == true)
	{
		standart_quantity(standart, x4_quantity, x3_quantity, x2_quantity, x1_quantity);
	}

	cout << char(178) << char(178) << char(178) << char(178) << " " << char(62) << " x" << x4_quantity;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (tank_index == 1)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 12));
		cout << " << ";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	}

	cout << endl << endl;
	cout << char(178) << char(178) << char(178) << " " << char(62) << " x" << x3_quantity;
	if (tank_index == 2)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 12));
		cout << " << ";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	}

	cout << endl << endl;
	cout << char(178) << char(178) << " " << char(62) << " x" << x2_quantity;
	if (tank_index == 3)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 12));
		cout << " << ";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	}

	cout << endl << endl;
	cout << char(178) << " " << char(62) << " x" << x1_quantity;
	if (tank_index == 4)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 12));
		cout << " << ";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	}
	cout << endl;
	cout << "Random:";
	if (tank_index == 5)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 12));
		cout << " << ";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	}
	

}

void choice_tank(int &tank_index,int &choice_t)
{
	
	int choice = _getch();
	choice_t = choice;
	choice = _getch();
	

	

	if (choice == 80)
	{
		
		tank_index++;
		if (tank_index == 6)
		{
			tank_index--;
		}
	}
	if (choice == 72)
	{
		tank_index--;
		if (tank_index == 0)
		{
			tank_index++;
		}
	}

	
}

void standart_quantity(bool &standart,int &x4_quantity,int &x3_quantity, int &x2_quantity, int &x1_quantity)
{
	x4_quantity = 1;
	x3_quantity = 2;
	x2_quantity = 3;
	x1_quantity = 4;

	standart = false;

}


void build_arena(char arr[10][10],char myplay_ground[10][10],char bot_arr[10][10],char play_ground[10][10], int &next_x, int &next_y, bool &go, bool &miss, bool &pooh)
{
	int tank_index = 1;
	system("mode con cols=25 lines=30");
	int choice_t = 0;
	int sheeps[5] = { 0,4,3,2,1 };
	int bot_sheeps[5] = { 0,4,3,2,1 };
	bool end = false;
	int choice = 0;
	bool next = true;

	while (true)
	{
		print_arena_table(tank_index, arr, myplay_ground, bot_arr, play_ground);
		if (tank_index != 5 || next == true)
		{
			choice_tank(tank_index, choice_t);
			
		}

		if (tank_index == 5)
		{
		
			if (choice_t == 13)
			{
				next = false;
			place_bot_tank(arr);
			system("cls");
			print_arena_table(tank_index, arr, myplay_ground, bot_arr, play_ground);
			cout << "One more?: ";
			cin >> choice;
			if (choice == 0)
			{

				system("cls");
				place_bot_tank(bot_arr);
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						myplay_ground[i][j] = arr[i][j];
					}
				}
				start_fight(arr, myplay_ground, bot_arr, play_ground,next_x,
					next_y,
					go,
					miss,
					pooh);

			}
			}
		}
		else
		{
			
				for (int i = 0; i < 5; i++)
				{
					if (sheeps[i] == 0)
					{
						end = true;
					}
					else
					{
						end = false;
						break;
					}
				}
			

			if (end == true || choice == 1)
			{
				system("cls");
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						myplay_ground[i][j] = arr[i][j];
					}
				}
				place_bot_tank(bot_arr);
				start_fight(arr, myplay_ground, bot_arr, play_ground,next_x,
					next_y,
					go,
					miss,
					pooh);
			}

			if (choice_t == 13)
			{
				place_tank(tank_index, sheeps, arr, myplay_ground, bot_arr, play_ground);
			}
		}
	}
}

void choice(int &choice_index, int &alt_save)
{


		int alt_choice = _getch();
		alt_save = alt_choice;
		alt_choice = _getch();


	if (alt_choice == 75)
	{
		choice_index--;
		if (choice_index == 0)
		{
			choice_index++;
		}
	}
	else if (alt_choice == 77)
	{
		choice_index++;
		if (choice_index == 5)
		{
			choice_index--;
		}
	}
	
}

void print_simvol(int alt_kod)
{
	cout << char(alt_kod);
}
void empty_line(int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << " ";
	}
}
void line(int first_kod, int midle_kod, int m_size, int last_kod)
{
	cout << char(first_kod);
	for (int i = 0; i < m_size; i++)
	{
		cout << char(midle_kod);
	}
	cout << char(last_kod);
}
void print_pixel(int index)
{
	if (index == 16)
	{
		index = 15;
	}

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((index << 4) | 15));
	cout << " ";
	
}

void start_menu()
{
	int arr[18][42] = { {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,7,7,6,7,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 },
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,6,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,6,6,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,7,7,7,7,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,8,16,16,16,16,16,0,0,0,7,16,16,16,16,16,8,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,8,16,16,16,7,7,7,7,7,16,16,16,16,8,16,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,8,8,7,7,16,16,0,0,0,7,0,16,16,7,7,8,8,16,16,16,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,16,8,16,16,16,16,8,16,16,16,16,7,7,7,7,16,7,7,7,7,7,16,7,7,7,7,16,16,16,16,8,16,16,16,16,16,16 },
	{ 16,16,16,16,16,16,16,8,7,16,16,16,8,7,16,16,0,0,7,0,16,0,0,7,0,7,16,0,7,0,0,16,16,7,8,16,16,16,16,16,16,16},
	{ 16,16,16,16,16,7,7,7,7,16,16,7,7,7,16,16,7,7,7,7,16,7,7,7,0,7,16,7,7,7,7,16,16,7,7,7,16,16,16,16,16,16 },
	{ 16,8,8,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8,16,16,16,16 },
	{ 16,16,7,7,7,7,7,0,7,0,7,0,7,0,7,7,7,7,7,7,7,7,0,7,0,7,7,0,7,7,0,7,0,7,0,7,7,7,16,16,16,16},
	{ 16,16,16,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8 ,8,16,16,16,16},
	{ 16,16,16,16,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,16,16,16,16},
	{ 16,16,16,16,16,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,16,16,16,16,16 },
	{ 16,16,3,3,16,7,3,3,7,7,3,3,7,7,3,3,7,7,3,3,7,7,3,3,7,7,3,3,7,7,3,3,7,7,3,3,7,16,3,3,16,16 },
	{ 3,3,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3,3,3,3,3},
	};
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl;
	cout << endl;
	for (int i = 0; i < 17; i++)
	{
		cout << "\t\t\t\t\t";
		for (int j = 0; j < 42; j++)
		{
			print_pixel(arr[i][j]);
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 11));
	
	cout << "\t\t\t\t      ____        _   _   _       _____ _     _      \n"
		<< "\t\t\t\t     |  _ \\      | | | | | |     / ____| |   (_)  \n"
		<< "\t\t\t\t     | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __ \n"
		 << "\t\t\t\t     |  _ < / _` | __| __| |/ _ \\\\___ \\| \'_ \\| | \'_ \\ \n";
		SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
		cout << "\t\t\t\t     | |_) | (_| | |_| |_| |  __/____) | | | | | |_) |\n"
		<< "\t\t\t\t     |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/ \n"
		<< "\t\t\t\t                                               | |  \n"
		<< "\t\t\t\t                                               |_|   \n";
	SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 0));
}


void main_menu(int choice_index)
{
	system("mode con cols=80 lines=25");
	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 11));

	cout << "\t        ____        _   _   _       _____ _     _      \n"
		<< "\t       |  _ \\      | | | | | |     / ____| |   (_)  \n"
		<< "\t       | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __ \n"
		<< "\t       |  _ < / _` | __| __| |/ _ \\\\___ \\| \'_ \\| | \'_ \\ \n";
	SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
	cout << "\t       | |_) | (_| | |_| |_| |  __/____) | | | | | |_) |\n"
		<< "\t       |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/ \n"
		<< "\t                                                 | |  \n"
		<< "\t                                                 |_|   \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(176);
		}
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(177);
		}
		cout << endl;
	}

		for (int j = 0; j < 80; j++)
		{
			print_simvol(178);
		}
		cout << endl;

		for (int i = 0; i < 3; i++)
		{
		
			empty_line(5);
			line(218, 196, 18, 191);
		}

		empty_line(5);

        	empty_line(5);
			print_simvol(179);
			if (choice_index == 1)
			{
				SetConsoleTextAttribute(hStdOut, (WORD)((11 << 4) | 3));
			}
			cout << "       Exit       ";
			SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
			print_simvol(179);

			empty_line(5);
			print_simvol(179);
			if (choice_index == 2)
			{
				SetConsoleTextAttribute(hStdOut, (WORD)((11 << 4) | 3));
			}
			cout << "  Single Player   ";
			SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
			print_simvol(179);
			empty_line(5);
			print_simvol(179);
			if (choice_index == 3)
			{
				SetConsoleTextAttribute(hStdOut, (WORD)((11 << 4) | 3));
			}
			cout << "       Rules      ";
			SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
			print_simvol(179);
			empty_line(5);

			for (int i = 0; i < 3; i++)
			{
			    empty_line(5);
				line(192, 196, 18, 217);
			}
			cout << endl;
			empty_line(30);
			line(218, 196, 18, 191);
			cout << endl;
			empty_line(30);
			print_simvol(179);
			if (choice_index == 4)
			{
				SetConsoleTextAttribute(hStdOut, (WORD)((11 << 4) | 3));
			}
			cout << "    Statistic     ";
			SetConsoleTextAttribute(hStdOut, (WORD)((15 << 4) | 3));
			print_simvol(179);
			cout << endl;
			empty_line(30);
			line(192, 196, 18, 217);
			cout << endl;
			for (int j = 0; j < 80; j++)
			{
				print_simvol(178);
			}
			cout << endl;

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 80; j++)
				{
					print_simvol(177);
				}
				cout << endl;
			}
			
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 80; j++)
				{
					print_simvol(176);
				}
				cout << endl;
			}
			
		

		
}
void rules()
{
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(176);
		}
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(177);
		}
		cout << endl;
	}

	for (int j = 0; j < 80; j++)
	{
		print_simvol(178);
	}
	cout << endl;

	
	setlocale(0, "");

		cout << "\n\n\n\n\n";
	
	cout << "Управление: ";

	cout << "1. <^v> -- Перемещать кораблики,прицели выбор.";
	cout << "\n";
	cout << "2. 1 -- Число для подтверждения действий.";
	cout << "\n";
	cout << "3. 0 -- Число для отклонения действия.";
	cout << "\n\n\n\n\n";

	setlocale(0, "C");
	cout << endl;
	for (int j = 0; j < 80; j++)
	{
		print_simvol(178);
	}
	cout << endl;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(177);
		}
		cout << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(176);
		}
		if(i != 2)
		cout << endl;
	}

	_getch();
	_getch();
}



void statistic(int choice,int win)

{
	system("mode con cols=80 lines=25");
	system("cls");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(176);
		}
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			print_simvol(177);
		}
		cout << endl;
	}

	for (int j = 0; j < 80; j++)
	{
		print_simvol(178);
	}
	cout << endl;


	setlocale(0, "");

	cout << "\n\n";

	

	player newPlayer;
	
	if (choice == 1)
	{
		FILE *Redactor;
		PlaySound("C:/Users/Діма/source/repos/Project166/Project166/Sounds/mix.wav", NULL, SND_FILENAME | SND_ASYNC);
		cout << "\t\tСтатистика:\n\n";
		cout << "Введите Имя пользователя(Eng): ";
		cin.getline(newPlayer.name, 10);
		cin.getline(newPlayer.name, 10);
		cout << "Название команды: ";
		cin.getline(newPlayer.party, 10);

		if (win == 1)
		{
			newPlayer.result[0] = 'w';
			newPlayer.result[1] = 'i';
			newPlayer.result[2] = 'n';
			newPlayer.result[3] = ' ';
		}
		else if (win == 0)
		{
			newPlayer.result[0] = 'l';
			newPlayer.result[1] = 'o';
			newPlayer.result[2] = 's';
			newPlayer.result[3] = 'e';
		}

		fopen_s(&Redactor, "redactor.txt", "ab+");
		fwrite(&newPlayer, 1, sizeof(player), Redactor);
		fclose(Redactor);

		fopen_s(&Redactor, "redactor.txt", "rb+");
		system("cls");
	}
	else if (choice == 2)
	{
		setlocale(0, "");
			FILE *Redactor;
			fopen_s(&Redactor, "redactor.txt", "ab+");
			fclose(Redactor);
			if (Redactor == NULL)
			{
				cout << "Список пустой!!\n";
			}
			else
			{
				fopen_s(&Redactor, "redactor.txt", "ab+");
				fseek(Redactor, 0L, SEEK_END);
				int playerAmount = ftell(Redactor) / sizeof(player);
				player *temp = new player[playerAmount];
				fseek(Redactor, 0L, SEEK_SET);
				for (int i = 0; i < playerAmount; i++)
					fread(&temp[i], 1, sizeof(player), Redactor);
				fclose(Redactor);


				if (playerAmount > 15)
					playerAmount = 15;

				cout << "\t\tСтатистика:\n\n";
				cout << "№       " << "Имя" << '\t' << "Команда" << endl;
				for (int lt = 0; lt < playerAmount; lt++)
					cout << lt + 1 << ')' << '\t' << temp[lt].name << '\t' << temp[lt].party << '\t' << temp[lt].result << endl;
				Sleep(2000);
				fopen_s(&Redactor, "redactor.bin", "wb+");
				for (int ps = 0; ps < playerAmount; ps++)
					fwrite(&temp[ps], 1, sizeof(player), Redactor);
				fclose(Redactor);
				delete[] temp;
			}
		system("cls");
	}
}


int main(int sleep)
{
	setlocale(0, "C");
	PlaySound("C:/Users/Діма/source/repos/Project166/Project166/Sounds/mix.wav", NULL, SND_FILENAME | SND_ASYNC);

	int next_x = 0;
	int next_y = 0;
	bool go = false;
	bool miss = false;
	bool pooh = false;
	
	char arr[10][10] = { ' ' };
	char bot_arr[10][10] = { ' ' };
	char play_ground[10][10] = { ' ' };
	char myplay_ground[10][10] = { ' ' };
	if (sleep != 0)
	{
		sleep = 7000;
    } 
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				arr[i][j] = ' ';
				bot_arr[i][j] = ' ';
				play_ground[i][j] = ' ';
				myplay_ground[i][j] = ' ';
			}
		}
	}

	int choice_index = 2;
	int alt_save = 0;

	system("color F0");

    start_menu();

	if (sleep != 0)
	{	
		Sleep(sleep);
	}

	main_menu(choice_index);
	
	while (true)
	{
		choice(choice_index, alt_save);
		main_menu(choice_index);
		if (alt_save == 13)
		{
			if (choice_index == 1)
			{
				
				exit(0);
				exit(0);
				exit(0);
			}
			else if (choice_index == 2)
			{
				build_arena(arr,
					myplay_ground,
					bot_arr,
					play_ground,
					next_x,
					next_y,
					go,
					miss,
					pooh);

			}
			else if (choice_index == 3)
			{
				rules();
				main_menu(choice_index);
					
			}
			else
			{
				statistic(2, NULL);
				setlocale(0, "C");
				main_menu(choice_index);
				
			}
		}
	}

}