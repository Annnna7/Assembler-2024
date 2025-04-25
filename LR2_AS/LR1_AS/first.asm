.686P
.MODEL FLAT, C

.DATA

.CODE

calcSumm PROC C a:Byte, b:Byte
xor     eax,eax
add     al,a
add     al,b
jnc     m1      ;если нет переноса, то перейти на m1
adc     ah,0    ;в ax сумма с учётом переноса
m1:
ret
calcSumm ENDP


END 
