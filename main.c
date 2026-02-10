#include "deter.h"

int get_random(int min, int max) // randint
{
    srand(seed);
    int random_number = min + rand() % (max - min - 1);
    seed = (seed + random_number) % 54351245;
    return random_number;
}

bool read_file(char *path, char *return_info, int max) // вспомогательная функция. Берем из файла рандом строку
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        perror("Ошибка нахождения файла\n");
        return false;
    }
    char BUFFER[256];
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
    int max_name = 388;
    path2 = "lists/male_surnames_rus.txt";
    int max_surname = 14651;
    path3 = "lists/middlenames.txt";
    int max_middlename = 388;
    // происходит внутри сразу копирование, поэтому надо изначально выделять память, вне функции
    read_file(path1, student->name, max_name);
    read_file(path2, student->surname, max_surname);
    read_file(path3, student->middlename, max_middlename);
    // printf("(2) %s\t", student->name);
    // printf("(3) %s\t", student->surname);
    // printf("(4) %s\n", student->middlename);
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
            .assessment_type = get_random(0, 3),
            .name = SUBJECT_NAMES[i]};
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

    student->subjects_count = len;
    unsigned char random_number = get_random(0, SUBEJCTS_LEN);
    char step = get_random(1, 4);
    if(random_number == SUBEJCTS_LEN)
    {
        printf("!!!");
    }
    for (char i = 0; i < len; i++)
    {
        random_number = (random_number + step+1) % SUBEJCTS_LEN;
        student->subjects[i] = random_number; // добавляем рандомный предмет

    A:
        continue;
    }
    return true;
}

Person *gen(size_t N, char min_sub, char max_sub)
{
    // if (N >= 5 * 1024 * 1024 * 8 / 150 || N < 1)
    // {
    //     printf("такое количество пользователей создаваться не будет.\n");
    //     return NULL;
    // }
    size_t memory = N * sizeof(Person);
    Person *p = malloc(memory);
    if (p == NULL)
    {
        perror("ошибка выделения памяти \n");
        return NULL;
    }
    ALL_MEMORY_USED_BY_STUDENTS += memory;
    already_gen += N;

    for (int i = 0; i < N; i++)
    {
        Person stud;

        // инициализация студента
        unsigned char len = get_random(min_sub, max_sub);
        christening(&stud);       // имянаречение
        get_subjects(len, &stud); // предметонаречение

        p[i] = stud;
    }
    return p;
}

void get_size()
{
    printf("%u", ALL_MEMORY_USED_BY_STUDENTS);
    return;
}

void print_students(int N, Person *students)
{
    if (N > already_gen)
    {
        printf("у вас столько не сгенерирован\n");
        return;
    }
    if (N == -1)
    {
        N = already_gen;
    }
    for (size_t i = 0; i < N; i++)
    {
        Person stud = students[i];
        printf("%s %s %s\n",
               stud.name,
               stud.surname,
               stud.middlename);

        char *AssessmentType;
        for (size_t j = 0; j < stud.subjects_count-1; j++)
        {
            char n = stud.subjects[j]; // номер предмета
            
            if(links_on_sub[n].assessment_type ==  0)
                AssessmentType = "EXAM";
            else if(links_on_sub[n].assessment_type ==  1)
                AssessmentType = "TEST";
            else if(links_on_sub[n].assessment_type ==  2)
                AssessmentType = "COURSEWORK";

            printf("| %s ", links_on_sub[n].name);
            printf("| total_hours: %d ", links_on_sub[n].total_hours);
            printf("| lab_room: %d ", links_on_sub[n].lab_room);
            printf("| lecture_room: %d ", links_on_sub[n].lecture_room);
            printf("| assessment_type: %s\n", AssessmentType);
        
        }
    }
    return;
}

void clean(Person *students) // суда закидывается массив студентов
{   
    for(size_t i = 0; i <already_gen; i++)
    {
        Person per = students[i];
        free(&per);
        ALL_MEMORY_USED_BY_STUDENTS -= sizeof(per);
        already_gen--;
    }
    return;
    
}
//надо реализовать интерфейс для консоли, \
 можно было динамически вызывать функции



 int main()
{
    char *locale = setlocale(LC_ALL, "Rus");
    seed = time(NULL) + 1;
    srand(seed);
    if (!initialization_subjects())
    {
        perror("ошибка инициализации\n");
        return -1;
    }
    // создаю список предметов, чтобы потом на них кидать ссылку, будет
    //  О(1) по памяти будут предметы как обьекты
    Person *students = gen(1000, MIN_SUBJECTS, MAX_SUBJECTS);
    print_students(10, students);
    get_size();
    // for(int i = 0; i < SUBEJCTS_LEN; i++)
    // {
    //     printf("%s ", links_on_sub[i].name);
    //     printf("%d ", links_on_sub[i].lab_room);
    //     printf("%d\n", links_on_sub[i].total_hours);
    // }
    // printf("%d\n", sizeof(Person));
    return 1;
}