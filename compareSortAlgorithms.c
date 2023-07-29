#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void Merge(int * myArray, int left, int middle, int right){
    int lArraySize = ((middle-left)+1);
    int rArraySize = (right-middle);
    int *lTempArray = (int *) malloc(sizeof(int)*lArraySize);
    int *rTempArray = (int *) malloc(sizeof(int)*rArraySize);
	extraMemoryAllocated += sizeof(int)*(lArraySize + rArraySize);

    for(int i = 0; i < lArraySize; i++){
        lTempArray[i] = myArray[i+left]; 
    }

    for(int i = 0; i < rArraySize; i++){
        rTempArray[i] = myArray[i+middle+1]; 
    }

    int counterL = 0;
    int counterR = 0;

    while(counterL < lArraySize && counterR < rArraySize){
        if(lTempArray[counterL] < rTempArray[counterR]){
            myArray[left] = lTempArray[counterL];
            left ++;
            counterL ++;
        }
        else{
            myArray[left] = rTempArray[counterR];
            left ++;
            counterR ++;
        }
    }

    while(counterL < lArraySize){
        myArray[left] = lTempArray[counterL];
        left ++;
        counterL ++;
    }

    while(counterR < rArraySize){
        myArray[left] = rTempArray[counterR];
        left ++;
        counterR ++;
    }

    free(rTempArray);
    free(lTempArray);

}

void mergeSort(int pData[], int l, int r)
{
	if(l < r){
        int m = (l + r)/2;
        mergeSort(pData, l, m);
        mergeSort(pData, m+1, r);
        Merge(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
int swap(int *firstIndex, int *secondIndex){
    int temp = *firstIndex;
    *firstIndex = *secondIndex;
    *secondIndex = temp; 
}

void insertionSort(int* pData, int n)
{

    for(int i = 1; i < n; i++){
        if(pData[i] < pData[i-1]){
            for(int j = i; j > 0; j--){
                if(pData[j-1] > pData[j]){
                    swap(&pData[j], &pData[j-1]);
                }
                else break;
            }
        }
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for(int i = 0; i < n; i++){
		for(int j = 1; j < n-i; j++){
			if(pData[j] < pData[j-1]) swap(&pData[j], &pData[j-1]);
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for(int i = 0; i < n; i++){
		int lowest = i;
		for(int j = i+1; j < n; j++){
			if(pData[lowest] > pData[j]) lowest = j;
		}
		swap(&pData[i], &pData[lowest]);
	}	
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		int * ppDataTemp = *ppData;
		// int counter = 0;
		for(int i = 0; i < dataSz; i++){
			int temp = 0;
			fscanf(inFile, "%i", &temp);
			*ppDataTemp = temp;
			ppDataTemp ++;
			// counter++;
			// printf("executed %i\n", counter);
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}