# The n option on mesg below says you're refusing write(1)
# messages.  We put this here to safeguard you against bad apples who
# might use the write program to send character streams that control
# your terminal against your wishes.  Remove "mesg n" at your own risk.

mesg n

alias gcc "gcc -I~csi402/utilites"
alias /usr/local/bin/gcc "/usr/local/bin/gcc -I~csi402/utilites"
alias g++ ~csi402/utilities/g++
alias /usr/local/bin/g++ ~csi402/utilities/g++
alias flex ~csi402/utilities/flex
alias /usr/local/bin/flex ~csi402/utilities/flex
alias yacc ~csi402/utilities/yacc
alias /usr/ccs/bin/yacc ~csi402/utilities/yacc
alias bison ~csi402/utilities/bison
alias /usr/local/bin/bison ~csi402/utilities/bison

alias logo logout
set ignoreeof
set mail=(5 /usr/spool/mail/$USER /var/mail/$USER )
/usr/ucb/stty dec 
#
# Give TERM a value just if this in not automatically assigned
if (`printenv TERM` == "" ) then
	setenv TERM vt100
endif
#
# let's get our termcap set right
#
switch ($TERM)
    case xterms:
    case xterm:
    case tvi950:
	breaksw
    case dialup:
# Your terminal type at home goes here    
#	setenv TERM tvi950
#	breaksw
    default:    
	setenv TERM vt100
	echo -n "Terminal type? ($TERM) "
        if ( ! ${?DT} ) then
		set newterm = $<
		if (x$newterm != x) setenv TERM $newterm
	endif
endsw
set nonomatch
eval `tset -Q -s $TERM`
unset nonomatch
echo Terminal type is $TERM
msgs -q
