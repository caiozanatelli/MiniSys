define(`ler', `INP $1')
define(`escrever', `OUT $1')

define(`program', `')
define(`begin', `')

define(`int', `builtin(`pushdef', `DC_VAR', `$1 DC $2')')dnl

define(`end', `HLT
f(`DC_VAR')')

define(`end_program', `END')
define(`end_se', `LBL_JMP builtin(`popdef', `LBL_JMP')dnl')dnl

define(`se', `LAD $1
SUB $3
ifelse(
	`$2', `menor', `JGZ LBL_JMP 
JZE LBL_JMP',
	`$2', `menor_igual', `JGZ LBL_JMP',
	`$2', `maior', `JLZ LBL_JMP
JZE LBL_JMP',
	`$2', `maior_igual', `JLZ LBL_JMP',
	`$2', `igual', `JZE LBL_JMP'
)
')dnl

pushdef(`LBL_JMP', `Z')dnl
pushdef(`LBL_JMP', `Y')dnl
pushdef(`LBL_JMP', `X')dnl

define(`lad', `LAD $1')
define(`sad', `SAD $1')
define(`add', `ADD $1')
define(`sub', `SUB $1')
define(`jump', `JMP $1')
define(`jgz', `JGZ $1')
define(`jlz', `JLZ $1')
define(`jze', `JZE $1')
define(`lxd', `LXD $1')
define(`sxd', `SXD $1')
define(`lax', `LAX')
define(`sax', `SAX')
define(`lcd', `LCD $1')
define(`jcc', `JCC')
define(`cal', `CAL $1')
define(`return', `RET')
define(`lai', `LAI')
define(`sai', `SAI')

