#include<iostream>
#include<string>
using namespace std;

double calculate(double a, double b) {
    double X;
    if (a > b) X = 3 * b / a - 100;

    else if (a == b) X = 205 / b;

    else X = (2 * a - 5 * b) / (1 - b);

    return X;
}

int main() {
    double a, b;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    double res = 0;
    int err = 0;
    const double const_no1 = -1, const_1 = 1, const_2 = 2, const_3 = 3, const_5 = 5, const_20 = 20, const_100 = 100, const_205 = 205;

    // X = 3*b/a - 100,             a > b
    // X = 205 / b,                 a = b
    // X = (2*a-5*b) / (1 - b),     a < b

    __asm {
        finit

        fld qword ptr[b];         st0 = b
        fld qword ptr[a];         st0 = a, st1 = b
        fcom; ���������� a � b
        fnstsw ax
        sahf
        ja a_bigger
        jb b_bigger
        ftst; ��������� b � 0
        fnstsw ax; ��������� ������� ������ ������������
        sahf; ���������� � ������� ������ ����������
        je error; ������� ���� b = 0
        fld qword ptr[const_205];          ST(0) = 205;     ST(1) = a    ST(2) = b
        fdiv qword ptr[b];                 ST(0) = 205 / c     ST(1) = a    ST(2) = b
        jmp m3; ������� ���������

        a_bigger :
        ; X = 3 * b / a - 100, a > b
            ;          ST(0) = a;                   ST(1) = b
            ftst; ��������� a � 0
            fnstsw ax; ��������� ������� ������ ������������
            sahf; ���������� � ������� ������ ����������
            je error; ������� ���� a = 0
            fld qword ptr[const_3];         ST(0) = 3, ST(1) = a, ST(2) = b
            fmulp st(2), st;                 ST(0) = a, ST(1) = 3 * b
            fdivp st(1), st;           ST(0) = 3 * b / a,
            fld qword ptr[const_100];         ST(0) = 100, ST(1) = 3 * b / a
            fsubp st(1), st;                 ST(0) = 3 * b / a - 100
            jmp m3; ������� ���������

            b_bigger :
        ; X = (2 * a - 5 * b) / (1 - b), a < b
            ;          ST(0) = a;                   ST(1) = b

            ; ���������� ���������

            fld qword ptr[const_5];          ST(0) = 5, ST(1) = a, ST(2) = b
            fmulp st(2), st;                 ST(0) = a, ST(1) = 5 * b
            fld qword ptr[const_2];          ST(0) = 2, ST(1) = a, ST(2) = 5 * b
            fmulp  st(1), st;                ST(0) = 2 * a, ST(1) = 5 * b
            fsubp st(1), st;                 ST(0) = 5 * b - 2 * a
            fld qword ptr[const_no1];        ST(0) = -1, ST(1) = 5 * b - 2 * a
            fmulp  st(1), st;                ST(0) = 2 * a - 5 * b

            ; ���������� �����������

            fld qword ptr[const_1];                ST(0) = 1, ST(1) = 2 * a - 5 * b
            fld qword ptr[b];          ST(0) = b, ST(1) = 1, ST(2) = 2 * a - 5 * b
            fsubp st(1), st;                 ST(0) = 1 - b, ST(1) = 2 * a - 5 * b

            ; �������� ����������� � �������

            ftst; ���������� st(0) � 0
            fstsw ax; ���������� ���������� SWR � ������� ��
            sahf; ������ ������ �� ax � flags
            je error; ���� ����������� = 0
            fdivp st(1), st; st(0) = (2 * a - 5 * b) / (1 - b)
            jmp m3

            error :
        mov err, 1
            jmp m3

            m3 :
        fstp res
    }
    if (err == 0) {
        cout << "Asm result: " << res << endl;
        cout << "C++ result: " << calculate(a, b);;
    }

    else if (err == 1) {
        cout << "Division by zero error" << endl;
    }

    return 0;
}
