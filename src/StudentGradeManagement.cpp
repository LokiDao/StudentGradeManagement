/*
 ============================================================================
 Name        : Student Management.c
 Author      : DAO VINH LOC
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stuIds[50][10];
float grades[50];
int cnt = 0;

void back(){
	printf("\nPress any key to back to the Menu!");
	fflush(stdout);
	getchar();
	fflush(stdin);
}

char next() {
	char cont;

	printf("\nDo you want to continue? (Y/N)");
	fflush(stdout);
	scanf("%c", &cont);
	fflush(stdin);

	return cont;
}

int findByStudentId(char id[10]) {
	for (int i = 0; i < cnt; i++) {
		if (strcmp(stuIds[i], id) == 0) {
			return i;
		}
	}
	return -1;
}

int* findByGrade(float grade) {
	int index[50];
	int x = 0;
	for (int i = 0; i < cnt; i++) {
		if (grades[i] == grade) {
			index[x] = i;
			x++;
		}
	}
	return index;
}

void show(int index[]) {
	printf("\n| Index | Student ID | Grade |");
	int n = sizeof(index);
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			if (strcmp(stuIds[index[i]], "")) {
				printf("\n| %d | %s | %f |", i + 1, stuIds[index[i]], grades[index[i]]);
			}
		}
	} else {
		printf("\nUnexpected error!");
	}
}

void show(int index) {
	printf("\n| Index | Student ID | Grade |");
	if (index <= -1) {
		for (int i = 0; i < cnt; i++) {
			printf("\n| %d | %s | %f |", i + 1, stuIds[i], grades[i]);
		}
	} else {
		printf("\n| %d | %s | %f |", index + 1, stuIds[index], grades[index]);
	}
}

void add() {
	char id[10];
	char cont = 'N';
	do {
		printf("\nEnter New Student ID (No. %d):", cnt + 1);
		fflush(stdout);
		scanf("%s", &id);
		fflush(stdin);

		if (findByStudentId(id) <= -1) {
//			stuIds[cnt] = id;
//			memcpy(stuIds[cnt], id, 10);
			strcpy(stuIds[cnt], id);

			printf("Enter Grade of Student %s: ", stuIds[cnt]);
			fflush(stdout);
			scanf("%f", &grades[cnt]);
			fflush(stdin);

			cnt++;
			printf("\nAdded successfully!");
		} else {
			printf("Student ID '%s' is already existed, please try again!", id);
		}
		cont = next();
	} while(cont == 'Y' || cont == 'y');
}

void edit() {
	int index;
	char id[10];
	char cont;

	do {
		printf("\nEnter Student ID:");
		fflush(stdout);
		scanf("%s", &id);
		fflush(stdin);

		index = findByStudentId(id);

		if (index > -1) {
			show(index);

			printf("\nEnter New Grade for Student '%s': ", id);
			fflush(stdout);
			scanf("%f", &grades[index]);
			fflush(stdin);

			printf("Edited successfully!");
		} else {
			printf("Student ID '%s' does not exist, please try again!", id);
		}
		cont = next();
	} while (cont == 'Y' || cont == 'y');
}

void remove() {
	int index;
	char id[10];
	char cont;
	char confirm;

	do {
		printf("\nEnter Student ID:");
		fflush(stdout);
		scanf("%s", &id);
		fflush(stdin);

		index = findByStudentId(id);
		if (index > -1) {
			show(index);
			printf("\nDo you want to remove Grade of Student '%s'? (Y/N)", id);
			fflush(stdout);
			scanf("%s", &confirm);
			fflush(stdin);

			if (confirm == 'Y' || confirm == 'y') {
				strcpy(stuIds[index], stuIds[cnt - 1]);
				strcpy(stuIds[cnt - 1], "");

				grades[index] = grades[cnt - 1];
				grades[cnt - 1] = 0;
				cnt--;
				printf("Student '%s' has been removed successfully!", id);
			} else {
				printf("Removing has been cancelled!");
			}
		} else {
			printf("Student ID '%s' does not exist, please try again!", id);
		}
		cont = next();
	} while (cont == 'Y' || cont == 'y');
}

void sortById(int mode) {
	char tempId[10];
	float tempGrade;

	if(mode == 0) {
		for (int i = 0; i < cnt; i++) {
			for (int y = 0; y < cnt; y++) {
				if(strcmp(stuIds[i], stuIds[y]) < 0) {
					strcpy(tempId, stuIds[i]);
					strcpy(stuIds[i], stuIds[y]);
					strcpy(stuIds[y], tempId);

					tempGrade = grades[i];
					grades[i] = grades[y];
					grades[y] = tempGrade;
				}
			}
		}
	} else {
		for (int i = 0; i < cnt; i++) {
			for (int y = 0; y < cnt; y++) {
				if(strcmp(stuIds[i], stuIds[y]) > 0) {
					strcpy(tempId, stuIds[i]);
					strcpy(stuIds[i], stuIds[y]);
					strcpy(stuIds[y], tempId);

					tempGrade = grades[i];
					grades[i] = grades[y];
					grades[y] = tempGrade;
				}
			}
		}
	}
}

void sortByGrade(int mode) {
	char tempId[10];
	float tempGrade;

	if(mode == 0) {
		for (int i = 0; i < cnt; i++) {
			for (int y = 0; y < cnt; y++) {
				if(grades[i] > grades[y]) {
					strcpy(tempId, stuIds[i]);
					strcpy(stuIds[i], stuIds[y]);
					strcpy(stuIds[y], tempId);

					tempGrade = grades[i];
					grades[i] = grades[y];
					grades[y] = tempGrade;
				}
			}
		}
	} else {
		for (int i = 0; i < cnt; i++) {
			for (int y = 0; y < cnt; y++) {
				if(grades[i] < grades[y]) {
					strcpy(tempId, stuIds[i]);
					strcpy(stuIds[i], stuIds[y]);
					strcpy(stuIds[y], tempId);

					tempGrade = grades[i];
					grades[i] = grades[y];
					grades[y] = tempGrade;
				}
			}
		}
	}
}

void sort() {
	int sortOpt;

	do {
		printf("\n1. SORT BY STUDENT ID - ASC");
		printf("\n2. SORT BY STUDENT ID - DESC");
		printf("\n3. SORT BY GRADE - HIGHEST TO HIGHEST");
		printf("\n4. SORT BY GRADE - LOWEST TO LOWEST");
		printf("\n5. BACK TO MENU");
		printf("\nENTER SORTING OPTION:");
		fflush (stdout);
		scanf("%d", &sortOpt);
		fflush (stdin);
		switch (sortOpt) {
			case 1:
				printf("\nSORT BY STUDENT ID - ASC");
				sortById(0);
				show(-1);
				back();
			  break;
			case 2:
				printf("\nSORT BY STUDENT ID - DESC");
				sortById(1);
				show(-1);
				back();
			  break;
			case 3:
				printf("\nSORT BY GRADE - HIGHEST TO LOWEST");
				sortByGrade(0);
				show(-1);
				back();
			  break;
			case 4:
				printf("\nSORT BY GRADE - LOWEST TO HIGHEST");
				sortByGrade(1);
				show(-1);
				back();
			  break;
			case 5:
				printf("\nBack to Main Menu...");
			  break;
			default:
				printf("PLEASE INPUT A CORRECT INDEX OPTION!");
				break;
		}
	} while (sortOpt != 5);
}

void searchByStudentId() {
	int index;
	char id[10];
	char cont;

	do {
		printf("\nEnter Student ID:");
		fflush(stdout);
		scanf("%s", &id);
		fflush(stdin);

		index = findByStudentId(id);
		if (index > -1) {
			show(index);
		} else {
			printf("Student ID '%s' does not exist, please try again!", id);
		}
		cont = next();
	} while (cont == 'Y' || cont == 'y');
}

void searchByGrade() {
	int* index;
	float grade;
	char cont;

	do {
		printf("\nEnter Grade:");
		fflush(stdout);
		scanf("%f", &grade);
		fflush(stdin);

		index = findByGrade(grade);
		if (sizeof(index) > 0) {
			show(index);
		} else {
			printf("There is none of student has grade '%f', please try again!", grade);
		}
		cont = next();
	} while (cont == 'Y' || cont == 'y');
}

void search() {
	int searchOpt;

	do {
		printf("\n1. SEARCH BY STUDENT ID");
		printf("\n2. SEARCH BY GRADE");
		printf("\n3. FIND HIGHEST GRADE");
		printf("\n4. FIND LOWEST GRADE");
		printf("\n5. BACK TO MENU");
		printf("\nENTER SEARCHING OPTION:");
		fflush(stdout);
		scanf("%d", &searchOpt);
		fflush(stdin);
		switch (searchOpt) {
			case 1:
				printf("\nSEARCH BY STUDENT ID");
				searchByStudentId();
			  break;
			case 2:
				printf("\nSEARCH BY GRADE");
				searchByGrade();
			  break;
			case 3:
				printf("\nFIND HIGHEST GRADE");
				sortByGrade(0);
				show(0);
				back();
			  break;
			case 4:
				printf("\nFIND LOWEST GRADE");
				sortByGrade(1);
				show(0);
				back();
			case 5:
				printf("\nBack to Main Menu...");
			  break;
			default:
				printf("PLEASE INPUT A CORRECT INDEX OPTION!");
				break;
		}
	} while(searchOpt != 5);
}

int main(void) {

	int opt = 0;
	int index = -1;

	do {
		printf("\n1. GRADE BOARD");
		printf("\n2. SORTING GRADE BOARD");
		printf("\n3. SEARCH");
		printf("\n4. ADD NEW GRADEs");
		printf("\n5. EDIT GRADEs");
		printf("\n6. REMOVE GRADEs");
		printf("\n7. EXIT PROGRAM");

		printf("\nENTER A MENU INDEX:");
		fflush (stdout);
		scanf("%d", &opt);
		fflush (stdin);
		//getchar();

		switch (opt) {
		    case 1:
		    	printf("\nGRADE BOARD!");
		    	show(index);
		    	back();
		      break;
		    case 2:
		    	sort();
		      break;
		    case 3:
		    	search();
			  break;
		    case 4:
		    	printf("\nADD NEW GRADE");
				add();
			  break;
		    case 5:
				printf("\nEDIT A GRADE");
				edit();
			  break;
		    case 6:
				printf("\nREMOVE A GRADE");
				remove();
			  break;
		    case 7:
				printf("\nPROGRAM HAS BEEN STOPPED");
				return 0;
			  break;
		    default:
		    	printf("PLEASE INPUT A CORRECT MENU INDEX!");
		    	break;
		}
	} while (opt != 7);

	return 0;
}
