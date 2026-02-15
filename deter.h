#ifndef DETER_H
#define DETER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#define MAX_NAME_LENGTH 100
#define MAX_GROUP_LENGTH 20
#define MAX_SUBJECT_NAME_LENGTH 56
#define DEFAULT_MIN_SUBJECTS 10
#define DEFAULT_MAX_SUBJECTS 20
#define SUBEJCTS_LEN 40
#define MAX_NUMBER_FOR_GEN 5 * 1024 * 1024
#define COUNT_GROUPS 100

typedef struct
{
    char month;
    char day;
    short year;
} dateParts;

typedef struct
{
    unsigned char lecture_room;
    unsigned char lab_room;
    unsigned char total_hours;
    unsigned char assessment_type;
    char *name;
} Subject;

typedef struct
{
    char name[30];
    char surname[30];
    char middlename[30];
    char number_group;
    unsigned char subjects[SUBEJCTS_LEN];
    unsigned char subjects_count;
    dateParts BD;

} Person;

static char *SUBJECT_NAMES[] = {
    "Математический анализ", "Линейная алгебра", "Дискретная математика",
    "Физика", "Информатика", "Программирование", "Базы данных",
    "Операционные системы", "Компьютерные сети", "Алгоритмы и структуры данных",
    "Теория вероятностей", "Статистика", "Дифференциальные уравнения",
    "Теория алгоритмов", "Искусственный интеллект",
    "Машинное обучение", "Веб-программирование", "Мобильная разработка",
    "Кибербезопасность", "Компьютерная графика", "Программная инженерия",
    "Компиляторы", "Численные методы", "Вычислительная математика",
    "Теория графов", "Криптография", "Распределенные системы",
    "Параллельное программирование", "Архитектура компьютеров",
    "Системное программирование", "Функциональное программирование",
    "Объектно-ориентированное программирование", "Тестирование программного обеспечения",
    "Управление проектами", "Экономика программной инженерии",
    "Интернет вещей", "Большие данные", "Облачные вычисления",
    "DevOps практики", "Микросервисная архитектура"};

unsigned char SUBJECTS_MIN = DEFAULT_MIN_SUBJECTS;
unsigned char SUBJECTS_MAX = DEFAULT_MAX_SUBJECTS;
long long already_gen = 0;
unsigned long ALL_MEMORY_USED_BY_STUDENTS = 0;

static Subject *links_on_sub = NULL;
int seed;
static char **GROUPS;

#endif // DETER_H
