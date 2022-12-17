#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iso646.h>
int main() {
	srand(time(NULL));
	char mx[3][3];
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printf("[");
			mx[i][j] = '\0';
			printf("]");
		}
		printf("\n");
	}

	int n = 5;
	int m = 0;
	int p1, p2, p3, p4;
	while (n > 0) {
		scanf("%d %d", &p1, &p2);
		mx[p1][p2] = 'x';
	
		if (n > 1) {
			while (m == 0) {
				p3 = rand() % 3;
				p4 = rand() % 3;
				if (mx[p3][p4] != 'x' && mx[p3][p4] != 'o')  {
					mx[p3][p4] = 'o';
					m = 1;
				}
			}
			m = 0;
		}

		char el[2] = {'x', 'o'};
		for (int i = 0; i < 2; i++) {
			if ((mx[0][0] == el[i] && mx[0][1] == el[i] && mx[0][2] == el[i]) or (mx[0][0] == el[i] && 
				mx[1][1] == el[i] && mx[2][2] == el[i]) or (mx[0][0] == el[i] && 
				mx[1][0] == el[i] && mx[2][0] == el[i]) or (mx[2][0] == el[i] && 
				mx[2][1] == el[i] && mx[2][2] == el[i]) or (mx[0][2] == el[i] && 
				mx[1][2] == el[i] && mx[2][2] == el[i]) or (mx[0][2] == el[i] && 
				mx[1][1] == el[i] && mx[2][0] == el[i]) or (mx[0][1] == el[i] &&
				mx[1][1] == el[i] && mx[2][1] == el[i]) or (mx[1][0] == el[i] &&
				mx[1][1] == el[i] && mx[1][2] == el[i])) {
				if (el[i] == 'x') {
					printf("You win!\n");
					exit(0);
				}
				if (el[i] == 'o') {
					for (int j = 0; j < 3; j++) {
						for (int m = 0; m < 3; m++) {
							printf("[%c]", mx[j][m]);
						}
						printf("\n");
					}
					printf("Putty win:(\n");
					exit(0);
				}
				if ((n == 1 and el[i] != 'x' and el[i] != 'o')) {
					printf("We have a draw\n");
					exit(0);
				}
			}
		}

		for (int i = 0 ; i < 3; i++) {
			for ( int j = 0; j < 3; j++) {
				printf("[%c]", mx[i][j]);
			}
			printf("\n");
		}
		n-=1;
	}
	printf("We have a draw\n");
	return 0;
}	
