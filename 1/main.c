#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_LINE_LEN 200
#define MAX_STUDENTS 100

// Структура "Школьник"
typedef struct {
    char name[MAX_NAME_LEN];
    int grade;
    char phone[20];
    int math, physics, russian, literature;
} Student;

void writeStudent(FILE* file, const Student* student) {
    fprintf(file, "%s,%d,%s,%d,%d,%d,%d\n", student->name, student->grade, student->phone, student->math, student->physics, student->russian, student->literature);
}

int readStudent(FILE* file, Student* student) {
    char line[MAX_LINE_LEN];
    if (fgets(line, MAX_LINE_LEN, file) == NULL) {
        return 0;
    }

    char* token = strtok(line, ",");
    strcpy(student->name, token);

    token = strtok(NULL, ",");
    student->grade = atoi(token);

    token = strtok(NULL, ",");
    strcpy(student->phone, token);

    token = strtok(NULL, ",");
    student->math = atoi(token);

    token = strtok(NULL, ",");
    student->physics = atoi(token);

    token = strtok(NULL, ",");
    student->russian = atoi(token);

    token = strtok(NULL, ",");
    student->literature = atoi(token);

    return 1;
}

int main() {
    // 1. Створення файлу та запис структурованих даних
    FILE* file = fopen("txt1.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    Student students[MAX_STUDENTS];
    int numStudents = 0;

    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    for (int i = 0; i < numStudents; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Grade: ");
        scanf("%d", &students[i].grade);
        printf("Phone: ");
        scanf(" %[^\n]", students[i].phone);
        printf("Math: ");
        scanf("%d", &students[i].math);
        printf("Physics: ");
        scanf("%d", &students[i].physics);
        printf("Russian: ");
        scanf("%d", &students[i].russian);
        printf("Literature: ");
        scanf("%d", &students[i].literature);

        writeStudent(file, &students[i]);
    }

    fclose(file);

    // 2. Виведення створеного файлу на екран
    file = fopen("txt1.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\nOriginal file contents:\n");
    Student student;
    while (readStudent(file, &student)) {
        printf("Name: %s, Grade: %d, Phone: %s\n", student.name, student.grade, student.phone);
        printf("Math: %d, Physics: %d, Russian: %d, Literature: %d\n", student.math, student.physics, student.russian, student.literature);
    }

    fclose(file);

    // 4. Додавання даних у файл
    int K;
    printf("\nEnter the number of students to add: ");
    scanf("%d", &K);

    file = fopen("txt1.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < K; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Grade: ");
        scanf("%d", &students[i].grade);
        printf("Phone: ");
        scanf(" %[^\n]", students[i].phone);
        printf("Math: ");
        scanf("%d", &students[i].math);
        printf("Physics: ");
        scanf("%d", &students[i].physics);
        printf("Russian: ");
        scanf("%d", &students[i].russian);
        printf("Literature: ");
        scanf("%d", &students[i].literature);

        writeStudent(file, &students[i]);
    }

    fclose(file);

    // 3. Видалення даних з файлу
    file = fopen("txt1.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(file);
        return 1;
    }

    while (readStudent(file, &student)) {
        if (student.math != 2 && student.physics != 2 && student.russian != 2 && student.literature != 2) {
            writeStudent(tempFile, &student);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("txt1.txt");
    rename("temp.txt", "txt1.txt");

    // 5. Виведення зміненого файлу на екран
    file = fopen("txt1.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\nModified file contents:\n");
    while (readStudent(file, &student)) {
        printf("Name: %s, Grade: %d, Phone: %s\n", student.name, student.grade, student.phone);
        printf("Math: %d, Physics: %d, Russian: %d, Literature: %d\n", student.math, student.physics, student.russian, student.literature);
    }

    fclose(file);

    return 0;
}