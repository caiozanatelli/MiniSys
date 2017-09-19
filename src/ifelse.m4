define(`se', `LAD $1
SUB $3
ifelse(
	`$2', `menor', `JGZ LULA',
	`$2', `menor', `JLZ LULA',
	`$2', `igual', `JZE LULA'
)
builtin(`popdef', `LULA')
')dnl
pushdef(`LULA', `Z')
pushdef(`LULA', `Y')
pushdef(`LULA', `X')
