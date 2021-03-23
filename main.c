#include <stdio.h>
#include <windows.h>


// Возвращает количество цифр в двоичной записи числа n
u_long get_bin_size(u_long n) {

    u_long i = 0;
    while (n) {
        n >>= 1;
        ++i;
    }
    return i;
}

/* возвращает маску, содержащую n едениц в младших разрядах */
u_long create_mask(u_long n) {
    return ~(~0 << n);
}

// Выводит двоичную запись числа n
void out_bin(u_long n) {
    if (n != 0) {
        u_long mask = 1 << (sizeof(u_long) * 8 - 1);
        while ((mask & n) == 0)
            mask >>= 1;

        while (mask) {
            putchar(mask & n ? '1' : '0');
            mask >>= 1;
        }
    } else
        putchar('0');
}

/* Замена в вхождения entry в двоичной форме числа n нулями*/
u_long get_replaced(u_long n, u_long entry) {
    if (n == 0)
        return 0;

    u_long entry_bin_size = get_bin_size(entry);
    u_long mask = create_mask(entry_bin_size);

    while (n >= entry) {
        if ((n & mask) == entry) {
            n &= ~mask;
            mask <<= entry_bin_size;
            entry <<= entry_bin_size;
        } else {
            mask <<= 1;
            entry <<= 1;
        }
    }

    return n;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);//Подключение русского языка

    u_long n;
    printf("Введите длинное целое число:");
    scanf("%ld", &n);
    printf("Ваше число: %ld в 2 СС : ", n);
    out_bin(n);
    printf("\n%d", get_bin_size(-1));
    u_long result = get_replaced(n, 6);
    printf("\n");
    printf("Ваше число в 2 СС, в котором вхождения 110 заменены на 000: ");
    out_bin(result);
    printf("\n");
    printf("Ваше число в 10 СС в котором вхождения 110 заменены на 000: %ld\n",
           result);
}
