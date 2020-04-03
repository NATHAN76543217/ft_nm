#!/bin/bash

ABS_PATH_TO_FT_NM="/ft_nm/ft_nm"
FILE_EXCLUDE_LIST="ret_ft"
DIR_EXCLUDE_LIST="sys proc"

function test_file
{
	#compare les sortie d'un fichier passe en argument
	nm $1 > ret_nm 2> ret_nm
	$ABS_PATH_TO_FT_NM $1 > ret_ft 2> ret_ft
	nb=$(diff ret_nm ret_ft | wc | sed 's/^[ \t]*//' | cut -d ' ' -f1)
	diff ret_nm ret_ft >> diff_file
	if [ "$nb" != "0" ]
	then
		echo -e "\033[32mSome error on \033[4;30m$1\033[0m" && echo $1 >> files_failed && ((FAILED++))
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
	echo "Test des fichiers en cours..."
	for files in $@
	do
		echo "" > ret_ft
		echo "" > ret_nm
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
	echo -e "\033[34mRecuperation des fichiers en cours..."
	add_file "$PWD/"
	echo -e "Test des fichiers en cours...\033[0m"
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
			echo -n "" > ret_ft
			echo -n "" > ret_nm
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
	touch ret_nm		&& echo -n "" > ret_nm 
	touch ret_ft		&& echo -n "" > ret_ft 
	touch files_tested	&& echo -n "" > files_tested
	touch files_failed	&& echo -n "" > files_failed
	touch diff_file		&& echo -n "" > diff_file 
}

function start
{
	#test existance de ft_nm
	echo -e "\033[1;5;34m************FT_NM_TESTER***********\033[0mby Nlecaill"
	if [ ! -e $ABS_PATH_TO_FT_NM ]
	then echo "file $ABS_PATH_TO_FT_NM not found" && exit 1
	fi

	#test mode de tests
	if [ "$#" -ne 0 ]
	then
		for file in $@
		do
			#test validite des arguments
			if [ ! -e $file ]
			then
				echo "file : $file not found" && exit 1 
			fi
		done
		echo -e "\033[1;31mTest mode:\033[0m specified files"
		test_specified $@
	else
		echo -e "\033[1;31mTest mode:\033[0m all files"
		test_all $@
	fi
	echo -e "\033[31m$SUCCESS \033[34msuccess and \033[31m$FAILED \033[34mfailure on \033[31m$nb_file \033[34mfiles tested\033[0m"
	echo -e "\033[5;1;34mDONE\033[0m"
}

FICHIERS=""
SUCCESS=0
FAILED=0
start $@


