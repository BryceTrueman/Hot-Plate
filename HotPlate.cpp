#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const int row = 20;
const int col = 20;
const int times_to_go = 20;
const int Change = 1;
const double Threshold = .10;

void Initialize_Plate(double table[row][col])
{
	for (int row = 0; row < times_to_go; row++)
	{
		for (int col = 0; col < times_to_go; col++)
		{
			table[row][col] = 0;
			if (row == 0 || row == 19)
			{
				table[row][col] = 100;
				table[row][col] = 100;
			}
			if (col == 0 || col == 19)
			{
				table[row][col] = 0;
				table[row][col] = 0;
			}
		}
	}
}


void Print_Plate(double table[row][col])
{
	for (int row = 0; row < times_to_go; row++)
	{
		for (int col = 0; col < times_to_go; col++)
		{
			cout << fixed << setprecision(2) << table[row][col] << "," << "\t";
		}
		cout << endl;
	}
}

void Average_Plate(double table[row][col])
{
	double top_value = 0;
	double right_value = 0;
	double bottom_value = 0;
	double left_value = 0;
	double average_value = 0;
	for (int row = 1; row < (times_to_go - Change); row++)
	{
		for (int col = 1; col < (times_to_go - Change); col++)
		{
			top_value = table[row - Change][col];
			right_value = table[row][col + Change];
			bottom_value = table[row + Change][col];
			left_value = table[row][col - Change];
			average_value = ((top_value + right_value + bottom_value + left_value) / 4);
			table[row][col] = average_value;
		}
	}
}

void Final_Hot_Plate(double table[row][col])
{
	double top_value = 0;
	double right_value = 0;
	double bottom_value = 0;
	double left_value = 0;
	double new_average_value = 0;
	double old_average = 0;
	double greatest_difference = 0;
	do
	{
		greatest_difference = 0;
		for (int row = 1; row < (times_to_go - Change); row++)
		{
			for (int col = 1; col < (times_to_go - Change); col++)
			{
				old_average = table[row][col];
				top_value = table[row - Change][col];
				right_value = table[row][col + Change];
				bottom_value = table[row + Change][col];
				left_value = table[row][col - Change];
				new_average_value = ((top_value + right_value + bottom_value + left_value) / 4);
				table[row][col] = new_average_value;

				if (abs(old_average - new_average_value) > greatest_difference)
				{
					greatest_difference = (abs(old_average - new_average_value));
				}

			}
		}

	} while (greatest_difference > Threshold);
}


void Export_Plate(double table[row][col])
{
	ofstream HotPlateExport;
	HotPlateExport.open("Final.csv");
	for (int row = 0; row < times_to_go; row++)
	{
		for (int col = 0; col < times_to_go; col++)
		{
			HotPlateExport << table[row][col] << ",";
		}
		HotPlateExport << endl;
	}
	HotPlateExport.close();
}

int main()
{
	cout << "Initialized Hot Plate" << endl;
	cout << endl;
	double table[row][col];
	Initialize_Plate(table);
	Print_Plate(table);
	cout << endl; cout << endl; cout << endl;

	cout << "Updated Elements Once" << endl;
	cout << endl;
	Average_Plate(table);
	Print_Plate(table);
	cout << endl; cout << endl; cout << endl;

	cout << "Stabilized Hot Plate" << endl;
	cout << endl;
	Final_Hot_Plate(table);
	Print_Plate(table);

	Export_Plate(table);


	system("pause");
	return 0;
}
