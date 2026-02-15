#include "deter.h"

// Реализация алгоритма Боера-Мура для поиска подстроки в строке
// Возвращает позицию первого вхождения pattern в text, либо -1 если не найдено

int max(int a, int b)
{
  return (a > b) ? a : b;
}

// Предобработка таблицы смещений для плохого символа
void build_bad_char_table(const char *pattern, int m, int bad_char_table[256])
{
  int i;
  for (i = 0; i < 256; ++i)
    bad_char_table[i] = -1;
  for (i = 0; i < m; ++i)
    bad_char_table[(unsigned char)pattern[i]] = i;
}

// Поиск Боера-Мура
int boyer_moore(const char *text, const char *pattern)
{
  int n = strlen(text);
  int m = strlen(pattern);

  if (m == 0 || n == 0 || m > n)
    return -1;

  int bad_char_table[256];
  build_bad_char_table(pattern, m, bad_char_table);

  int shift = 0;
  while (shift <= n - m)
  {
    int j = m - 1;

    // Сравниваем справа налево
    while (j >= 0 && pattern[j] == text[shift + j])
      j--;

    if (j < 0)
    {
      // Найдено вхождение
      return shift;
    }
    else
    {
      int bad_char_shift = j - bad_char_table[(unsigned char)text[shift + j]];
      shift += max(1, bad_char_shift);
    }
  }

  return -1;
}

int get_random(int min, int max) // randint
{
  srand(seed);
  int random_number = min + rand() % (max - min);
  seed = (seed + random_number * 10) % 54351245;
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

void get_BirthDay(Person *student)
{
  student->BD.year = get_random(1990, 2010);
  student->BD.month = get_random(1, 12);
  student->BD.day = get_random(1, 28);
  return;
}

void get_group(Person *student)
{
  int number = get_random(0, COUNT_GROUPS - 1);
  student->number_group = number;
  return;
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
  // происходит внутри сразу копирование, поэтому надо изначально выделять
  // память, вне функции
  read_file(path1, student->name, max_name);
  read_file(path2, student->surname, max_surname);
  read_file(path3, student->middlename, max_middlename);

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
    Subject sub = {.total_hours = get_random(10, 255),
                   .lecture_room = get_random(1, 255),
                   .lab_room = get_random(1, 255),
                   .assessment_type = get_random(0, 3),
                   .name = SUBJECT_NAMES[i]};
    links_on_sub[i] = sub;
  }
  return true;
}

bool initialization_groups()
{
  GROUPS = malloc(COUNT_GROUPS * sizeof(char *));
  if (!GROUPS)
  {
    return false;
  }
  for (int i = 0; i < COUNT_GROUPS; i++)
  {
    char *group = calloc(sizeof(char), 20);
    if (!group)
    {
      return false;
    }
    for (char t = 0; t < 4; t++)
    {
      int s = get_random(10000, 99999);
      for (int j = t * 5; j < t * 5 + 5; j++)
      {
        group[j] = (s % 10) + 48;
        s = s / 10;
      }
      group[19] = '\0';
    }
    GROUPS[i] = group;
  }
  return true;
}

bool get_subjects(unsigned char len, Person *student) // присвоение каждому студенту список предметов, реализация                                                // массовой неповторяющейся рандома
{
  if (len < 1 || len > SUBEJCTS_LEN)
  {
    printf("такого количества я создавать не буду.\n");
    return false;
  }

  student->subjects_count = len;
  unsigned char random_number = get_random(0, SUBEJCTS_LEN);
  char step = get_random(1, 4);
  if (random_number == SUBEJCTS_LEN)
  {
    printf("!!!");
  }
  for (char i = 0; i < len; i++)
  {
    random_number = (random_number + step + 1) % SUBEJCTS_LEN;
    student->subjects[i] = random_number; // добавляем рандомный предмет

  A:
    continue;
  }
  return true;
}

Person *gen(size_t N, char min_sub, char max_sub, Person *per)
{
  size_t memory = N * sizeof(Person);
  Person *p = realloc(per, ALL_MEMORY_USED_BY_STUDENTS + memory);
  per = NULL;
  if (p == NULL)
  {
    printf("ошибка выделения памяти \n");
    return NULL;
  }
  ALL_MEMORY_USED_BY_STUDENTS += memory;

  for (int i = already_gen; i < already_gen + N; i++)
  {
    Person stud;

    // инициализация студента
    unsigned char len = get_random(min_sub, max_sub);
    christening(&stud);       // имянаречение
    get_subjects(len, &stud); // предметонаречение
    get_BirthDay(&stud);      // датанаречение
    get_group(&stud);         // групонаречение

    p[i] = stud;
  }
  already_gen += N;

  return p;
}

void get_size()
{
  printf("%u\n", ALL_MEMORY_USED_BY_STUDENTS);
  return;
}

void print_students(int N, Person *students)
{

  for (size_t i = 0; i < N; i++)
  {
    Person stud = students[i];
    printf("%s %s %s ", stud.name, stud.surname, stud.middlename);
    printf("%d.%d.%d group:%s\n", stud.BD.day, stud.BD.month, stud.BD.year, GROUPS[stud.number_group]);
    char *AssessmentType;
    for (size_t j = 0; j < stud.subjects_count - 1; j++)
    {
      char n = stud.subjects[j]; // номер предмета

      if (links_on_sub[n].assessment_type == 0)
        AssessmentType = "EXAM";
      else if (links_on_sub[n].assessment_type == 1)
        AssessmentType = "TEST";
      else if (links_on_sub[n].assessment_type == 2)
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

void init()
{
  char *locale = setlocale(LC_ALL, "Rus");
  seed = time(NULL) + 1;
  srand(seed);
  if (!initialization_subjects())
  {
    perror("ошибка инициализации\n");
    return;
  }
  if (!initialization_groups())
  {
    perror("ошибка инициализации\n");
    return;
  }
}

int main()
{
  printf("%d", sizeof(Person));
  char buffer[100];
  Person *students = NULL;
  init();

  printf("\nВведите команду(чтобы закончить напишите exit): ");
  while (fgets(buffer, sizeof(buffer), stdin) != NULL)
  {

    // Читает строку до ENTER
    buffer[strcspn(buffer, "\n")] = 0;

    if (!strncmp(buffer, "gen", 3))
    {

      if (boyer_moore(buffer, "-min-disciplines") != -1)
      {
        char start = 16 + 1 + boyer_moore(buffer, "-min-disciplines");
        int n = strtol(buffer + start, NULL, 10);
        printf("%d = min\n", n);
        if (n >= 0 && SUBJECTS_MAX >= n)
        {
          SUBJECTS_MIN = n;
        }
      }
      if (boyer_moore(buffer, "-max-disciplines") != -1)
      {
        char start = 16 + 1 + (boyer_moore(buffer, "-max-disciplines"));
        int n = strtol(buffer + start, NULL, 10);
        printf("%d max\n", n);
        if (n >= SUBJECTS_MIN && SUBJECTS_MAX >= n)
        {
          SUBJECTS_MAX = n;
        }
      }

      char **end;
      int num = strtol(buffer + 3, end, 10);

      if ((num + already_gen) > MAX_NUMBER_FOR_GEN)
      {
        printf("слишком много\n");
      }
      else
      {
        students = gen(num, SUBJECTS_MIN, SUBJECTS_MAX, students);
        if (students != NULL)
        {
          printf("[+] успешно создали %d\n", num);
        }
        else
        {
          perror("[-] ошибка\n");
        }
      }
    }
    // Возможность вызвать print_students N
    else if (!strncmp(buffer, "print_students", 14))
    {
      if (already_gen == 0)
      {
        printf("нет студентов\n");
      }
      else
      {
        char **end;
        int num = strtol(buffer + 15, end, 10);

        if (num > already_gen || num == -1)
        {
          num = already_gen;
        }
        print_students(num, students);
      }
      // printf("print stud %d\n", num);
    }
    // Возможность вызвать clean
    else if (!strncmp(buffer, "clean", 5))
    {
      if (ALL_MEMORY_USED_BY_STUDENTS == 0)
      {
        printf("всё уже почищено\n");
      }
      else
      {
        free(students);
        students = NULL;
        ALL_MEMORY_USED_BY_STUDENTS = 0;
        already_gen = 0;
        printf("произошла дизинтеграция студентов\n");
      }
    }

    else if (!strncmp(buffer, "exit", 4))
    {

      if (ALL_MEMORY_USED_BY_STUDENTS != 0)
      {
        free(students);
      }
      return 0;
    }
    else if (!strncmp(buffer, "get_size", 8))
    {
      get_size();
    }

    else
    {
      printf("команда не распознана\n");
    }
    // return 1;
  }
}
