#include "nm.h"

typedef struct ar_header
{
	char	file_name[16];
	char	file_modif[12];
	char	ownID[6];
	char	grpID[6];
	char	file_mode[8];
	char	file_size[10];
	char	end_char[2];
}			ar_head;

typedef struct s_ar_data
{
	char	sign[8];
	ar_head header;
	int		nb_sym;
	int		first_offset;
}				t_ar;

void	print_value(ar_head *har)
{
	int i;

	i = 0;
	ft_printf("\nfile name = ");
	while (i < 16)
		ft_printf("%c", har->file_name[i++]);
	i = 0;
	ft_printf("\nFile_timestemp = ");
	while (i < 12)
		ft_printf("%c", har->file_modif[i++]);
	i = 0;
	ft_printf("\nownId = ");
	while (i < 6)
		ft_printf("%c", har->ownID[i++]);
	i = 0;
	ft_printf("\ngrpId = ");
	while (i < 6)
		ft_printf("%c", har->grpID[i++]);
	i = 0;
	ft_printf("\nfile mode = ");
	while (i < 8)
		ft_printf("%c", har->file_mode[i++]);
	i = 0;
	ft_printf("\nfile_size = ");
	while (i < 10)
		ft_printf("%c", har->file_size[i++]);
	ft_printf("\nend_char = ");
	ft_printf("[%#04x][%#04x]", har->end_char[0], har->end_char[1]);
	ft_printf("\n");
}

//handle a systeme V (GNU library)

void	interp_ar(t_nmdata *data)
{
	//besoin de lire en endian inversé
	t_ar		*ar;
	t_nmdata	ar_data;
	ar_head		*header;
	char		*name_table;
	int			nb_sym;
	int			i;
	int			len;
	void		*mychar;
	int			valid;

	ar = data->file;
	i = 0;
	//If system V archive
	if (ft_strncmp(ar->header.file_name, "/", 16))
	{
		// "/" en nom de fichier indique que le fichier contient la table de recherche de symboles
		// ft_putnstr_fd(ar->header.file_name, 16, 1);
		//table de recherche en 3 parties
		//partie 1: nombre de symboles
		if (ft_endian() == LITTLE_ENDIAN)
			nb_sym = ar->nb_sym;
		else
			nb_sym = ft_r_endian_int(ar->nb_sym);

		// ft_printf("nm sym = %d\n", nb_sym);
		//partie 2: un ensemble d'offset de header_files des fichier où apparaisse les symboles 
		len = nb_sym * sizeof(int);
		//partie 3 : un ensemble de chaine de caracteres,  les noms des symboles (dans le meme ordre que les offsets)
		while (i < nb_sym)
		{
			len += ft_strlen((char*)(&(ar->first_offset)) + len) + 1;
			i++;
		}
		//gerer la liste "//" (liste des noms de symboles de plus de 16 caracteres)
		ar = (t_ar*)((char *)&(ar->first_offset) + len);
		// ft_putnstr_fd(ar->header.file_name, 16, 1);
		mychar = ar;
		while (*(char *)mychar == '\0')
			mychar++;
		
		if (((char*)mychar)[1] == '/')
		{
			i = 0;
			header = mychar;
			mychar += sizeof(ar_head);
			name_table = mychar;
			mychar += ft_natoi((char *)&header->file_size, 10);
		}
		header = mychar;
		while (((long)header - (long)ar) < data->ar_size)
		{
			i = 0;
			if (ft_natoi(header->file_size, 10) == 0)
				return ;
			mychar = header;
			ft_printf("\n");
			if (header->file_name[i] == '/')
				ar_data.file_name = name_table + ft_natoi(&header->file_name[1], 15);
			else
				ar_data.file_name = header->file_name;
			//affiche le nom du fichiers
			ft_putuntil_fd(STDOUT_FILENO, ar_data.file_name,'/');
			ft_printf(":\n");
			ar_data.file = (mychar + sizeof(ar_head));
			ar_data.ehdr = ar_data.file;
			ar_data.fd = data->fd;
			ar_data.is_ar = 1;
			valid = ft_ehdr(&ar_data);
			if (ar_data.ehdr->e_phoff != 0 && valid)
		    	ar_data.phdr = ar_data.file + ar_data.ehdr->e_phoff + (ar_data.ehdr->e_phnum * ar_data.ehdr->e_phentsize);
			if (valid)
				ft_section(&ar_data);
			mychar += (long)(ft_natoi(header->file_size, 10) + sizeof(ar_head));
			header = mychar;
		}
	}
}	