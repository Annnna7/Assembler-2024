#include<iostream>
#include<string>
using namespace std;
int main()
{
    int a, b, c;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input c: ";
    cin >> c;
    int res;
    int zm = 0;
    __asm {
        mov zm, 0
        mov eax, a; кладем в eax значение a
        mov ebx, b; кладем в ebx значение b
        mov ecx, c; кладем в ecx значение c

        imul eax, 3; 3 * a
        jo error_of; ошибка переполнения
        ; готовимся к делению
        cdq
        idiv ebx; 3 * a / b
        add eax, ecx; < eax >= 3 * a / b + c
        jz error_zf; ошибка деление на ноль
        jo error_of; ошибка переполнения

        push eax; в стеке c + 3 * a / b

        mov eax, a
        imul eax, 6; 6 * a
        jo error_of; ошибка переполнения
        sub eax, ebx; < eax >= 6 * a - b
        jo error_of; ошибка переполнения
        mov ebx, eax; < ebx >= 6 * a - b
        mov eax, c; eax = c
        mov ecx, 2; ecx = 2
        cdq
        idiv ecx; eax = c / 2
        add eax, ebx; < eax >= 6 * a - b + c / 2
        jo error_of; ошибка переполнения

        ; готовимся к делению
        pop ebx; < ebx >= c + 3 * a / b
        cdq
        idiv ebx; < eax >= (6 * a - b + c / 2) / (c + 3 * a / b)

        jmp m3

        error_zf :
        mov zm, 1
            jmp m3

            error_of :
        mov zm, 2
            jmp m3

            m3 :
        mov res, eax
    }
    if (zm == 0) cout << "Answer asm: " + to_string(res);
    if (zm == 1) cout << "division by zero";
    if (zm == 2) cout << "owerflow";
    return 0;
}
