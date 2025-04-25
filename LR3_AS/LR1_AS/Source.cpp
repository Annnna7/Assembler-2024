#include<iostream>
#include<string>
using namespace std;
int main()
{
    int a, b;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    int res = 0;

    int zm = 0;
    __asm {
        mov zm, 0
        mov ecx, a; < eсx >= a
        mov ebx, b; < ebx >= b
        cmp ecx, ebx; сравнение a и b
        jg l_bigger; переход если a > b
        jl l_smaller; переход если a < b

        ; a = b
        mov eax, 205; < eax >= 205
        or ebx, ebx; сравнение b и 0
        jz error_zf; ошибка деление на ноль
        cdq
        idiv ebx; eax = 205 / b
        jz error_zf; ошибка деление на ноль
        jo error_of; ошибка переполнени€
        jmp m3; переход на конец программы

        l_bigger :

        or ecx, ecx; сравнение a и 0
            jz error_zf; ошибка деление на ноль
            xor eax, eax
            mov eax, 3; < eax >= 3
            imul ebx; eax = 3 * b
            jo error_of; ошибка переполнени€
            cdq; подготовка делени€ <edx:eax> = a
            ; обработка ситуации Ђчастное великої
            idiv ecx; <eax> = 3 * b / a
            sub eax, 100; <eax> = 3 * b / a Ц 100
            jo error_of
            jmp m3; переход на конец программы

            l_smaller :

        mov eax, 1
            sub eax, ebx; eax = 1 - b
            or eax, eax; сравнение a и 0
            jz error_zf; ошибка деление на ноль
            push eax; в стеке 1 - b

            imul ecx, 2; ecx = ecx * 2
            jo error_of; ошибка переполнени€
            imul ebx, 5; ebx = ebx * 5
            jo error_of; ошибка переполнени€
            mov eax, ecx; eax = ecx
            sub eax, ebx; eax = 2 * a - 5 * b
            jo error_of; ошибка переполнени€

            pop ebx; ebx = 1 - b

            cdq
            idiv ebx
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
