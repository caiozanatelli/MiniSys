include(library.m4)dnl
program
int(A, 0)
int(B, 0)
int(C, 0)
begin
ler(A)
ler(B)
LAD A
SAD C
LAD B
SAD A
LAD C
SAD B
escrever(A)
escrever(B)
end
end_program
