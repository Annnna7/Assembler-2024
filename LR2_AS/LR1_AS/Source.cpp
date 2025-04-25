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
        mov eax, a; ������ � eax �������� a
        mov ebx, b; ������ � ebx �������� b
        mov ecx, c; ������ � ecx �������� c

        imul eax, 3; 3 * a
        jo error_of; ������ ������������
        ; ��������� � �������
        cdq
        idiv ebx; 3 * a / b
        add eax, ecx; < eax >= 3 * a / b + c
        jz error_zf; ������ ������� �� ����
        jo error_of; ������ ������������

        push eax; � ����� c + 3 * a / b

        mov eax, a
        imul eax, 6; 6 * a
        jo error_of; ������ ������������
        sub eax, ebx; < eax >= 6 * a - b
        jo error_of; ������ ������������
        mov ebx, eax; < ebx >= 6 * a - b
        mov eax, c; eax = c
        mov ecx, 2; ecx = 2
        cdq
        idiv ecx; eax = c / 2
        add eax, ebx; < eax >= 6 * a - b + c / 2
        jo error_of; ������ ������������

        ; ��������� � �������
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
