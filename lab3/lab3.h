#ifndef LAB3_H
#define LAB3_H
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 128 

typedef struct {
    unsigned long id;   
    char name[SIZE];    
    char surname[SIZE];    
    char groupName[SIZE];   
    unsigned birthYear;     
} Student;

typedef struct {
    char name[SIZE];       
    unsigned studentsCount;
    Student *students;      
} Group;

typedef struct {
    unsigned groupsCount;   
    Group *groups;         
} University;

University *initUniversity(const char *fileName);
bool addNewGroup(University *university, const Group group);
bool addNewStudent(Group *group, Student student);
bool removeGroup(University *university, const char *name);
bool removeStudent(University *university, const unsigned long id);
Group *getGroup(const University *university, const char *name);
Student *getStudent(const University *university, const unsigned long id);
void printUniversity(const University *university); // +
void printGroup(const Group group); // +
void printStudent(const Student student); // +
void freeUniversity(University *university);
bool saveToFile(const char *fileName, const University *university);

#endif //LAB3_H//
