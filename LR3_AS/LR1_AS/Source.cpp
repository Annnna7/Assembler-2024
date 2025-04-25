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
        mov ecx, a; < e�x >= a
        mov ebx, b; < ebx >= b
        cmp ecx, ebx; ��������� a � b
        jg l_bigger; ������� ���� a > b
        jl l_smaller; ������� ���� a < b

        ; a = b
        mov eax, 205; < eax >= 205
        or ebx, ebx; ��������� b � 0
        jz error_zf; ������ ������� �� ����
        cdq
        idiv ebx; eax = 205 / b
        jz error_zf; ������ ������� �� ����
        jo error_of; ������ ������������
        jmp m3; ������� �� ����� ���������

        l_bigger :

        or ecx, ecx; ��������� a � 0
            jz error_zf; ������ ������� �� ����
            xor eax, eax
            mov eax, 3; < eax >= 3
            imul ebx; eax = 3 * b
            jo error_of; ������ ������������
            cdq; ���������� ������� <edx:eax> = a
            ; ��������� �������� �������� ������
            idiv ecx; <eax> = 3 * b / a
            sub eax, 100; <eax> = 3 * b / a � 100
            jo error_of
            jmp m3; ������� �� ����� ���������

            l_smaller :

        mov eax, 1
            sub eax, ebx; eax = 1 - b
            or eax, eax; ��������� a � 0
            jz error_zf; ������ ������� �� ����
            push eax; � ����� 1 - b

            imul ecx, 2; ecx = ecx * 2
            jo error_of; ������ ������������
            imul ebx, 5; ebx = ebx * 5
            jo error_of; ������ ������������
            mov eax, ecx; eax = ecx
            sub eax, ebx; eax = 2 * a - 5 * b
            jo error_of; ������ ������������

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
