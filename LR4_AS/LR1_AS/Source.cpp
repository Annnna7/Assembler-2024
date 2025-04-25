#include<iostream>
#include<string>

int zm = 0;
int func(int* arr, int n, int b, int d) {
    __asm {
        xor esi, esi; подготовим регистр индекса в массиве
        xor edi, edi; счётчик количества элементов
        mov ebx, arr; ebx указывает на начало массива
        mov ecx, n; счётчик цикла по всем элементам массива
        jecxz m3; завершить если длина массива 0

        begin_loop:

        mov eax, [ebx + esi * 4]; определяем текущий элемент
            cmp eax, 0; сравнение a[i] и 0
            jl end_loop; если меньше то завершаем цикл
            mov edx, d; подготовка сравнения с d
            cmp eax, edx; сравнение a[i] и d
            jg end_loop; если больше, то завершаем цикл
            mov edx, b; подготовка сравнения с b
            cmp eax, edx; сравнение a[i] и b
            jl end_loop; если меньше, то завершаем цикл
            inc edi; элемент удовлетворяет условию,

            end_loop:

        inc esi; переходим к следующему элементу
            loop begin_loop; повторяем цикл для всех элементов массива
            jmp m3

            m3 :
        mov eax, edi; возвращаем количество элементов
    }
}
int main()
{
    std::cout << "Enter size: ";
    int n, b, d, result = 0;
    std::cin >> n;
    while (!std::cin || n < 0 || std::cin.peek() != '\n') {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Wrong size, try again.\n";
        std::cin >> n;
    }
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter a [" << i << "]: ";
        std::cin >> arr[i];
        while (!std::cin || std::cin.peek() != '\n') {
            std::cin.clear();
            while (std::cin.get() != '\n');
            std::cout << "Wrong input, try again.\nEnter a[" << i << "]: ";
            std::cin >> arr[i];
        }
    }
    std::cout << "Enter b: ";
    std::cin >> b;
    while (!std::cin || std::cin.peek() != '\n') {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Wrong input, try again.\n";
        std::cin >> b;
    }
    std::cout << "Enter d: ";
    std::cin >> d;
    while (!std::cin || std::cin.peek() != '\n') {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Wrong input, try again.\n";
        std::cin >> d;
    }

    result = func(arr, n, b, d);
    if (zm == 0) std::cout << "Result: " << result << std::endl;
    return 0;
}
