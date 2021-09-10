#!/bin/bash

ABS_PATH_TO_FT_NM="/ft_nm/ft_nm"
FILE_EXCLUDE_LIST="dump_tested"
DIR_EXCLUDE_LIST="sys proc"

# colors/style
_BOLD="\033[1m"
_SLOW_BLINK="\033[5m"
_BLACK="\033[30m"
_RED="\033[31m"
_GREEN="\033[32m"
_YELLOW="\033[33m"
_BLUE="\033[34m"
_RESET="\033[0m"

function test_file
{
	#compare les sortie d'un fichier passe en argument
	nm $1 > dump_nm 2> dump_nm
	nm_return=`echo $?`
	$ABS_PATH_TO_FT_NM $1 > dump_tested 2> dump_tested
	tested_return=`echo $?`
	nb=$(diff dump_nm dump_tested | wc | sed 's/^[ \t]*//' | cut -d ' ' -f1)
	diff dump_nm dump_tested >> diff_file
	if [ "$nm_return" != "$tested_return" ]
	then
		echo "error result:" >> diff_file 
		diff nm_return tested_return >> diff_file
	fi
	if [ "$nb" != "0" ] || [ "$nm_return" != "$tested_return" ]
	then
		echo -e "${_GREEN}Some error on ${_YELLOW}${_SLOW_BLINK}$1${_RESET}" && echo $1 >> files_failed && ((FAILED++))
	else
		((SUCCESS++))
	fi 
}

function add_file
{
	#recupere les fichier du repertoire passé en parametre
	IFS=$'\n'
	new=`ls -p $1 | grep -v \/`
	for file in $new
	do
		file="$1$file"
		FICHIERS+="$file"$'\n'
	done
	rest=`ls -p $1 | grep \/`

	#puis pour chaque repertoire trouvé
	for dir in $rest
	do
		DoNotTest=0
		IFS=$' \t'
		#verifie si ils n'est pas a exclure
		for ex in $DIR_EXCLUDE_LIST
		do
			if echo "$dir" | grep "$ex" >/dev/null 2>&1
			then
				DoNotTest=1
			fi
		done
		#puis recupere sont contenue
		if [ "$DoNotTest" == "0" ]
		then
			add_file "$1$dir"
		fi
		IFS=$'\n'
	done 
}

function test_specified
{
	#test tout les fichier passe en arguments
	init
	echo -e "${_BLUE}Test des fichiers en cours...${_RESET}"
	for files in $@
	do
		echo "" > dump_tested
		echo "" > dump_nm
		test_file $file
		nb_file=$(($nb_file + 1))
		echo $file >> files_tested
	done
}

function test_all
{
	init
	nb_file_tested=0
	PWD=`pwd`
	if [ "$PWD" == / ]
	then
		PWD=""
	fi
	#recuperer tout les noms de fichier du repertoire courant et des sous repertoire
	echo -e "${_BLUE}Recuperation des fichiers en cours..."
	add_file "$PWD/"
	echo -e "Test des fichiers en cours...${_RESET}"
	IFS=$'\n'
	#test tout ces fichiers
	for file in $FICHIERS
	do
		DoNotTest=0
		IFS=$' \t'
	#et verifie qu'ils ne sont pas a exclure
		for ex in $FILE_EXCLUDE_LIST
		do
			if echo "$file" | grep "$ex" >/dev/null 2>&1
			then
				DoNotTest=1
			fi
		done
		if [ "$DoNotTest" == "0" ]
		then
			echo -n "" > dump_tested
			echo -n "" > dump_nm
			test_file $file
			nb_file=$(($nb_file + 1))
			echo $file >> files_tested
		fi
		IFS=$'\n'
	done
}

function init
{
	#creation des cinq fichiers de retour
	touch dump_nm		&& echo -n "" > dump_nm 
	touch dump_tested		&& echo -n "" > dump_tested 
	touch files_tested	&& echo -n "" > files_tested
	touch files_failed	&& echo -n "" > files_failed
	touch diff_file		&& echo -n "" > diff_file 
}

function start
{
	#test existance de ft_nm
	echo -e "${_BOLD}${_SLOW_BLINK}${_BLUE}m************FT_NM_TESTER***********${_RESET}by Nlecaill"
	if [ ! -e $ABS_PATH_TO_FT_NM ]
	then echo "file $ABS_PATH_TO_FT_NM not found" && exit 1
	fi

	#test mode de tests
	if [ "$#" -ne 0 ]
	then
		# for file in $@
		# do
		# 	test validite des arguments
		# 	if [ ! -e $file ]
		# 	then
		# 		echo "file : $file not found" && exit 1 
		# 	fi
		# done
		echo -e "${_RED}${_BOLD}Test mode:${_RESET} specified files"
		test_specified $@
	else
		echo -e "${_RED}${_BOLD}Test mode:${_RESET} all files"
		test_all $@
	fi
	echo -e "${_RED} ${SUCCESS} ${_BLUE}success and${_RED} ${FAILED} ${_BLUE}failure on${_RED} $nb_file ${_BLUE}files tested${_RESET}"
	echo -e "${_RED}${_BOLD}${_SLOW_BLINK}DONE${RESET}"
}

FICHIERS=""
SUCCESS=0
FAILED=0
start $@


