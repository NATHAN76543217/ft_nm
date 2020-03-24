#!/bin/bash

#ci-dessous permet d'effacer les espaces et tabulations de debut de ligne
#sed 's/^[ \t]*//'
 for param in "$@"
 do
nm $param > ret_nm 2> ret_nm
/ft_nm/ft_nm $param > ret_ft
diff ret_nm ret_ft
nb=$(diff ret_nm ret_ft | wc | sed 's/^[ \t]*//' | cut -d ' ' -f1)
$(diff ret_nm ret_ft >> diff_file)
if [ "$nb" == "0" ]
then    echo "  no error"
else    echo "  $nb different lines on $param"
fi
 done 



