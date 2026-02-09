#ifndef DETER_H
#define DETER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#define MAX_NAME_LENGTH 100
#define MAX_GROUP_LENGTH 20
#define MAX_SUBJECT_NAME_LENGTH 30
#define DEFAULT_MIN_SUBJECTS 10
#define DEFAULT_MAX_SUBJECTS 20
#define SUBEJCTS_LEN 22


typedef enum {
    NAME = 0,
    SURNAME = 1,
    MIDDLENAME = 2
} FIO;


// typedef enum {
//     EXAM = 0,       // Экзамен
//     TEST = 1,       // Зачет
//     COURSEWORK = 2  // Курсовая работа
// } AssessmentType;

typedef struct
{
    unsigned char lecture_room;
    unsigned char lab_room;
    unsigned char total_hours;
    unsigned char assessment_type;
    char name[MAX_SUBJECT_NAME_LENGTH];
} Subject;

typedef struct
{      
    unsigned char subjects_count;
    unsigned char subjects_capacity;
    Subject *subjects;
    char name[31];
    char surname[31];
    char middlename[31];
} Person;

static char* SUBJECT_NAMES[] = {
    "Математический анализ", "Линейная алгебра", "Дискретная математика",
    "Физика", "Информатика", "Программирование", "Базы данных",
    "Операционные системы", "Компьютерные сети", "Алгоритмы и структуры данных",
    "Теория вероятностей", "Статистика", "Дифференциальные уравнения",
    "Теория алгоритмов", "Компиляторы", "Искусственный интеллект",
    "Машинное обучение", "Веб-программирование", "Мобильная разработка",
    "Кибербезопасность", "Компьютерная графика", "Программная инженерия"
};

static Subject *links_on_sub = NULL;

#endif // DETER_H

