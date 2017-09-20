define(`lad', `LAD $1')dnl
define(`sad', `SAD $1')dnl
define(`add', `ADD $1')dnl
define(`sub', `SUB $1')dnl
define(`jump', `JMP $1')dnl
define(`jgz', `JGZ $1')dnl
define(`jlz', `JLZ $1')dnl
define(`jze', `JZE $1')dnl
define(`lxd', `LXD $1')dnl
define(`sxd', `SXD $1')dnl
define(`lax', `LAX')dnl
define(`sax', `SAX')dnl
define(`lcd', `LCD $1')dnl
define(`jcc', `JCC')dnl
define(`cal', `CAL $1')dnl
define(`return', `RET')dnl
define(`lai', `LAI')dnl
define(`sai', `SAI')dnl
dnl
dnl
dnl
pushdef(`LBL_PROG', `a')dnl
dnl
dnl
dnl
pushdef(`LBL_JMP', `w')dnl
pushdef(`LBL_JMP', `z')dnl
pushdef(`LBL_JMP', `y')dnl
pushdef(`LBL_JMP', `x')dnl
pushdef(`LBL_JMP', `v')dnl
pushdef(`LBL_JMP', `u')dnl
pushdef(`LBL_JMP', `t')dnl
pushdef(`LBL_JMP', `s')dnl
pushdef(`LBL_JMP', `r')dnl
pushdef(`LBL_JMP', `q')dnl
dnl
pushdef(`LBL_FOR', `l')dnl
pushdef(`LBL_FOR', `k')dnl
pushdef(`LBL_FOR', `j')dnl
pushdef(`LBL_FOR', `i')dnl
pushdef(`LBL_FOR', `h')dnl
pushdef(`LBL_FOR', `g')dnl
pushdef(`LBL_FOR', `f')dnl
pushdef(`LBL_FOR', `e')dnl
pushdef(`LBL_FOR', `d')dnl
pushdef(`LBL_FOR', `c')dnl
pushdef(`LBL_FOR', `b')dnl
dnl
dnl
dnl
define(`program', `JMP LBL_PROG
z DC 0
u DC 1')dnl
define(`begin', `LBL_PROG builtin(`popdef', `LBL_PROG')dnl')dnl
dnl
dnl
dnl
define(`ler', `INP $1')dnl
define(`escrever', `OUT $1')dnl
dnl
define(`soma', LAD $2
ADD $3
SAD $1)dnl
define(`sub', LAD $2
SUB $3
SAD $1)dnl
dnl
define(`inc', LAD $1
ADD u
SAD $1)dnl
define(`dec', LAD $1
SUB u
SAD $1)dnl
dnl
define(`clr', `LAD z
SAD $1')dnl
dnl
define(`int', `$1 DC $2')dnl
define(`end', `HLT')dnl
define(`end_program', `END')dnl
define(`end_se', `LBL_JMP builtin(`popdef', `LBL_JMP')dnl')dnl
dnl
dnl
dnl
define(`se', `LAD $1
SUB $3 
ifelse(`$2', `menor', `JGZ LBL_JMP 
JZE LBL_JMP', 
	`$2', `menor_igual', `JGZ LBL_JMP',
	`$2', `maior', `JLZ LBL_JMP
JZE LBL_JMP', 
	`$2', `maior_igual', `JLZ LBL_JMP',
	`$2', `igual', `JGE LBL_JMP'
JLE LBL_JMP)')dnl
dnl
dnl
dnl
define(`para', `JMP LBL_JMP
dnl
LBL_FOR DC $3 dnl
pushdef(`LBL_FOR_ARG', defn(`LBL_FOR'))dnl
popdef(`LBL_FOR')
dnl
LBL_FOR DC $2 dnl
pushdef(`LBL_FOR_ARG', defn(`LBL_FOR'))dnl
popdef(`LBL_FOR')
dnl
LBL_JMP builtin(`popdef', `LBL_JMP')dnl
LAD LBL_FOR_ARG
SAD $1
popdef(`LBL_FOR_ARG')dnl
SUB LBL_FOR_ARG
JGE LBL_JMP
ADD u
SAD $1 dnl
')dnl
dnl
define(`end_para', `LBL_JMP builtin(`popdef', `LBL_JMP')dnl')dnl
