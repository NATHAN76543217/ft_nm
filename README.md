# ft_nm

Reproduction de la commande nm. (voir man nm)

ft_nm liste tout les symboles du fichier passé en parametre en affichant pour chacun son nom, son type ainsi que sa valeur.

Formats de fichier supportés : ELF64bits + achives ar (format system V).

# tester

Le script NM_TESTER.sh compare la sortie de ft_nm avec celle de la commande nm.

 ## Il y a deux modes de fonctionnement:

**-all files**:
        teste recursivement tout les fichiers.
        (ex: ../tester/nm_tester)
**-specified files**:
        teste uniquement les fichiers specifier en arguments
        (ex: ../tester/nm_tester file1 file2 file3 ...)

## plusieur fichiers de retours sont crées:

**-ret_ft:** comporte le resultat de la commande ft_nm du dernier test.
**-ret_nm:** comporte le resultat de la commande nm du dernier test.
**-files_tested:** comporte la liste de tout les fichiers testées
**-files_failed:** comporte la liste de tout les fichiers qui ont échouées.
**-diff_files:** comporte la liste des differences entre ret_nm et ret_ft pour tout les tests qui ont échoués. (commande diff).

Le champs ABS_PATH_TO_FT_NM="" doit contenir le chemin absolue vers le fichier ft_nm.

DIR_EXCLUDE_LIST comporte la liste des nom de repertoires a ne pas tester.
FILE_EXCLUDE_LIST comporte la liste des nom de fichiers a ne pas tester.

Les fichier avec un espace dans le nom sont supportées.
