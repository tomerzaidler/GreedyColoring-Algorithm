/*
* *Greedy Coloring - HW2 *
* Name: Tomer Zaidler
* ID : 312468549
* Group Number: 61309-6
* Lecturer : Dr. Ahuva Meualem
* Lecturer Practitioner: Dr. Yulia Kempner
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct Interval 
{
	int start, end;
	int colorID;
	int degree;
} vertex;

void GreedyColoring(); // main function that calls out all the other functions and prints all the requested data
int inRange(vertex a, vertex b); // check if both vertex are neighbors
void printVertex(vertex *arr, int k); // print all vertex from the graph
void setDegreeANDcolorID(vertex *arr, int k);
int getMaxDegree(vertex *arr, int k);// get the maximum degree of one of the vertex in the graph
int getMinDegree(vertex *arr, int k); // get the minimum degree of one of the vertex in the graph
int getGEdges(vertex *arr, int k); // get number of Edges
int getChromaticNum(vertex *arr, const int k); // return the chromatic number of the graph
void sort(vertex* arr, int k); // sort the array of vertex by the start point of each Interval
void printByColorID(vertex *arr, int k); // print each group of colorID Interval

void main() {
	GreedyColoring();
	system("pause");
}

void GreedyColoring() // main function that calls out all the other functions and prints all the requested data
{
	int k, i;
	vertex *arr;
	printf("Please input k\n");
	scanf("%d", &k); // getting the interval's family size into K
	// Dynamic memory allocate
	arr = (vertex*)malloc(k * sizeof(vertex));
	// Getting all vertex's (interval) data
	for (i = 0; i < k; i++) {
		printf("Interval %d: ", i + 1);
		scanf("%d%d", &arr[i].start, &arr[i].end);
		arr[i].degree = 0;
		arr[i].colorID = 0;
	}
	printVertex(arr, k);
	sort(arr, k);
	setDegreeANDcolorID(arr, k);
	printVertex(arr, k);
	printf("G Edges = %d\n", getGEdges(arr, k));
	printf("Maximum Degree of G = %d\n", getMaxDegree(arr, k));
	printf("Minimum Degree of G = %d\n", getMinDegree(arr, k));
	printf("Chromatic Number of G = %d\n", getChromaticNum(arr,k));
	printf("G's Complement Edges = %d\n", ((k*(k - 1)) / 2) - (getGEdges(arr, k)));
	printf("Maximum degree of G's Complement = %d\n", k - getMinDegree(arr, k) - 1);
	printf("Minimum degree of G's Complement = %d\n", k - getMaxDegree(arr, k) - 1);
	printByColorID(arr, k);
}

int inRange(vertex a, vertex b) // check if both vertex are neighbors, return true(1) or false(0)
{
	if (!((a.end < b.start) || (a.start > b.end)))
	{
		return 1;
	}
	return 0;
}

void printVertex(vertex *arr, int k)
{
	int i;
	for (i = 0; i < k; i++)
	{
		printf("[%d,%d]", arr[i].start, arr[i].end);
		if (i != k - 1)
			printf(",");
	}
	printf("\n");
} 
void setDegreeANDcolorID(vertex *arr, int k) // set the degree of the each vertex;
{
	int i, j, c, p;
	for (c = 0; c < k; c++)
	{
		arr[c].colorID = 1; // set the starting colorID of each vertex to 1
	}
	for (i = 0; i < k; i++)
	{
		for (j = i + 1; j < k; j++)
		{
			if (inRange(arr[i], arr[j])) // check if both vertex are neighbors
			{
				arr[i].degree++; // set degree +1 for this vertex
				arr[j].degree++; // set defree +1 for this vertex neighbor
				if (arr[i].colorID == arr[j].colorID) // check if they have they same colorID, then add 1 to the neigbor colorID
				{
					arr[j].colorID++;
				}
			}
		}
		// checking again all the vertex we have been moved through,
		// to see if we have equal colorID for this vertex and one of his neighbors that we check before
		if (i > 0) 
		{
			p = i-1; // set the index to check backwards
			while (p != 0) // when p reaches 0 we know that we check all the previuos vertex
				{
					if (inRange(arr[p],arr[i])) // check if both are neighbors
						{
							if (arr[i].colorID == arr[p].colorID) // check if they have the same color - change it
								{
									arr[i].colorID++; // add 1 to this vertex colorID
								}
						}
					p--;
				}
		}
	}// vertex for loop
} // setDegree

int getMaxDegree(vertex *arr, int k) // get the maximum degree of one of the vertex in the graph
{
	int i, max = 0;
	for (i = 0; i < k; i++)
	{
		if (arr[i].degree > max)
			max = arr[i].degree;
	}
	return max;
}
int getMinDegree(vertex *arr, int k) // get the minimum degree of one of the vertex in the graph
{
	int i, min = arr[0].degree;
	for (i = 1; i < k; i++)
	{
		if (arr[i].degree < min)
			min = arr[i].degree;
	}
	return min;
}
int getGEdges(vertex *arr, int k) // get number of Edges
{
	int i, sumofdegrees = 0;
	for (i = 0; i < k; i++)
	{
		sumofdegrees += arr[i].degree;
	}
	return (sumofdegrees / 2); 
}
int getChromaticNum(vertex *arr, const int k)
{
	int i, max = 0;
	for (i = 0; i < k; i++)
	{
		if (max < arr[i].colorID)
		{
			max = arr[i].colorID;
		}
			
	}
	return max;
}
void sort(vertex* arr, int k) // sort the array of vertex by the start point of each Interval
{
	int j, i;
	for (i = 1; i < k; i++)
	{
		for (j = 0; j < k - i; j++)
		{
			if (arr[j].start > arr[j + 1].start)
			{
				vertex temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void printByColorID(vertex *arr, int k) // print each group of colorID Interval
{
	int i, j;
	bool flag = false;
	printf("Optional Coloring: ");
	for (j = 1; j <= getChromaticNum(arr, k); j++)
		{
			printf("{");
			for (i = 0; i < k; i++) // vertex for loop
			{
				if (arr[i].colorID == j)
				{
					if (flag)
						printf(",");
					printf("[%d,%d]",arr[i].start,arr[i].end);
					flag = true;
				}
			}
			printf("} = %d, ",j);
			flag = false;
		}
	printf("\n");
}
