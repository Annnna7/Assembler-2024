#include<iostream>
#include<string>
using namespace std;

int main() {
    double a, b, c;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input c: ";
    cin >> c;
    double res;
    int zm = 0;
    const double const_6 = 6, const_2 = 2, const_3 = 3;
    //(6 * a - b + c / 2) / (c + 3a / b)
    __asm {
        finit

        ; вычисление числител€

        fld qword ptr[a];          ST(0) = a
        fmul qword ptr[const_6];   ST(0) = 6 * a
        fsub qword ptr[b];         ST(0) = 6 * a - b
        fld qword ptr[c];          ST(0) = c;                   ST(1) = 6 * a - b
        fdiv qword ptr[const_2];   ST(0) = c / 2                ST(1) = 6 * a - b
        faddp  st(1), st;          ST(0) = 6 * a - b + c / 2;

        ; вычисление знаменател€

            fld qword ptr[a];        ST(0) = a, ST(1) = 6 * a - b + c / 2
            fmul qword ptr[const_3]; ST(0) = 3 * a, ST(1) = 6 * a - b + c / 2
            fld qword ptr[b];        ST(0) = b, ST(1) = 3 * a, ST(2) = 6 * a - b + c / 2
            ftst; сравниваем st(0) = b и 0
            fstsw ax; записываем содержимое SWR в регистр ј’
            sahf; запись флагов из ax в flags
            jz error_zf; если знаменатель = 0
            fdivp st(1), st;           ST(0) = 3 * a / b, ST(1) = 6 * a - b + c / 2
            fadd qword ptr[c];         ST(0) = 3 * a / b + c, ST(1) = 6 * a - b + c / 2

            ; проверка знаменател€ и деление

            ftst; сравниваем st(0) и 0
            fstsw ax; записываем содержимое SWR в регистр ј’
            sahf; запись флагов из ax в flags
            jz error_zf; если знаменатель = 0
            fdivp st(1), st; st(0) = (6 * a - b + c / 2) / (c + 3a / b)
            jmp m3

            error_zf :
        mov zm, 1
            jmp m3

            m3 :
        fstp res
    }
    if (zm == 0) {
        cout << "Answer asm: " << res << endl;
        cout << (6 * a - b + c / 2) / (c + 3 * a / b) << endl;
    }
    if (zm == 1) cout << "division by zero";
    return 0;
}
