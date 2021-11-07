# Bash

Useful bash commands so I don't have to look at stack overflow to figure out what arguments I want for grep.

## Common commands

1. ls
	* List directory contents
	* -a, -l are useful
2. echo
	* Prints text to the terminal window
	* Useful in conjunction with > or >> to run something quickly
3. touch
	* Used to create a file
	* Can change time of file access/modification, even for symlinks
	* Look up man as needed
4. grep
	* Search a file, super useful so I'm gonna list everything from man here
	* grep [option(s)] pattern [file(s)]
	* -A number prints number lines before for context
	* -B number prints number lines after
	* -C number is basically -A number -B number
	* -e pattern matches regex
	* -q quiet mode, only prints on matches
5. mv
	* Move or rename directory
	* mv [-f | -i | -n] [-v] source target
6. locate
	* Locate a specific file or directory
	* The args are niche
7. cat
	* Read a file, create a file, and concatenate files
	* cat [-benstuv] [file ...]
	* Much more powerful, I'll create a separate file to go into it
8. head / tail
	* Read the start/end of a file
9. `> / | / >>`
	* `>` redirects stdout to a file
	* `>>` redirects stdout to a file but appends instead of replacing
	* `|` pipe, takes the output of the first command as the input to the next
10. chmod
	* Sets the file permissions flag on a file or folder
	* Tons of different permission levels, look up case by case
11. cp
	* Copies a file or directory from source to destination
	* cp [option(s)] current_name new_name

## More common commands that I use less/don't need explaining

1. man
	* Manual for command - man [command]
2. pwd
	* Print working directory
3. cd
	* Change directory
4. mkdir
	* Make a directory
5. less
	* View a file, less powerful cat
	* Lots or args
6. history
	* Lists the most recent commands
7. clear
	* Clears the screen
8. kill
	* Terminates a process
12. sleep
	* Delays a process

## Useful link

https://www.educative.io/blog/bash-shell-command-cheat-sheet
