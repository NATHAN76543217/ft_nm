#!/bin/bash
#trouver tout les fichiers objets de l'ordi
#les donner a NM_DIFF
#NM_DIFF va f

function test_file
{
	nm $1 > ret_nm 2> ret_nm
	/ft_nm/ft_nm $1 > ret_ft
	diff ret_nm ret_ft
	nb=$(diff ret_nm ret_ft | wc | sed 's/^[ \t]*//' | cut -d ' ' -f1)
	$(diff ret_nm ret_ft >> diff_file)
	if [ "$nb" == "0" ]
	then    echo "  no error"
	else    echo "  $nb different lines on $1"
	fi 
}

function add_file

{
	new="$(ls -p $2 | grep -v /)"
	for file in $new
	do
		file="$2$file"
		echo "$file"
		var+="$file "
	done
	rest=$(ls -p $2 | grep /)
	for dir in $rest
	do
		echo "IN: | $2 | $dir|"
		add_file "" "$2$dir"
	done 
}
#init
touch ret_nm
touch ret_ft
touch diff_file
echo " " > diff_file 
#recupere tout les noms de fichier du repertoire courant
nb_file=0
var=""
PWD=$(pwd)
#ici faire une comparaison avec la chaine de caractere car si c'est '/' alors il faut mettre une
if [ "$PWD" == / ];
 then
	PWD=""
fi
add_file "$var" "$PWD/"
echo "VAR = $var"
for variable in $var
do
	echo "$variable : "
	#bash /ft_nm/tester/NM_DIFF.sh $variable
	test_file $variable
	nb_file=$(($nb_file + 1))
	rm ret_nm
	rm ret_ft
	touch ret_nm
	touch ret_ft
done

echo "TEST ON REPERTORY:"
	test_file .
echo "$nb_file fichier testées"
echo "FINISH"

