//January 14, 2018
//CompSci 30S - Huacheng Qin
/*Algorithms: 
	This is a program that generates an array containing a desired amount (up to a maximum)
	of random numbers, then allows the user to use a variety of sorting methods to sort it.
	The user may also search for a value using linear search, or binary search on a sorted array
	
  Vsort: Vsort is the visualization of the sorting algorithms, it uses inefficient methods to
         create the visualization so large arrays are not recommended
	*/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "colours.h"
using namespace std;

//Declare constants
const int MAX = 100;			//Maximum size of arrays

//Function prototypes
void seedran();													//Seeds the random number generator
char menu(bool generate, bool sort, bool &order);	//Prints menu and allows the user to choose an option
void generatelist(int list[MAX], int &length);					//Assigns random numbers to array
void printlist(int list[MAX], int length);						//Prints array
void swap(int &num1, int &num2);								//Switches the place of two numbers
void SRprint(int num, int pos, int compares, bool found);		//Prints search results
void bubble(int list[MAX], int length, bool order, bool Vsort);	//Sorts array using bubble sort
void insert(int list[MAX], int length, bool order, bool Vsort);	//Sorts array using insert sort
void selection(int list[MAX], int length, bool order, bool Vsort);	//Sorts array using selection sort
void linear(int list[MAX], int length);							//Finds value using linear search
void binary(int list[MAX], int length, bool order);				//Finds value using binary search
void space(int num, bool index);								//Puts spaces in front/behind numbers
void shell(int list[MAX], int length, bool order, bool Vsort);	//Sorts array using shell sort

//Main program
int main(void)
{
	int list[MAX];			//Array containing numbers
	char choice;			//User choice
	bool generate = false;	//Whether a list has been generated
	bool sort = false;		//Whether the list has been sorted
	int length;				//How long the user wants the array to be
	bool order;				//Whether the user wants the array to be in ascending or descending order
	bool Vsort;				//Whether or not Vprint will used

	//Seed random number generator
	seedran();

	//Ask if the user wants to visualize the sorting algorithms
	text_colour(f_yellow, b_black);
	cout << "Vsort stands for Visualized Sorting, enabling Vsort prints" << endl;
	cout << "out how the algorithms sort the list using a bar graph." << endl;
	cout << "Use with caution. Maximum advised list: 30. Maximum advised values: 100." << endl;
	cout << "Warning: using Vsort with large arrays causes flashing lights which may cause epilepsy" << endl;
	text_colour(f_cyan, b_black);
	cout << "Do you want to enable Vsort? [Y/N] ";
	choice = toupper(_getch());
	system("cls");
	//Validate
	while (choice != 'Y' && choice != 'N')
	{
		text_colour(f_yellow, b_black);
		cout << "Vsort stands for Visualized Sorting, enabling Vsort prints" << endl;
		cout << "out how the algorithms sort the list using a bar graph." << endl;
		cout << "Use with caution. Maximum advised list: 30. Maximum advised values: 100." << endl;
		cout << "Warning: using Vsort with large arrays causes flashing lights which may cause epilepsy" << endl;
		text_colour(f_red, b_black);
		cout << "Invalid choice! ";
		text_colour(f_cyan, b_black);
		cout << "Do you want to enable Vsort ? [Y / N] ";
		choice = toupper(_getch());
		system("cls");
	}//Validate
	if (choice == 'Y')
		Vsort = true;
	else
		Vsort = false;

	//Allow user to choose until they choose quit
	do
	{
		//Print menu and allow user to choose
		system("cls");
		choice = menu(generate, sort, order);
		
		//Call funciton based on user choice
		switch (choice)
		{
		case 'G': generatelist(list, length); text_colour(f_green, b_black); 
			cout << "A list has been generated." << endl; generate = true; sort = false; break;
		case 'P': printlist(list, length); break;
		case 'B': bubble(list, length, order, Vsort); sort = true; break;
		case 'I': insert(list, length, order, Vsort); sort = true; break;
		case 'S': selection(list, length, order, Vsort); sort = true; break;
		case 'L': linear(list, length); break;
		case 'F': binary(list, length, order); break;
		case 'H': shell(list, length, order, Vsort); sort = true; break;
		case 'Q': break; //User quits
		default: text_colour(f_red, b_black); "Error: choice does not exist."; break;
		}//switch (choice)

		//Pause the loop until user chooses to continue
		if (choice != 'Q')
		{
			text_colour(f_gray, b_black);
			cout << "Press any key to continue...";
			_getch();
		}//Pause loop
	} while (choice != 'Q');

	//Reset text colour
	text_colour(f_gray, b_black);
	return 0;
}//main

//seedran - This function seeds the random number generator
void seedran()
{
	int i;                  //Loop counter

	//Seed the random number generator use the timer
	srand((unsigned)time(NULL));
	for (i = 0; i<rand(); i++)
		rand();
}//seedran

//menu - This function prints the menu and allows the user to choose an option
//generate - Whether a list has been generated
//sort - Whether the list has been sorted
//order - Whether the user wants the array to be in ascending or descending order
char menu(bool generate, bool sort, bool &order)
{
	char choice;			//User choice

	//Loop back to main menu if the user chooses to
	do
	{
		//Print options (basic)
		text_colour(f_cyan, b_black);
		cout << "Enter the inicated key to choose." << endl;
		cout << "G - Generate list" << endl;
		if (!generate)
			text_colour(f_gray, b_black);
		cout << "P - Print list" << endl;
		cout << "S - Sort" << endl;
		cout << "F - Search" << endl;
		text_colour(f_cyan, b_black);
		cout << "Q - Quit" << endl;
		//User input
		choice = toupper(_getch());
		system("cls");
		//Validate
		while ((choice != 'G' && choice != 'S' && choice != 'F' && choice != 'Q' && choice != 'P') 
			|| ((choice == 'S' || choice == 'F' || choice == 'P') && !generate))
		{
			//Print response
			text_colour(f_red, b_black);
			if (choice == 'S' || choice == 'F' || choice == 'P')
				cout << "A list must be generated before you can use that function." << endl;
			else
				cout << "Invalid choice." << endl;
			//Print Options
			text_colour(f_cyan, b_black);
			cout << "Enter the inicated key to choose." << endl;
			cout << "G - Generate list" << endl;
			if (!generate)
				text_colour(f_gray, b_black);
			cout << "P - Print list" << endl;
			cout << "S - Sort" << endl;
			cout << "F - Search" << endl;
			text_colour(f_cyan, b_black);
			cout << "Q - Quit" << endl;
			//User input
			choice = toupper(_getch());
			system("cls");
		}//Validate

		//Advanced Menu
		if (choice == 'S')
		{
			//Print options
			cout << "Enter the inicated key to choose." << endl;
			cout << "B - Bubble sort" << endl;
			cout << "I - Insert sort" << endl;
			cout << "S - Selection sort" << endl;
			cout << "H - Shell sort" << endl;
			cout << "Q - Back" << endl;
			//User input
			choice = toupper(_getch());
			system("cls");
			//Validate
			while (choice != 'B' && choice != 'I' && choice != 'S' && choice != 'Q' && choice != 'H')
			{
				//Print response
				text_colour(f_red, b_black);
				cout << "Invalid Option." << endl;
				//Print options
				text_colour(f_cyan, b_black);
				cout << "B - Bubble sort" << endl;
				cout << "I - Insert sort" << endl;
				cout << "S - Selection sort" << endl;
				cout << "H - Shell sort" << endl;
				cout << "Q - Back" << endl;
				//User input
				choice = toupper(_getch());
				system("cls");
			}//Validate
			if (choice == 'Q')
				choice = 'R';
		}//Advanced menu (sort)
		if (choice == 'F')
		{
			//Print options
			cout << "Enter the inicated key to choose." << endl;
			cout << "L - Linear search" << endl;
			if (!sort)
				text_colour(f_gray, b_black);
			cout << "B - Binary search" << endl;
			text_colour(f_cyan, b_black);
			cout << "Q - Back" << endl;
			//User input
			choice = toupper(_getch());
			system("cls");
			//Validate
			while ((choice != 'L' && choice != 'B' && choice != 'Q') || (choice == 'B' && !sort))
			{
				//Print response
				text_colour(f_red, b_black);
				if (choice == 'B')
					cout << "List must be sorted before binary searching." << endl;
				else
					cout << "Invalid Option." << endl;
				//Print options
				text_colour(f_cyan, b_black);
				cout << "L - Linear search" << endl;
				if (!sort)
					text_colour(f_gray, b_black);
				cout << "B - Binary search" << endl;
				text_colour(f_cyan, b_black);
				cout << "Q - Back" << endl;
				//User input
				choice = toupper(_getch());
				system("cls");
			}//Validate
			if (choice == 'Q')
				choice = 'R';
			if (choice == 'B')
				choice = 'F';
		}//Advanced menu (search)
		if (choice == 'B' || choice == 'I' || choice == 'S' || choice == 'D' || choice == 'H')
		{
			//Ask user whether they want the array in ascending or descending order
			cout << "How will the values be sorted?" << endl;
			cout << "A - Ascending order" << endl;
			cout << "D - Descending order" << endl;
			char choice2 = toupper(_getch());
			system("cls");
			//Validate
			while (choice2 != 'A' && choice2 != 'D')
			{
				//Ask user whether they want the array in ascending or descending order
				text_colour(f_red, b_black);
				cout << "Invalid choice." << endl;
				text_colour(f_cyan, b_black);
				cout << "A - Ascending order" << endl;
				cout << "D - Descending order" << endl;
				choice2 = toupper(_getch());
				system("cls");
			}//Validate
			if (choice2 == 'A')
				order = true;
			else
				order = false;
		}//Ask for order
		
		//If the list is already sorted, validate
		if (choice == 'S' && sort)
		{
			text_colour(f_yellow, b_black);
			cout << "The list is already sorted, are you sure you want to sort again? [Y/N] ";
			choice = toupper(_getch());
			system("cls");
			//Validate
			while (choice != 'Y' && choice != 'N')
			{
				text_colour(f_red, b_black);
				cout << "Invalid choice!" << endl;
				text_colour(f_yellow, b_black);
				cout << "The list is already sorted, are you sure you want to sort again? [Y/N] ";
				choice = toupper(_getch());
				system("cls");
			}//Validate
			if (choice == 'Y')
				choice = 'S';
			else
				choice = 'R';
		}//if (the user chooses sort again)
	} while (choice == 'R');
	return choice;
}//menu

//generatelist - This function assigns random numbers to the array
//list - Array containing numbers
//length - How long the user wants the array to be
void generatelist(int list[MAX], int &length)
{
	int cap;		//How large the generated number can be

	//Ask user for length of list
	cout << "How many values will be in the list? [1-" << MAX << "] ";
	text_colour(f_yellow, b_black);
	cin >> length;
	//Validate
	while (length < 1 || length > 100)
	{
		text_colour(f_red, b_black);
		cout << "Invalid number, please choose a number between 1 and " << MAX << " ";
		text_colour(f_yellow, b_black);
		cin >> length;
	}//Validate
	//Ask user for number cap
	text_colour(f_cyan, b_black);
	cout << "How large can the generated values be? [1-99999] ";
	text_colour(f_yellow, b_black);
	cin >> cap;
	//Validate
	while (cap < 1 || cap > 99999)
	{
		text_colour(f_red, b_black);
		cout << "Invalid choice, please choose a number between 1 and 99999. ";
		text_colour(f_yellow, b_black);
		cin >> cap;
	}//Validate
	text_colour(f_cyan, b_black);
	
	//Assign number to list
	for (int i = 0; i < length; i++)
		list[i] = rand() % cap;
}//generatelist

//printlist - This function prints the array
//list - Array containing numbers
//length - How long the user wants the array to be
void printlist(int list[MAX], int length)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; i + j < length; j += 20)
		{
			text_colour(f_cyan, b_black);
			space(i + j, true);
			text_colour(f_magenta, b_black);
			space(list[i + j], false);
			text_colour(f_cyan, b_black);
			cout << "| ";
		}
			cout << endl;
	}//for
	cout << endl;
}//printlist

//space - This function reads in a number, and decides how many spaces
//		  should be put before or after the number
//num - The number used to determine spaces
//index - Whether the number is a index number, determines maximum number of spaces
void space(int num, bool index)
{
	if (index)
	{
		cout << num + 1 << " ";
		if (num < 99)
			cout << " ";
		if (num < 9)
			cout << " ";
	}//if (index)
	else
	{
		if (num < 10000)
			cout << " ";
		if (num < 1000)
			cout << " ";
		if (num < 100)
			cout << " ";
		if (num < 10)
			cout << " ";
		cout << num << " ";
	}//else		
}//space 

/*-------------------------------------------Algorithms-----------------------------------------------*/

//swap - This function switches the values of two numbers
//num1, num2 - Numbers that are to be switched
void swap(int &num1, int &num2)
{
	int placehold;		//Place holder
	
	placehold = num1;
	num1 = num2;
	num2 = placehold;
}//swap

//SRprint - This function prints the search results
//num - The number the user was trying to find
//pos - The position of the number
//compares - Number of compares done
//found - Whether or not the number was found
void SRprint(int num, int pos, int compares, bool found)
{
	if (found)
	{
		text_colour(f_magenta, b_black);
		cout << num;
		text_colour(f_green, b_black);
		cout << " is the ";
		text_colour(f_magenta, b_black);
		cout << pos;
		text_colour(f_green, b_black);
		switch (pos)
		{
		case 1: cout << "st "; break;
		case 2: cout << "nd "; break;
		case 3: cout << "rd "; break;
		default: cout << "th "; break;
		}//switch
		cout << "number in the array." << endl;
		cout << "The number was found in ";
		text_colour(f_magenta, b_black);
		cout << compares;
		text_colour(f_green, b_black);
		cout << " compares." << endl;
	}//if (number was found)
	else
	{
		cout << "The number ";
		text_colour(f_magenta, b_black);
		cout << num;
		text_colour(f_green, b_black);
		cout << " is not in the array." << endl;
		cout << "This was concluded after ";
		text_colour(f_magenta, b_black);
		cout << compares;
		text_colour(f_green, b_black);
		cout << " compares." << endl;
	}//else (number was not found)
}//SRprint

//Vprint - This function prints a visualization of sorting algorithms
//list - Array containing numbers
//length - How long the user wants the array to be
//num, num2 - Current postition in loop
//pos, pos2 - How far on the list is sorted
//type - What type of sorting it is
void Vprint(int list[MAX], int length, int num, int pos, int type, int num2, int pos2)
{
	system("cls");
	for (int i = 0; i < length; i++)
	{
		//Determine colour
		text_colour(f_white, b_black);
		switch (type)
		{
		case 1:if (i >= pos)
			text_colour(f_green, b_black);
			break;
		case 2: if (i <= pos)
			text_colour(f_green, b_black);
			break;
		case 3: if (i >= pos || i < pos2)
			text_colour(f_green, b_black);
			break;
		}//switch (type)
		if (i == num || i == num2)
			text_colour(f_red, b_black);

		space(i, true);
		for (int j = 1; (j <= list[i] && j <= 100); j++)
			cout << char(219);
		cout << " " << list[i];
		cout << endl;
	}//for
	Sleep(10);
}//Vprint

//bubble - This function sorts an array using the bubble sort algorithm
//list - Array containing numbers
//length - How long the user wants the array to be
//order - Whether the user wants the array to be in ascending or descending order
//Vsort - Whether or not Vprint will be used
void bubble(int list[MAX], int length, bool order, bool Vsort)
{
	bool check = false;			//Whether or not the array is sorted
	int i, r;					//Loop counter

	//Loop until sorted
	for (r = length; (r >= 0 && !check); r--)
	{
		check = true;
		//Loop through the array
		for (i = 1; i < r; i++)
		{
			if (Vsort)
				Vprint(list, length, i - 1, r, 1, -1, -1);
			if ((list[i] < list[i - 1] && order) || (list[i] > list[i - 1] && !order))
			{
				swap(list[i], list[i - 1]);
				check = false;
			}//if (switch values)
		}//for
	}//for (not sorted)
	if (Vsort)
		Vprint(list, length, -1, -1, 1, -1, -1);

	//Print list
	text_colour(f_green, b_black);
	cout << "The list has been sorted." << endl;
	if (!Vsort)
		printlist(list, length);
}//bubble

//insert - This function sorts an array using the insertion sort algorithm
//list - Array containing numbers
//length - How long the user wants the array to be
//order - Whether the user wants the array to be in ascending or descending order
//Vsort - Whether or not Vprint will be used
void insert(int list[MAX], int length, bool order, bool Vsort)
{
	int i;			//Loop counter
	int p;			//Position counter

	//Loop through the array
	for (p = 1; p < length; p++)
	{
		i = p;
		while (((list[i] < list[i - 1] && order) || (list[i] > list[i - 1] && !order)) && i > 0)
		{
			if (Vsort)
				Vprint(list, length, i, p, 2, -1, -1);
			swap(list[i], list[i - 1]);
			i--;
		}//while			
	}//for
	if (Vsort)
		Vprint(list, length, -1, 102, 2, -1, -1);

	//Print list
	text_colour(f_green, b_black);
	cout << "The list has been sorted." << endl;
	if (!Vsort)
		printlist(list, length);
}//insert

//selection - This function sorts an array using the selection sort algorithm
//list - Array containing numbers
//length - How long the user wants the array to be
//order - Whether the user wants the array to be in ascending or descending order
//Vsort - Whether or not Vprint will be used
void selection(int list[MAX], int length, bool order, bool Vsort)
{
	int i;			//Loop counter
	int p;			//Position counter
	int hold;		//Position placeholder

	//Loop through the array
	for (p = 0; p < length - 1; p++)
	{
		hold = p;
		//Loop through unsorted part of array
		for (i = p + 1; i < length; i++)
		{
			if (Vsort)
				Vprint(list, length, i, p - 1, 2, -1, -1);
			if ((list[i] < list[hold] && order) || (list[i] > list[hold] && !order))
				hold = i;
		}//for
		if (hold != p)
			swap(list[p], list[hold]);
	}//for
	if (Vsort)
		Vprint(list, length, -1, 102, 2, -1, -1);

	//Print list
	text_colour(f_green, b_black);
	cout << "The list has been sorted." << endl;
	if (!Vsort)
		printlist(list, length);
}//selection

//linear - This function searches for a value through an array using linear search
//list - Array containing numbers
//length - How long the user wants the array to be
void linear(int list[MAX], int length)
{
	int wanted;					//The number that the user wants to find
	int position = -1;			//Position of the number in the array
	int compares = 0;			//Howmany compares it took to find the number
	bool found = false;			//Whether or not the number has been found

	//Ask user what number they want to find
	text_colour(f_green, b_black);
	cout << "What number are you trying to find? ";
	text_colour(f_yellow, b_black);
	cin >> wanted;
	
	//Loop through the array to see if the number is in it
	for (int i = 0; (i < length && !found); i++)
	{
		if (list[i] == wanted)
		{
			found = true;
			position = i + 1;
		}//if (found)
		compares++;
	}//for

	//Print results
	SRprint(wanted, position, compares, found);
}//linear

//binary - This function searches for a value through an array using binary search
//list - Array containing numbers
//length - How long the user wants the array to be
void binary(int list[MAX], int length, bool order)
{
	int wanted;					//The number that the user wants to find
	int position = -1;			//Position of the number in the array
	int compares = 0;			//Howmany compares it took to find the number
	bool found = false;			//Whether or not the number has been found
	int bottom = 0, top = length - 1, middle;	//Position holders in the array

	//Ask user what number they want to find
	text_colour(f_green, b_black);
	cout << "What number are you trying to find? ";
	text_colour(f_yellow, b_black);
	cin >> wanted;

	//Loop through the array to see if the number is in it
	while (!found && bottom <= top)
	{
		//Find middle
		middle = (bottom + top) / 2;
		if (list[middle] == wanted)
		{
			found = true;
			position = middle + 1;
		}//if (wanted is middle)
		else
			if ((wanted < middle && order) || (wanted > middle && !order))
				top = middle - 1;
			else
				bottom = middle + 1;
		compares++;
	}//While 

	//Print results
	SRprint(wanted, position, compares, found);
}//binary

//shell - This function sorts the list using shell sort
//list - Array containing numbers
//length - How long the user wants the array to be
//order - Whether the user wants the array to be in ascending or descending order
//Vsort - Whether or not Vprint will be used
void shell(int list[MAX], int length, bool order, bool Vsort)
{
	int gap = length / 2;			//Gap between items compared
	int hold;						//Holds value temporarily
	int Cup, Cins;					//Loop counter

	//Loop until sorted
	while (gap > 0)
	{
		for (Cup = gap; Cup < length; Cup++)
		{
			hold = list[Cup];
			for (Cins = Cup; (Cins >= gap && ((list[Cins - gap] > hold && order) || (list[Cins - gap] < hold && !order))); Cins -= gap)
			{
				if (Vsort)
					if (gap != 1)
						Vprint(list, length, Cins, -1, 2, Cins - gap, -1);
					else
						Vprint(list, length, Cins, Cup, 2, Cins - gap, -1);
				swap(list[Cins], list[Cins - gap]);
			}//while
			list[Cins] = hold;
		}//for
		gap /= 2;
	}//while
	if (Vsort)
		Vprint(list, length, -1, 102, 2, -1, -1);

	//Print list
	text_colour(f_green, b_black);
	cout << "The list has been sorted." << endl;
	if (!Vsort)
		printlist(list, length);
}//shell