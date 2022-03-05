#include<iostream>
#include<time.h>

/*�	���� ������� � ����������;
  �	���� ������� � ���������� �� �����;
  �	����������� ������� ���������� ������� �� ���������� ���������;
  �	����������� ������� �� �������� ������� �������� ��������;
  �	����� ������� �� �����;
  �	����� ������� � ��������� ����;
  �	����� ������� � �������� ����.
  19.��������� ����� ����������� � ����������� ��������� �������*/

const int MAX = 50;

void scanArraySize(int& rows, int& cols)
{
	printf("������� ������ ���������� �������:\n");
	printf("���-�� �����: "); scanf_s("%d", &rows);
	printf("���-�� ��������: "); scanf_s("%d", &cols);
}

void fillArrayByKeyboard(int arr[][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			printf("[%d][%d] = ", i + 1, j + 1);
			scanf_s("%d", &arr[i][j]);
		}
}

void fillArrayByTXTFile(int arr[][MAX], int& rows, int& cols, const char* filename)
{
	FILE* file;

	if (fopen_s(&file, filename, "rt") != 0)
	{
		printf("File %s doesn't  exist", filename);
		exit(1);
	}

	fscanf_s(file, "%d", &rows);
	fscanf_s(file, "%d", &cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			fscanf_s(file, "%d", &arr[i][j]);

	fclose(file);
}

void fillArrayByBINFile(int arr[][MAX], int& rows, int& cols, const char* filename)
{
	FILE* file;

	if (fopen_s(&file, filename, "rb") != 0)
	{
		printf("File %s doesn't  exist", filename);
		exit(1);
	}

	fread(&rows, sizeof(int), 1, file);
	fread(&cols, sizeof(int), 1, file);
	
	for (int i = 0; i < rows; i++)
		fread(arr[i], sizeof(int), cols, file);

	fclose(file);
}

void fillArrayByRandomNumbers(int arr[][MAX], int rows, int cols)
{
	srand(time(0));

	int A, B;

	printf("������� ������� [A, B]:\n");
	printf("A = "); scanf_s("%d", &A);
	
	do
	{
		printf("B = "); scanf_s("%d", &B);

		if (A >= B)
			printf("����� ������������ ��������");
	} while (A >= B);

	int n = B - A + 1;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				arr[i][j] = rand() % n + A;
}

void fillArrayByFormula(int arr[][MAX], int rows, int cols)
{
	for (int i = 1; i <= rows; i++)
		for (int j = 1; j <= cols; j++)
		{
			if (i <= j)
				arr[i - 1][j - 1] = 1 / (i * i * i + 2 * j);
			else
				arr[i - 1][j - 1] = 2 * i / (i + j);
		}
}

void printArrayOnScreen(int arr[][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("|%3d", arr[i][j]);
		printf("|\n");
	}
}

void printArrayInTXTFile(int arr[][MAX], int rows, int cols, const char* filename)
{
	FILE* file;

	if (fopen_s(&file, filename, "wt") != 0)
	{
		printf("File %s doesn't  exist", filename);
		exit(1);
	}

	fprintf(file, "���-�� c�����: %d\n", rows);
	fprintf(file, "���-�� ��������: %d\n", cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fprintf(file, "|%3d", arr[i][j]);
		fprintf(file, "|\n");
	}

	fclose(file);
}

void printArrayInBINFile(int arr[][MAX], int rows, int cols, const char* filename)
{
	FILE* file;

	if (fopen_s(&file, filename, "wb") != 0)
	{
		printf("File %s doesn't  exist", filename);
		exit(1);
	}

	fwrite(&rows, sizeof(int), 1, file);
	fwrite(&cols, sizeof(int), 1, file);

	for (int i = 0; i < rows; i++)
		fwrite(arr[i], sizeof(int), cols, file);

	fclose(file);
}

int findMaxElement(int arr[][MAX], int rows, int cols)
{
	int max = arr[0][0];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (max < arr[i][j]) max = arr[i][j];

	printf("Max: %d\n", max);

	return max;
}

int findMinElement(int arr[][MAX], int rows, int cols)
{
	int min = arr[0][0];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (min > arr[i][j]) min = arr[i][j];

	printf("Min: %d\n", min);

	return min;
}

int main()
{
	system("chcp 1251");
	system("cls");

	int massive[MAX][MAX];
	int way, rows, cols;
	
	printf("�������� ������ ���������� �������:\n");
	printf("1 - � ����������\n");
	printf("2 - �� ���������� �����\n");
	printf("3 - �� ��������� �����\n");
	printf("4 - ���������� ������� �� ��������� [A,B]\n");
	printf("5 - �� �������� �����\n");
	
	do
	{
		scanf_s("%d", &way);

		if (way < 1 || way > 5)
			printf("������� ������������ �����");
	} while (way < 1 || way > 5);

	switch (way)
	{
	case 1:
		scanArraySize(rows, cols);
		fillArrayByKeyboard(massive, rows, cols);

		break;
	case 2:
		fillArrayByTXTFile(massive, rows, cols, "1.txt");

		break;
	case 3:
		fillArrayByBINFile(massive, rows, cols, "2.bin");

		break;
	case 4:
		scanArraySize(rows, cols);
		fillArrayByRandomNumbers(massive, rows, cols);

		break;
	case 5:
		scanArraySize(rows, cols);
		fillArrayByFormula(massive, rows, cols);

		break;
	}

	printf("�������� ������ ������ �������:\n");
	printf("1 - �� �����\n");
	printf("2 - � ��������� ����\n");
	printf("3 - � �������� ����\n");
	
	do
	{
		scanf_s("%d", &way);

		if (way < 1 || way > 3)
			printf("������� ������������ �����");
	} while (way < 1 || way > 3);
	
	switch (way)
	{
	case 1:
		printArrayOnScreen(massive, rows, cols);

		break;
	case 2:
		printArrayInTXTFile(massive, rows, cols, "3.txt");

		break;
	case 3:
		printArrayInBINFile(massive, rows, cols, "4.bin");

		break;
	}

	printf("����� ������������ � ������������ ��������� �������: %d\n", findMaxElement(massive, rows, cols) + findMinElement(massive, rows, cols));

	return 0;
}