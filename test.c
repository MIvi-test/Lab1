#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];

    printf("Введите текст (для выхода нажмите Ctrl+D или введите 'exit'):\n");

    // Цикл работает, пока fgets не вернет NULL (конец ввода)
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        
        // 1. Удаляем символ переноса строки '\n', который fgets добавляет в конец
        buffer[strcspn(buffer, "\n")] = 0;

        // 2. Условие выхода (по желанию)
        if (strcmp(buffer, "exit") == 0) break;

        // 3. Ваша логика обработки
        printf("Вы ввели: [%s]\n", buffer);
    }

    return 0;
}
