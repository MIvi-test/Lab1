#include "deter.h"

int get_random(int min, int max) // randint
{
    srand(seed);
    int random_number = min + rand() % (max - min - 1);
    seed = (seed+random_number) % 54351245;
    return random_number;
}

bool read_file(char *path, char *return_info, int max) // вспомогательная функция. Берем из файла рандом строку
{
    FILE *f = fopen(path, "r");
    if(f == NULL)
    {
        perror("Ошибка нахождения файла\n");
        return false;
    }
    char *BUFFER = (char *)malloc(256 * sizeof(char));
    if (BUFFER == NULL)
    {
        perror("ошибка выделения памяти\n");
        fclose(f);
        return false;
    }
    int random_number = get_random(1, max);
    while (random_number--)
    {
        fscanf(f, "%s\n", BUFFER);
    }
    fscanf(f, "%s\n", BUFFER);
    // printf("(1) %s\n", BUFFER); // просто для дебагинга, посмотреть что выдаёт
    strcpy(return_info, BUFFER);
    fclose(f);
    return true;
}

void christening(Person *student)
{
    char *path1, *path2, *path3;
    path1 = "lists/male_names_rus.txt";
    int max_name = 731;
    path2 = "lists/male_surnames_rus.txt";
    int max_surname = 14651;
    path3 = "lists/middlenames.txt";
    int max_middlename = 731;
    // происходит внутри сразу копирование, поэтому надо изначально выделять память, вне функции
    read_file(path1, student->name, max_name);
    read_file(path2, student->surname, max_surname);
    read_file(path3, student->middlename, max_middlename);
    printf("(2) %s\t", student->name);
    printf("(3) %s\t", student->surname);
    printf("(4) %s\n", student->middlename);
    // для дебагинга
    return;
}

bool initialization_subjects()
{
    links_on_sub = malloc(sizeof(Subject) * SUBEJCTS_LEN);
    if (links_on_sub == NULL)
    {
        perror("ошибка выделения памяти в инициализации предметов\n");
        return false;
    }

    for (int i = 0; i < SUBEJCTS_LEN; i++)
    {
        Subject sub = {
            .total_hours = get_random(10, 255),
            .lecture_room = get_random(1, 255),
            .lab_room = get_random(1, 255),
            .assessment_type = get_random(0, 2),
            .name = SUBJECT_NAMES[get_random(1, SUBEJCTS_LEN)]};
        links_on_sub[i] = sub;
    }
    return true;
}

bool get_subjects(unsigned char len, Person *student) // присвоение каждому студенту список предметов, реализация массовой неповторяющейся рандома
{
    if (len < 1 || len > SUBEJCTS_LEN)
    {
        printf("такого количества я создавать не буду.\n");
        return false;
    }
    Subject *p = calloc(len, sizeof(Subject));
    if (p == NULL)
    {
        printf("ошибка выделения памяти\n");
        return false;
    }

    student->subjects = p; // ссылка на обьем дисциплин
    student->subjects_count = len;
    student->subjects_capacity = sizeof(Subject) * len;
    for (char i = 0; i < len; i++)
    {
        unsigned char random_number = 1 + rand() % SUBEJCTS_LEN;
        for (char j = 0; j < i; j++)
        {
            if (&(p[j]) == &(links_on_sub[random_number]))
            {
                i--;
                goto A; // снова надо отработать для генерации i предмета в список
            }
        }
        p[i] = links_on_sub[random_number]; // добавляем рандомный предмет

    A:
        continue;
    }
    return true;
}

Person *gen(int N)
{
    if (N >= 5 * 1024 * 1024 * 8 / 150 || N < 1)
    {
        printf("такое количество пользователей создаваться не будет.\n");
        return NULL;
    }
    Person *p = calloc(N, sizeof(Person));
    if(p == NULL)
    {
        perror("ошибка выделения памяти \n");
        return NULL;
    }
    for(int i = 0; i < N; i++)
    {
        Person stud;

        //инициализация студента
        unsigned char len = get_random(MIN_SUBJECTS, MAX_SUBJECTS);
        christening(&stud);//имянаречение
        get_subjects(len, &stud); //предметонаречение

        p[i] = stud;
    }
    return p;
}

void get_size()
{
    ;
}

void print_students(int N)
{
    ;
}

void clean() // суда закидывается массив студентов
{
    ;
}
//надо реализовать интерфейс для консоли, \
 можно было динамически вызывать функции
int main()
{   
    char *locale = setlocale(LC_ALL, "Rus"); 
    seed = time(NULL)+1;
    srand(seed);
    initialization_subjects(); //создаю список предметов, чтобы потом на них кидать ссылку, будет \
    // О(1) по памяти будет
    Person *students = gen(7);

    return 1;
}