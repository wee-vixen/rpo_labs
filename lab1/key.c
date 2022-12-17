#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(x, y) (x > y) ? x : y

int main() {
    srand(time(NULL));    
	const int n = 100; /*array dimension*/

    int start, end;
    printf("Enter a range of numbers: ");
    scanf("%d %d", &start, &end);
    printf("Your range - [%d,%d]\n", start, end);
    int array[n];
    for (int i = 0; i < 10; i++) {
		for (int j = i * 10; j < i * 10 + 10; j++, putchar('\t')) {
			array[j] = rand() % (end - start + 1) + start;
			printf("%d", array[j]); 
    	}
		printf("\n");
	}

    for(int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
	    	if (array[j] > array[j + 1]) {
				int value = array[j];
				array[j] = array[j + 1];
				array[j + 1] = value; 
	    	}
		}
    }

    printf("\nThe sorted array is ready\n");
	for (int i = 0; i < 10; i++) {
		for (int j = i * 10; j < i * 10 + 10; j++, putchar('\t')) {
			printf("%d", array[j]);
		}
		printf("\n");
    }

    printf("\nNow we turn to the tasks->\n"); 
    
    printf("Max number is %d\n", array[n - 1]);
    printf("Minimal value is %d\n", array[0]);
    printf("Gap between max_array and min_array is %d\n", array[n - 1] - array[0]);

    float sum_array;
    for (int i = 0; i < n; i++) {
		sum_array += array[i]; 
    }
	float midpoint = (sum_array / n);    
	printf("Arithmetic mean is %.2f\n", midpoint);
	 
    float median;
	if (n % 2 == 0) {
		median = ((float)array[(n / 2) - 1] + array[n / 2]) / 2;
    }
	if (n % 2 != 0) {
		median = array[(n / 2)];
	}	
    printf("Median of the array is %.2f\n", median);	    
 
    int count = 1;
    int ms[n];
	for (int i = 0; i < n; i++) {
		ms[i] = 0;
	}
     /*I created an additional array to record \
    the number of repetitions of the sorted array*/
    int mass[n];
	for (int i = 0; i < n; i++) {
		 mass[i] = 0;
	}
    /*This array is needed to find \
     all non-repeating numbers*/
    for (int i = 0; i < n; i++) {
		if (array[i] != array[i + 1]) {
	    	mass[i] = array[i];
		}
		if (array[i] == array[i + 1]) {
	    	mass[i + 1] = 0; 
		} 
    }
    /*
 	for (int i = 0; i < n; i++) {
		printf("%d\t", mass[i]);
    }
    printf("\n"); */
    for (int i = 0; i < n; i++) {
		if (mass[i] == 0) {
	    	count += 1; 
		}
		else {
	    	ms[i] = count;
	    	count = 1;
		} 
    }
    /*for (int i = 0; i < n; i++) {
		printf("%d\t", ms[i]);  
    }
    printf("\n");*/

    /*printf("How many times does the certain number occus in the array?\n");
    for (int i = 0; i < n; i++) {
		if (ms[i] != 0) {
	   		printf("Number %d - %d times\n", mass[i], ms[i]); 
		} 
    }
    printf("\n"); */

    int mx = 0;
    for (int i = 0; i < n; i++) {
		mx = MAX(mx, ms[i]); 
    }	
    if (mx == 1) {
		printf("The array consists of different numbers\n");
    }
    if (mx == n) {
		printf("The array consists of same numbers\n");
    }
    if ((mx != 1) && (mx != n)){
	 	printf("These are the most common elements:\n");
		for (int i = 0; i < n; i++) {    
			if (ms[i] == mx) {
		    	printf("Number %d occurs in the array %d times\n", mass[i], ms[i]);
			}  
    	}
	} 
	return 0; 
}   
