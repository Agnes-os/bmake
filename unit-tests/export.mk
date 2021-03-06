# $Id: export.mk,v 1.1.1.5 2020/09/28 01:27:05 sjg Exp $

UT_TEST=export
UT_FOO=foo${BAR}
UT_FU=fubar
UT_ZOO=hoopie
UT_NO=all
# believe it or not, we expect this one to come out with $UT_FU unexpanded.
UT_DOLLAR= This is $$UT_FU

.export UT_FU UT_FOO
.export UT_DOLLAR

.if !defined(.MAKE.PID)
.error .MAKE.PID must be defined
.endif
@=	at
%=	percent
*=	asterisk
${:U!}=	exclamation		# A direct != would try to run "exclamation"
				# as a shell command and assign its output
				# to the empty variable.
&=	ampersand

# This is ignored because it is internal.
.export .MAKE.PID
# These are ignored because they are local to the target.
.export @
.export %
.export *
.export !
.export &
# This is ignored because it is undefined.
.export UNDEFINED

BAR=bar is ${UT_FU}

.MAKE.EXPORTED+= UT_ZOO UT_TEST

FILTER_CMD?=	egrep -v '^(MAKEFLAGS|MALLOC_OPTIONS|PATH|PWD|SHLVL|_)='

all:
	@env | ${FILTER_CMD} | sort
