#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iso646.h>
#include "lab3.h"

typedef enum {
    E_INVALID = 0,
    E_ADD_GROUP,
    E_ADD_STUDENT,
    E_DEL_GROUP,
    E_DEL_STUDENT,
    E_PRINT_UNI,
    E_PRINT_GROUP,
    E_PRINT_STUDENT,
    E_END
} EAction;

const char *Enum2Str(EAction eAct) {
    switch (eAct) {
        case E_INVALID:
            return "- Невалидная команда";
        case E_ADD_GROUP:
            return "- Добавить группу";
        case E_ADD_STUDENT:
            return "- Добавить студента";
        case E_DEL_GROUP:
            return "- Удалить группу";
        case E_DEL_STUDENT:
            return "- Удалить студента";
        case E_PRINT_UNI:
            return "- Напечатать информацию об университете";
        case E_PRINT_GROUP:
            return "- Напечатать информацию о группе";
        case E_PRINT_STUDENT:
            return "- Напечатать информацию о студенте";
        case E_END:
            return "- Окончание работы";
        default:
            return "? - Невалидная команда";
    }
}

int main(int argc, char** argv) {
    char* file = NULL;
    int must_free = 0;

    if (argc < 2) {
        puts("Введите имя файла:");
		scanf("%s", file);
		/*char proverka[] = "\\:*?\"<>|/"; //это проверка на корректный ввод имени файла
		for (int i = 0; i < strlen(file); i++) {
			if (file[i] == proverka[i] and proverka[i] not_eq '\0') {
				puts("Имя файла введено некорректно!");
			}
		}*/
		must_free = 1;
    } 
	else {
        file = argv[1];
    }

    University* university = initUniversity(file);
    EAction eAction = E_INVALID;
	Student* student;

    while (eAction not_eq  E_END) {
        puts("Выберите то действие, которое хотите выполнить:");
		for (int i = 1; i < E_END + 1; i++) {
			printf("№%d функции %s", i, Enum2Str((EAction) i));
			putchar(10);
		}

		int choice = 0;
		scanf("%d", &choice);
		if (choice < E_INVALID or choice > E_END) {
			eAction = E_INVALID;
		}
		else {
			eAction = (EAction) choice;
		}
        switch (eAction) {
            case (E_ADD_GROUP):
				{
				char group_name[SIZE];
				puts("Введите название группы:");
				scanf("%s", group_name);
				Group* add_group = calloc(1, sizeof(Group));
				strcpy(add_group->name, group_name);
				if (addNewGroup(university, *add_group)) {
					printf("Группа %s была добавлена!\n", group_name);
				}
				else {
					puts("Мда, error");
				}

                free(add_group);
                continue;
				}
            case (E_ADD_STUDENT):
				{
				puts("Небольшое анкетирование:>");
               	student = calloc( 1, sizeof(Student));

				puts("Введите имя студента:");
				scanf("%s", student->name);
				
				puts("Введите фамилию студента:");
				scanf("%s", student->surname);

				puts("Введите год рождения студента:");
				scanf("%u", &(student->birthYear));

				puts("Введите название нужной группы:");
				scanf("%s", student->groupName);
				
				if (getGroup(university, student->groupName) == NULL) {
					puts("Что-то пошло не так. Такой группы нет!");
				}
				else {
					Group* group_student = getGroup(university, student->groupName);
					addNewStudent(group_student, *student);
					puts("Студент теперь в группе!");
				}
                continue;
				}
            case E_DEL_GROUP:
                {
				char group_name[SIZE];
				puts("Введите название группы, которую следует удалить:");
				scanf("%s", group_name);
				if (removeGroup(university, group_name)) {
					puts("Данная группа была успешно удалена!");
				}
				else {
					puts("Такой группы не существует!");
				}
                continue;
				}
            case E_DEL_STUDENT:
                {
				unsigned long int ID = 0;
				puts("Введите ID того студента, от которого желаете избавиться");
				scanf("%lu", &ID);
				if (removeStudent(university, ID) == false) {
					puts("Студент с введённым ID не найден!");
				}
				if (removeStudent(university, ID)) {
					puts("Студент с введённым ID покинул чат!");
				}
                continue;
				}
            case E_PRINT_UNI:
                printUniversity(university);
                continue;
            case E_PRINT_GROUP:;
				{
				puts("Введите название группы:");
				char groupname[SIZE];
				scanf("%s", groupname);
				Group* group_search = getGroup(university, groupname);
				if (group_search == NULL) {
					puts("Группа с данным названием не найдена!");
				}
				else {
					printGroup(*group_search);
				}
                continue;
				}
            case E_PRINT_STUDENT:
				{
                unsigned long int ID = 0;
				puts("Введите ID студента:");
				scanf("%lu", &ID);
				Student *student = getStudent(university, ID);
				if (student == NULL){
					puts("Студент с данным ID не найден!");
				}
				else {
					printStudent(*student);
				}
                continue;
				}
            case E_INVALID:
                puts("? - Невалидная команда");
                continue;
            case E_END:
				puts("Окончание работы");
                break;
        }
    }

    puts("This is the end:<");
	char SaveFile[SIZE];
	puts("Введите название для файла под сохранение:");
    scanf("%s", SaveFile);
	/*char proverka[] = "\\:*?\"<>|/"; //это проверка на корректный ввод имени файла
 	for (int i = 0; i < strlen(SaveFile); i++) {
		if (SaveFile[i] == proverka[i] and proverka[i] not_eq '\0' and SaveFile not_eq '\0') {
			puts("Некорректный ввод имени файла!");
		}
	} */
    printf("Сохранение в файл %s\n", SaveFile);
	saveToFile(SaveFile, university);
    
	freeUniversity(university);
    if (must_free == 1) {
		free(file);
	}

    return 0;
}
