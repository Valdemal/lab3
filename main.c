#include <stdio.h>
#include <stdint.h>
#include <windows.h>


int32_t get_bin_size(long n) {
    // Возвращает количество значащих бит в двоичной записи числа n
    int32_t i = 0;
    while (n) {
        n >>= 1;
        ++i;
    }
    return i;
}

void binary_output(long n) {
    // Выводит двоичную запись числа n
    if (n != 0) {
        long mask = 1 << (get_bin_size(n) - 1);
        for (; mask; mask >>= 1) {
            putchar(mask & n ? '1' : '0');
        }
    } else putchar('0');
}

long create_mask(int32_t n) {
    /* возвращает маску, содержащую n едениц в младщих разрядах */
    return ~(~0 << n);
}

long replace_occurrences(long n, long entry) {
    /* Возвращает число, которое является результатом замены нулями
     * вхождения двоичной записи entry в двоичную запись n*/
    if (n == 0) return 0;

    int32_t entry_bin_size = get_bin_size(entry);
    long mask = create_mask(entry_bin_size), n_copy = n;

    size_t size = 1 + (get_bin_size(n) - get_bin_size(entry));

    for (size_t i = 1; i <= size; i++) {
        if ((n & mask) == entry)
            n_copy &= ~mask;
        mask <<= 1;
        entry <<= 1;
    }

    return n_copy;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);//Подключение русского языка

    long n;
    printf("Введите длинное целое число:");
    scanf("%ld", &n);
    printf("Ваше число: %ld в 2 СС : ", n);
    binary_output(n);

    long result = replace_occurrences(n, 6);

    printf("\n");
    printf("Ваше число в 2 СС, в котором вхождения 110 заменены на 000: ");
    binary_output(result);
    printf("\n");
    printf("Ваше число в 10 СС в котором вхождения 110 заменены на 000: %ld\n",
           result);
}
