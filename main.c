#include "deter.h"


int get_random(int min, int max) //randint
{
    srand(time(NULL));
    int random_number = min + rand() % (max - min-1);
    return random_number;
}

void read_file(char *path, char *return_info, int max) // вспомогательная функция. Берем из файла рандом строку
{
    FILE *f = fopen(path, "r");
    char *BUFFER = (char *)malloc(256 * sizeof(char));
    if(BUFFER == NULL)
    {
        perror("ошибка выделения памяти\n");
        fclose(f);
        return;
    }
    int random_number = get_random(1, max);
    while (random_number--)
    {
        fscanf(f, "%s\n", BUFFER);
    }
    fscanf(f, "%s\n", BUFFER);
    printf("(1) %s\n", BUFFER); // просто для дебагинга, посмотреть что выдаёт
    strcpy(return_info, BUFFER);
    fclose(f);
    return;

}

void get_strings_from_file(char *return_name, char *return_surname, char *return_middlename)
{
    char *path1,*path2,*path3;
    path1 = "lists/male_names_rus.txt";
    int max_name = 731;
    path2 = "lists/male_names_rus.txt";
    int max_surname = 14651;
    path3 = "lists/middlenames.txt";
    int max_middlename = 731;
    //происходит внутри сразу копирование, поэтому надо изначально выделять память, вне функции
    read_file(path1,return_name,max_name);
    read_file(path2,return_surname,max_surname);
    read_file(path3,return_middlename,max_middlename);
    printf("(2) %s\t",return_name);
    printf("(3) %s\t",return_surname);
    printf("(4) %s\n",return_middlename);
    //для дебагинга
    return;
}

void initialization_subjects()
{
    links_on_sub = malloc(sizeof(Subject) * SUBEJCTS_LEN);
    if (links_on_sub == NULL)
    {
        perror("ошибка выделения памяти в инициализации предметов\n");
        return;
    }
    
    for(int i = 0; i < SUBEJCTS_LEN; i++)
    {
        Subject sub = {
            .total_hours = get_random(10,255),
            .lecture_room = get_random(1,255),
            .lab_room = get_random(1,255),
            .assessment_type = get_random(0,2)};
        strcpy(sub.name, SUBJECT_NAMES[i]);
        links_on_sub[i] = sub;
    }
}

void get_subjects(int len) // присвоение каждому студенту список предметов, реализация массовой неповторяющейся рандома
{
    if(len < 1 || len > SUBEJCTS_LEN)
    {
        printf("такого количества я создавать не буду.\n");
        return;
    }
    for(char i = 0; i < len; i++)
    {
        srand(time(NULL));
        unsigned char random_number = 1 + rand() % SUBEJCTS_LEN;
        for(char j = 0; j < i; j++)
        {
            //
        }

        A:
        continue;
    }
}

int gen(int N)
{
    if (N >= 5 * 1024 * 1024 * 8 / 150 || N < 1)
    {
        printf("такое количество пользователей создаваться не будет.\n");
        return -1;
    }
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
    initialization_subjects(); //создаю список предметов, чтобы потом на них кидать ссылку, будет \
    // О(1) по памяти будет

    printf("%d", sizeof(short) > sizeof(int));
}