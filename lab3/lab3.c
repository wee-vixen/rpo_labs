#include "lab3.h"
#include <stdio.h>
#include <string.h>
#include <strings.h> /*тут лежит функция 
						int strcasecmp(const char *str1, const char *str2);*/
#include <stdbool.h>
#include <stdlib.h>
#include <iso646.h> 

#define MAX(x, y) (x > y) ? x : y

unsigned long int g_Id = 1;

University *initUniversity(const char *fileName) {
    University *university = (University *) calloc (1, sizeof(University));
    if (university == NULL) {
        return NULL;
    }
    university->groups = NULL;
	university->groupsCount = 0;

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
		return university;
    }
	
    Group *ness_group = NULL;

    while (!feof(file)) {
        Student* student = (Student *) calloc(1, sizeof(Student));
        fread(student, sizeof(Student), 1, file);
	
		if (feof(file)) {
			free(student);
			break;
		}

        ness_group = getGroup(university, student->groupName);
        if (ness_group == NULL) { // подготовка к добавлению новой группы
            Group *new_group = (Group *) calloc(1, sizeof(Group));
            new_group->studentsCount = 0; 

            strcpy(new_group->name, student->groupName);
            new_group->students = NULL;
            
            addNewGroup(university, *new_group);
				
            free(new_group);
            ness_group = getGroup(university, student->groupName);
        }
        addNewStudent(ness_group, *student);
        free(student);
    }

	unsigned long int max_ID = 0;
	for (int i = 0; i < university->groupsCount; i++) {
		for(int j = 0; j < university->groups[i].studentsCount; j++) {
			max_ID = MAX(max_ID, university->groups[i].students[j].id);
		}
	} 
    g_Id = max_ID + 1;

	fclose(file);
    return university;
}

bool addNewGroup(University *university, const Group group) {
    if (university == NULL) {
        return false;
    }
	Group *tmp_group = NULL;
    if (university->groupsCount == 0) {
        tmp_group = (Group *) calloc(1, sizeof(Group));/*выделена память только под 1 группу*/
		if (tmp_group == NULL) {
			return false;
		}
    }
	if (university->groupsCount not_eq 0){
        tmp_group = (Group *) realloc(university->groups, (university->groupsCount + 1) * sizeof(Group));
		/*увеличиваю размер блока памяти на sizeof(Group) для записи новой группы*/
		if (tmp_group == NULL) {
			return false;
		}
	}
	university->groups = tmp_group;
	university->groups[university->groupsCount] = group;
    university->groupsCount+=1;

    return true;
}

bool addNewStudent(Group *group, Student student) {
    if (group == NULL) {
        return false;
   }
    if (strcmp(student.groupName, group->name) not_eq 0) {
        return false;
    }
	Student *tmp_student = NULL;
    if (group->studentsCount == 0) {
        tmp_student = (Student *) calloc(1, sizeof(Student));
		if (tmp_student == NULL) {
			return false;
		}
    } 
	else {
        tmp_student = (Student *) realloc(group->students, 
							(group->studentsCount + 1)* sizeof(Student));
		if (tmp_student == NULL){
			return false;
		}
    }
	group->students = tmp_student;
    if (student.id == 0) {
        student.id = g_Id;
    } /*назначает ID переданному студенту при условии, что он не задан*/

    group->students[group->studentsCount] = student;
    group->studentsCount+=1;

	//insert sort группы по фамилиями после добавления нового студента
	for (int i = 1; i < group->studentsCount; ++i) {
		int k = i;
		while ((k > 0) and (strcasecmp(group->students[k].surname, group->students[k - 1].surname) < 0)) {
			Student temporary = group->students[k - 1];
			group->students[k - 1] = group->students[k];
			group->students[k] = temporary;
			k -= 1;
		}
	}

	if (student.id > g_Id) {
		g_Id = student.id + 1;
	}
	else {
		g_Id += 1;
	}
    return true;
}

bool removeGroup(University *university, const char *name) {
    if (university == NULL or name == NULL) {
        return false;
    }
	
    for (int i = 0; i < university->groupsCount; i++) {
        if (strcmp(university->groups[i].name, name) == 0) {
            free(university->groups[i].students);/*удаляем студентов, 
												записанных в этой группе*/
            
			memmove(&university->groups[i], &university->groups[i + 1],
                    (university->groupsCount - i - 1) * sizeof(Group)); 
            university->groupsCount = university->groupsCount - 1;
            return true;
        }
    }
    return false;
}

bool removeStudent(University *university, const unsigned long id) {
    if (university == NULL) {
        return false;
    }

    for (int i = 0; i < university->groupsCount; i++) {
        for (int j = 0; j < university->groups[i].studentsCount; j++) {
            if (university->groups[i].students[j].id == id) {
                memmove(&university->groups[i].students[j], &university->groups[i].students[j + 1],
                        (university->groups[i].studentsCount - j - 1) * sizeof(Student));
                university->groups[i].studentsCount = university->groups[i].studentsCount - 1;
                return true;
            }
        }
    }
    return false;
}

Group *getGroup(const University *university, const char *name) {
    if (university == NULL or name == NULL) {
        return NULL;
    }
    for (int i = 0; i < university->groupsCount; i++) {
        if (strcmp(university->groups[i].name, name) == 0) {
            return &university->groups[i]; /*возвращаемое значение - указатель
											на группу по заданному имени name*/
        }
    }
    return NULL;
}

Student *getStudent(const University *university, const unsigned long id) {
    if (university == NULL) {
        return NULL;
    }
    for (int i = 0; i < university->groupsCount; i++) {
        for (int j = 0; j < university->groups[i].studentsCount; j++) {
            if (university->groups[i].students[j].id == id) {
                return &university->groups[i].students[j];
						/*указатель на студента по заданному ID*/
            }
        }
    }
    return NULL;
}

void printUniversity(const University *university) {
    if (university == NULL) {
        return;
    }

    for (int i = 0; i < university->groupsCount; i++) {
        printf("------------------------------------------------------------------------------\n");
		printGroup(university->groups[i]);
	}
	printf("------------------------------------------------------------------------------\n");
    if (university->groupsCount == 0) {
        printf("Выбранный Вами университет пуст.\n");
    }
}

void printGroup(const Group group) {
	printf("%s\n", group.name);
    for (int i = 0; i < group.studentsCount; i++) {
        printStudent(group.students[i]);
    }
    if (group.studentsCount == 0) {
        puts("Выбранная Вами группа пуста.");
    }
}

void printStudent(const Student student) {
    putchar('\t'); printf("%lu\n", student.id); 
	putchar('\t'); putchar('\t'); printf("%s %s\n", student.surname, student.name);
	printf("\t\t%u\n", student.birthYear); 
}

void freeUniversity(University *university) {
    for (int i = 0; i < university->groupsCount; i++) {
        free(university->groups[i].students);
    }
    free(university->groups);
    free(university);
}

bool saveToFile(const char *fileName, const University *university) {
	if (fileName == NULL or university == NULL) {
		return false;
	}

    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        return false;
    }

    for (int i = 0; i < university->groupsCount; i++) {
        for (int j = 0; j < university->groups[i].studentsCount; j++) {
            fwrite(&university->groups[i].students[j], sizeof(Student), 1, file);
        }
    }

    fclose(file);
	printf("Данные были записаны успешно!\n"); 

    return true;
}
