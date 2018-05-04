#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

void readFile(char *fn, char* *data);
void print(int* *dataInfo, int* numLists);
int** sort(char* *data, int* *outputList);

int main(int argc, char *argv[])
{
	int **txt;
	char* fn = argv[1];
	FILE *fp;
	fp = fopen(fn, "r");
	int numTotal;

	if (fp != NULL)
	{
		fscanf(fp, "%d", &numTotal);
		txt = (int**)malloc(numTotal * sizeof(int*));

		for (int i = 0; i < numTotal; i++)
		{
			char line[128];
			if (i == 0)
			{
				fgets(line, sizeof line, fp);
			}
			else
			{
				fgets(line, sizeof line, fp);
				int len = 0;
				char remainderLine[128];
				char sep = ':';
				sscanf(line, "%d%c%[^\t\n]", &len, &sep, &remainderLine);


				char number[10];

				txt[i] = (int*)malloc(len * sizeof(int));
				for (int j = 0; j < len; j++)
				{
					char sep = ',';
					sscanf(remainderLine, "%s%c%[^\t\n]", &number, &sep, &remainderLine);
					txt[i][j] = atoi(number);
				}
			}
		}
		fclose(fp);
	}

	char **info = (char**)calloc(64, sizeof(char*));
	for (int i = 0; i < 64; i++)
	{
		info[i] = (char*)calloc(256, sizeof(char));
	}
	int* numLists = NULL;
	readFile(fn, info);

	int* *dataInfo = sort(info, &numLists);

	print(dataInfo, numLists);

	getchar();
	return 0;
}

void readFile(char *fn, char* *data) 
{
	FILE* fp = fopen(fn, "r");

	if (fp != NULL) {
		for (char* *i = data; fgets((*i), 256, fp) != NULL; i++) 
		{			
		}
		fclose(fp);
	}
}

void print(int* *dataInfo, int* numLists)
{
	printf("%d Lists:\n", (*numLists));
	for (int i = 0; i < (*numLists); i++)
	{
		for (int j = 1; j <= dataInfo[i][0]; j++)
		{
			if (j < dataInfo[i][0])
			{
				printf("%d, ", dataInfo[i][j]);
			}
			else
			{
				printf("%d", dataInfo[i][j]);
			}
		}
		printf("\n");
	}
}

int** sort(char* *data, int* *outputList)
{
	int* numLists = malloc(sizeof(int));
	(*numLists) = atoi((*data));
	(*outputList) = numLists;

	int maxSize = max(max(((*((*data) + 304)) - '0'), ((*((*data) + 608)) - '0')),
		max(((*((*data) + 608)) - '0'), ((*((*data) + 912)) - '0')));

	int* *dataInfo = (int**)calloc((*numLists), sizeof(int*));
	for (int i = 0; i < (*numLists); i++)
	{
		dataInfo[i] = (int*)calloc(maxSize + 1, sizeof(int));
	}

	for (int i = 1; i <= (*numLists); i++) 
	{
		char *val = strtok((*data) + (304 * i), ";, :");
		for (int j = 0; val != NULL; j++) 
		{
			dataInfo[i - 1][j] = atoi(val);
			val = strtok(NULL, ";, :");
		}
	}

	for (int i = 0; i < (*numLists) - 1; i++)
	{
		for (int j = 0; j < (*numLists) - 1; j++) 
		{
			if (dataInfo[j][0] > dataInfo[j + 1][0]) 
			{
				int *temp = (int*)calloc(maxSize + 1, sizeof(int));
				temp = dataInfo[j];
				dataInfo[j] = dataInfo[j + 1];
				dataInfo[j + 1] = temp;
			}
		}
	}

	int count = 0;

	for (int i = 0; i < (*numLists); i++) 
	{
		for (int j = 1; j < dataInfo[i][0]; j++) 
		{
			for (int k = 1; k < dataInfo[i][0]; k++) 
			{
				if (dataInfo[i][k] > dataInfo[i][k + 1]) 
				{
					int temp = dataInfo[i][k];
					dataInfo[i][k] = dataInfo[i][k + 1];
					dataInfo[i][k + 1] = temp;
				}
			}
		}
	}
	return dataInfo;
}










	
	


