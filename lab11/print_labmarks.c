// starting point for COMP1511 lab 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_STUDENT_NAME_LENGTH 128
#define MAX_GRADE_STRING_LENGTH 22
#define MAX_LAB_NAME_LENGTH 32
#define MAX_LINE_LENGTH 4096

double grade2labmark(char grade, bool isPlus) {
	if (grade == 'A') {
		if (isPlus) {
			return 1.2;
		}
		return 1;
	}
	if (grade == 'B') {
		return 0.8;
	}
	if (grade == 'C') {
		return 0.5;
	}
	if (grade == '.') {
		return 0;
	}
	return 0;
}

double grades2labmark(char grades[]) {
	double sum = 0;
	int index = strlen(grades) - 1;
	int num_grades = 0;
	while (index >= 0) {
		if (grades[index] == '+') {
			index--;
			sum += grade2labmark(grades[index], true);
		} else {
			sum += grade2labmark(grades[index], false);
		}
		index--;
		num_grades++;
	}
	
	if (sum > 10) {
		return 10;
	}
	return sum;
}

struct student {
    int              zid;
    char             name[MAX_STUDENT_NAME_LENGTH + 1];
    char             lab_name[MAX_LAB_NAME_LENGTH + 1];
    char             lab_grades[MAX_GRADE_STRING_LENGTH + 1];
    struct student   *next;
};

struct student *read_students_file(char filename[]);
struct student *read_student(FILE *stream);

void print_student_result(struct student *a_student) {
	double mark = grades2labmark(a_student->lab_grades);
	printf("%d %-30s %-12s %-22s %4.1lf\n", a_student->zid, a_student->name, a_student->lab_name, a_student->lab_grades,  mark);
}

void print_results_for(struct student *student_list, char lab_name[MAX_LAB_NAME_LENGTH + 1]) {
	struct student *a_student = student_list;
	while (a_student->next != NULL) {
		if (strcmp(a_student->lab_name, lab_name) == 0) {
			print_student_result(a_student);
		}
		a_student = a_student->next;
	}
}

int main(int argc, char *argv[]) {
    // CHANGE THIS CODE

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <marks-file> <tut-lab-name>\n", argv[0]);
        return 1;
    }

    struct student *student_list = read_students_file(argv[1]);

    //printf("Students file read into linked list (pointer=%p)\n", student_list);
    print_results_for(student_list, argv[2]);

    return 0;
}

// DO NOT CHANGE THE CODE BELOW HERE - DO NOT CHANGE read_students_file

// read_students_file reads a file where line contains information for 1 student
// it creates a linked of student structs containing the information
// it returns a pointer to the head of the list

struct student *read_students_file(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"warning file %s could not  be opened for reading\n", filename);
        return NULL;
    }

    struct student *first_student = NULL;
    struct student *last_student = NULL;
    struct student *s;
    while ((s = read_student(fp)) != NULL) {
        if (last_student == NULL) {
            first_student = s;
            last_student = s;
        } else {
            last_student->next = s;
            last_student = s;
        }
    }

    fclose(fp);
    return first_student;
}

// DO NOT CHANGE read_student

// read_student mallocs a student struct
// and reads a line in this format:
//
// 5099703 Tsun Bordignon thu13-sitar A+A+CABAB..A.
//
// stores the values in the struct field
// and returns a pointer to the struct

struct student *read_student(FILE *stream) {
    char line[MAX_LINE_LENGTH];

    struct student *s = malloc(sizeof (struct student));
    assert(s);

    if (fgets(line, MAX_LINE_LENGTH, stream) == NULL) {
        free(s);
        return NULL;
    }

    char *newline_ptr = strchr(line, '\n');
    assert(newline_ptr);
    *newline_ptr = '\0';

    char *space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_grades, space_ptr + 1, MAX_GRADE_STRING_LENGTH);
    s->lab_grades[MAX_GRADE_STRING_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_name, space_ptr + 1, MAX_LAB_NAME_LENGTH);
    s->lab_name[MAX_LAB_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strchr(line, ' ');
    assert(space_ptr);
    strncpy(s->name, space_ptr + 1, MAX_STUDENT_NAME_LENGTH);
    s->name[MAX_STUDENT_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    s->zid = atoi(line);
    s->next = NULL;
    return s;
}
