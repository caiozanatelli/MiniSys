include(library.m4)dnl
program
int(A, 0)
int(B, 1)
begin
ler(A)
ler(B)
se(A, maior_igual, B)
escrever(A)
end_se
se(A, menor, B)
escrever(B)
end_se
end
end_program
