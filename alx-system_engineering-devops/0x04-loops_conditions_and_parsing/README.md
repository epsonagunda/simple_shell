#loop conditions and parsing

the for loop
-is the first of the three shell looping constructs.
syntax

for NAME [in LIST]; do COMMANDS; done

Examples
9.1.2.1. Using command substitution for specifying LIST items

[carol@octarine ~/articles] ls *.xml
file1.xml  file2.xml  file3.xml

[carol@octarine ~/articles] ls *.xml > list

[carol@octarine ~/articles] for i in `cat list`; do cp "$i" "$i".bak ; done

[carol@octarine ~/articles] ls *.xml*
file1.xml  file1.xml.bak  file2.xml  file2.xml.bak  file3.xml  file3.xml.bak

Using the content of a variable to specify LIST items

[carol@octarine ~/html] cat html2php.sh
#!/bin/bash
# specific conversion script for my html files to php
LIST="$(ls *.html)"
for i in "$LIST"; do
     NEWNAME=$(ls "$i" | sed -e 's/html/php/')
     cat beginfile > "$NEWNAME"
     cat "$i" | sed -e '1,25d' | tac | sed -e '1,21d'| tac >> "$NEWNAME"
     cat endfile >> "$NEWNAME"
done


operators

assignment

variable assignment
Initializing or changing the value of a variable

=
All-purpose assignment operator, which works for both arithmetic and string assignments.

var=27
category=minerals  # No spaces allowed after the "=".
Caution	
Do not confuse the "=" assignment operator with the = test operator.

#   =  as a test operator

if [ "$string1" = "$string2" ]
then
   command
fi

#  if [ "X$string1" = "X$string2" ] is safer,
#+ to prevent an error message should one of the variables be empty.
#  (The prepended "X" characters cancel out.)


arithmetic operators

+
plus

-
minus

*
multiplication

/
division

**
exponentiation

# Bash, version 2.02, introduced the "**" exponentiation operator.

let "z=5**3"    # 5 * 5 * 5
echo "z = $z"   # z = 125

modulo, or mod (returns the remainder of an integer division operation)

bash$ expr 5 % 3
2

Greatest common divisor

#!/bin/bash
# gcd.sh: greatest common divisor
#         Uses Euclid's algorithm

#  The "greatest common divisor" (gcd) of two integers
#+ is the largest integer that will divide both, leaving no remainder.

#  Euclid's algorithm uses successive division.
#    In each pass,
#+      dividend <---  divisor
#+      divisor  <---  remainder
#+   until remainder = 0.
#    The gcd = dividend, on the final pass.
#
#  For an excellent discussion of Euclid's algorithm, see
#+ Jim Loy's site, http://www.jimloy.com/number/euclids.htm.


# ------------------------------------------------------
# Argument check
ARGS=2
E_BADARGS=85

if [ $# -ne "$ARGS" ]
then
  echo "Usage: `basename $0` first-number second-number"
  exit $E_BADARGS
fi
# ------------------------------------------------------


gcd ()
{

  dividend=$1             #  Arbitrary assignment.
  divisor=$2              #! It doesn't matter which of the two is larger.
                          #  Why not?

  remainder=1             #  If an uninitialized variable is used inside
                          #+ test brackets, an error message results.

  until [ "$remainder" -eq 0 ]
  do    #  ^^^^^^^^^^  Must be previously initialized!
    let "remainder = $dividend % $divisor"
    dividend=$divisor     # Now repeat with 2 smallest numbers.
    divisor=$remainder
  done                    # Euclid's algorithm

}                         # Last $dividend is the gcd.


gcd $1 $2

echo; echo "GCD of $1 and $2 = $dividend"; echo


# Exercises :
# ---------
# 1) Check command-line arguments to make sure they are integers,
#+   and exit the script with an appropriate error message if not.
# 2) Rewrite the gcd () function to use local variables.

exit 0

+=
plus-equal (increment variable by a constant) [1]

let "var += 5" results in var being incremented by 5.

-=
minus-equal (decrement variable by a constant)

*=
times-equal (multiply variable by a constant)

let "var *= 4" results in var being multiplied by 4.

/=
slash-equal (divide variable by a constant)

%=
mod-equal (remainder of dividing variable by a constant)

Other Comparison Operators

integer comparison

-eq
is equal to

if [ "$a" -eq "$b" ]

-ne
is not equal to

if [ "$a" -ne "$b" ]

-gt
is greater than

if [ "$a" -gt "$b" ]

-ge
is greater than or equal to

if [ "$a" -ge "$b" ]

-lt
is less than

if [ "$a" -lt "$b" ]

-le
is less than or equal to

if [ "$a" -le "$b" ]

<
is less than (within double parentheses)

(("$a" < "$b"))

<=
is less than or equal to (within double parentheses)

(("$a" <= "$b"))

>
is greater than (within double parentheses)

(("$a" > "$b"))

>=
is greater than or equal to (within double parentheses)

(("$a" >= "$b"))



File test operators
Returns true if...

-e
file exists

-a
file exists

This is identical in effect to -e. It has been "deprecated," [1] and its use is discouraged.

-f
file is a regular file (not a directory or device file)

-s
file is not zero size

-d
file is a directory

-b
file is a block device


-c
file is a character device

device0="/dev/sda2"    # /   (root directory)
if [ -b "$device0" ]
then
  echo "$device0 is a block device."
fi

# /dev/sda2 is a block device.



device1="/dev/ttyS1"   # PCMCIA modem card.
if [ -c "$device1" ]
then
  echo "$device1 is a character device."
fi

# /dev/ttyS1 is a character device.

-p
file is a pipe

function show_input_type()
{
   [ -p /dev/fd/0 ] && echo PIPE || echo STDIN
}

show_input_type "Input"                           # STDIN
echo "Input" | show_input_type                    # PIPE

# This example courtesy of Carl Anderson.

-h
file is a symbolic link

-L
file is a symbolic link

-S
file is a socket

-t
file (descriptor) is associated with a terminal device

This test option may be used to check whether the stdin [ -t 0 ] or stdout [ -t 1 ] in a given script is a terminal.

-r
file has read permission (for the user running the test)

-w
file has write permission (for the user running the test)

-x
file has execute permission (for the user running the test)

-g
set-group-id (sgid) flag set on file or directory

If a directory has the sgid flag set, then a file created within that directory belongs to the group that owns the directory, not necessarily to the group of the user who created the file. This may be useful for a directory shared by a workgroup.

-u

set-user-id (suid) flag set on file

A binary owned by root with set-user-id flag set runs with root privileges, even when an ordinary user invokes it. [2] This is useful for executables (such as pppd and cdrecord) that need to access system hardware. Lacking the suid flag, these binaries could not be invoked by a non-root user.

	      -rwsr-xr-t    1 root       178236 Oct  2  2000 /usr/sbin/pppd
	      
A file with the suid flag set shows an s in its permissions.

-k
sticky bit set

Commonly known as the sticky bit, the save-text-mode flag is a special type of file permission. If a file has this flag set, that file will be kept in cache memory, for quicker access. [3] If set on a directory, it restricts write permission. Setting the sticky bit adds a t to the permissions on the file or directory listing. This restricts altering or deleting specific files in that directory to the owner of those files.

	      drwxrwxrwt    7 root         1024 May 19 21:26 tmp/
	      
If a user does not own a directory that has the sticky bit set, but has write permission in that directory, she can only delete those files that she owns in it. This keeps users from inadvertently overwriting or deleting each other's files in a publicly accessible directory, such as /tmp. (The owner of the directory or root can, of course, delete or rename files there.)

-O
you are owner of file

-G
group-id of file same as yours

-N
file modified since it was last read

f1 -nt f2
file f1 is newer than f2

f1 -ot f2
file f1 is older than f2

f1 -ef f2
files f1 and f2 are hard links to the same file

!
"not" -- reverses the sense of the tests above (returns true if condition absent).

Example 7-4. Testing for broken links

#!/bin/bash
# broken-link.sh
# Written by Lee bigelow <ligelowbee@yahoo.com>
# Used in ABS Guide with permission.

#  A pure shell script to find dead symlinks and output them quoted
#+ so they can be fed to xargs and dealt with :)
#+ eg. sh broken-link.sh /somedir /someotherdir|xargs rm
#
#  This, however, is a better method:
#
#  find "somedir" -type l -print0|\
#  xargs -r0 file|\
#  grep "broken symbolic"|
#  sed -e 's/^\|: *broken symbolic.*$/"/g'
#
#+ but that wouldn't be pure Bash, now would it.
#  Caution: beware the /proc file system and any circular links!
################################################################


#  If no args are passed to the script set directories-to-search 
#+ to current directory.  Otherwise set the directories-to-search 
#+ to the args passed.
######################

[ $# -eq 0 ] && directorys=`pwd` || directorys=$@


#  Setup the function linkchk to check the directory it is passed 
#+ for files that are links and don't exist, then print them quoted.
#  If one of the elements in the directory is a subdirectory then 
#+ send that subdirectory to the linkcheck function.
##########

linkchk () {
    for element in $1/*; do
      [ -h "$element" -a ! -e "$element" ] && echo \"$element\"
      [ -d "$element" ] && linkchk $element
    # Of course, '-h' tests for symbolic link, '-d' for directory.
    done
}

#  Send each arg that was passed to the script to the linkchk() function
#+ if it is a valid directoy.  If not, then print the error message
#+ and usage info.
##################
for directory in $directorys; do
    if [ -d $directory ]
	then linkchk $directory
	else 
	    echo "$directory is not a directory"
	    echo "Usage: $0 dir1 dir2 ..."
    fi
done

exit $?


#!/usr/bin/env As a Shebang
#! is called shebang
consists of a number sign and exclamation point character (#!)
for poratable across different UNIX like operating systems we use /usr/bin/env command as shebang






