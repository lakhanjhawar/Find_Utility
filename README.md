Find_Utility
============

Used C language 

Problem:
find is a powerful UNIX utility. Besides locating files in the given source directory and its
descendent directories, it can execute shell commands
on the located files. See its man page and try the
following commands to gain some experience.
find /dev –name null –type l //finds a link file named ‘null’ in /dev
find ~cs5352 –mtime +2 –mtime -5 –ls //lists files modified 2 or more days ago but no before 5 days
find $HOME –name core –ok mv {} /tmp \;
(The last command is cryptic and requires some explanation. 'find’ would search for files named ‘core’ in
the HOME and its descendent directories and execute the command ‘mv’ on all such files to move them to
/tmp. ‘ok’ means that shell would prompt the user for a response before executing the given command on
each file. {} (no spaces within parentheses) denotes the coll
ection of located files. ‘\;’ is needed
with ‘ok’;its purpose is not fully clear to me.)
Purpose of this project is to study UNIX file system by developing a similar but much simpler utility
. In brief, the summary syntax of our utility is as follows.
Find source selection cmd Like ‘find’,
Find should traverse the source directory recursively, examine
each entry of every descendent directory to verify if it meets the given
selection criterion, and finally arrange for the execution of the
command cmd on the selected entries. The source argument can be any pathname such as
dir, ./dir1, ~/dir1,
$HOME/dir1,
etc. Unlike, ‘find’,
Find
uses just one selection criterion and executes a single command. The
selection criterion has two parts; the firs
t part is a file attribute, which is
name, mtime,
or
user
, and the second part is a single corresponding argument. cmd is any single shell command compatible with the
selection criterion, and it is discussed later. The following examples should demonstrate use of
Find
.
Find /tmp –user lakhan –ls //find all files of user ‘lak
hani’ in /tmp folder or its descendents and do “ls” to
list them
Find . –mtime 5 –ls //find regular files in the current directory (.) and its descendents that were
modified in the last 5 days and list them
Find DIR –name core –mv -i /tmp // find files/directories named ‘core’ in DIR (and descendents) and
move them to /tmp interactively.
The source is a pathname and it may contain shell meta-characters such as $ or ~ (which you do not have to
process, because shell would resolve meta-characters,
if any, before executing Fi
nd). You may assume that
there is no syntax error in the ‘Find’ command line, i.e., all its components are given in the right order and
each command is complete. 
