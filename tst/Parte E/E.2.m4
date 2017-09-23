include(library.m4)dnl
program
int(A, 0)
int(B, 0)
int(Q, 0)
int(D, 0)
begin
ler(A)
ler(B)
L se(A, maior_igual, B)
LAD A
SUB B
SAD A
inc(Q)
JMP L
end_se
escrever(Q)
end
end_program
