#include<iostream>
#include<string>

int zm = 0;
int func(int* arr, int n, int b, int d) {
    __asm {
        xor esi, esi; ���������� ������� ������� � �������
        xor edi, edi; ������� ���������� ���������
        mov ebx, arr; ebx ��������� �� ������ �������
        mov ecx, n; ������� ����� �� ���� ��������� �������
        jecxz m3; ��������� ���� ����� ������� 0

        begin_loop:

        mov eax, [ebx + esi * 4]; ���������� ������� �������
            cmp eax, 0; ��������� a[i] � 0
            jl end_loop; ���� ������ �� ��������� ����
            mov edx, d; ���������� ��������� � d
            cmp eax, edx; ��������� a[i] � d
            jg end_loop; ���� ������, �� ��������� ����
            mov edx, b; ���������� ��������� � b
            cmp eax, edx; ��������� a[i] � b
            jl end_loop; ���� ������, �� ��������� ����
            inc edi; ������� ������������� �������,

            end_loop:

        inc esi; ��������� � ���������� ��������
            loop begin_loop; ��������� ���� ��� ���� ��������� �������
            jmp m3

            m3 :
        mov eax, edi; ���������� ���������� ���������
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
