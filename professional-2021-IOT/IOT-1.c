/* -----------------------------------------------------------------------------
В отделе контроля качества одной сельскохозяйственной фирмы присутствует
несколько линий, отвечающих за контроль содержания нитратов в продуктах.
Поступает строка (максимальная длина строки – 512 символов) – пакет показаний
с датчиков, перед показанием идет однозначный ID линии, на которой установлен
датчик, однозначный тип датчика, затем содержание нитратов (целое число от 20
до 5000), показания друг от друга отделяются символом $.

Необходимо вычислить среднее содержание нитратов с точностью до десятых для
каждой линии, вывести показания в следующем виде: сначала id линии, затем пробел
и среднее содержание нитратов, полученное с этой линии, с новой строки следующий
id и т.д., отсортировать по возрастанию id.
--------------------------------------------------------------------------------
Примеры:

ВВОД
224714$294617$071459$751765$761825$

ВЫВОД
0 1459.0
2 4665.5
7 1795.0
---------------------------------------
ВВОД
741435$751921$723151$311286$003399$093346$

ВЫВОД
0 3372.5
3 1286.0
7 2169.0
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

char line[513];

struct m_data {
    size_t count;
    size_t sum;
} channels[10] = {{0, 0}};

int main() {
    scanf("%s", line);

    char *p = line;
    while (*p) {
        size_t ch = *p - '0';
        p += 2;

        char *iter = p;
        for (iter; *iter && *iter != '$'; iter++);
        *iter = 0;

        channels[ch].count++;
        channels[ch].sum += atoi(p);

        p = iter + 1;
    }

    for (size_t i = 0; i < 10; i++) {
        if (channels[i].count)
            printf("%lu %.1f\n", i, (double) channels[i].sum / channels[i].count);
    }

    return 0;
}
