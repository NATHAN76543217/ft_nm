#include "nm.h"

void    ft_nm(t_sym_list *lst)
{
	symb_sort(&lst);
	while (lst != NULL)
	{
		if (*(lst->name) != '\0' && (lst->value != 0 || (lst->value == 0 && (lst->type == 't' || lst->type == 'T' || lst->type == 'A'
		|| lst->type == 'n' || lst->type == 'b' || lst->type == 'B' || lst->type == 'd' || lst->type == 'D'|| lst->type == 'W'
		|| lst->type == 'V' || lst->type == 'v' || lst->type == 'r' || lst->type == 'R' || lst->type == 'i'))))
		{
			if (lst->type == 'C')
				dprintf(1, "%016lx %c %s\n", lst->size, lst->type, lst->name);
			else
				dprintf(1, "%016lx %c %s\n", lst->value, lst->type, lst->name);
		}
		else if (*(lst->name) != '\0' && lst->value == 0)
				ft_printf("%16s %c %s\n", "", lst->type, lst->name);
		lst = lst->next;
	}
}

void	ft_bind(t_nmdata *data, t_sym_list *lst)
{
	if (lst->bind == STB_WEAK && lst->type != 'i')
	{
		if (lst->T == STT_OBJECT)
			lst->type = 'v';
		else 
			lst->type = 'w';
		(data->shdr[lst->sec_ndx].sh_type == SHT_PROGBITS || data->shdr[lst->sec_ndx].sh_type == SHT_NOBITS) ? (lst->type = ft_toupper(lst->type)) : 0;
	}
	else if (lst->bind == STB_GLOBAL)
		(lst->type != 'i') ? (lst->type = ft_toupper(lst->type)) : 0;
	else if (lst->bind == STB_LOCAL)
		lst->type = ft_tolower(lst->type);
	else if (lst->bind == STB_GNU_UNIQUE)
		lst->type = 'u';
}

void	find_type(t_nmdata *data, t_sym_list *lst)
{
	if(lst->sec_ndx == SHN_UNDEF)
		lst->type = 'U';
	else if(lst->sec_ndx == SHN_ABS)
		lst->type = 'A';
	else if(lst->sec_ndx == SHN_COMMON)
		lst->type = 'C';
	else if(data->shdr[lst->sec_ndx].sh_flags == SHF_ALLOC || ft_strncmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".rodata", 6) == 0)
		lst->type = 'r';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_PROGBITS)
	{
		if (ft_strncmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".gnu.warning", 12) == 0)
			lst->type = 'n';
		else if (ft_strncmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".debug", 6) == 0)
			lst->type = 'n';
		else if (lst->T == STT_OBJECT)
			lst->type = 'd';
		else if (lst->T == STT_GNU_IFUNC)
			lst->type = 'i';
		else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".data") == 0)
			lst->type = 'd';
		else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".tdata") == 0)
			lst->type = 'd';
		else
		{
				lst->type = 't';
		}
	}
	else if ( data->shdr[lst->sec_ndx].sh_type == SHT_NOBITS)
		lst->type = 'b';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_GROUP)
		lst->type = 'n';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_INIT_ARRAY)
		lst->type = 't';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_FINI_ARRAY)
		lst->type = 't';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_DYNAMIC)
		lst->type = 'd';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_PREINIT_ARRAY)
		lst->type = 'd';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".bss") == 0)
		lst->type = 'b';
	else
		lst->type = '?';

	if (str_endwith((char*)lst->name, ".c") == 1)
		lst->name = data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset;
	else if (str_endwith((char*)lst->name, ".cc") == 1 && lst->type == 'A')
		lst->name = data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset;
	ft_bind(data, lst);
}

int     ft_symbol(t_nmdata *data, t_sec_index index)
{
	Elf64_Sym *sym;
	int			nb_entries;
	t_sym_list *lst;
	t_sym_list *new;


	if (index.symtab == 0)
	{
		if (data->is_ar)
		{
			ft_putstr_fd("nm: ", 2);
			ft_putuntil_fd(2, data->file_name, '/');
			ft_putstr_fd(": no symbols\n", 2);
		}
		else
			ft_printf("nm: %s: no symbols\n", data->file_name);
		return (0);
	}
	else if (index.strtab == 0)
	{
		ft_printf("strtab not found\n");
		return (0);
	}
	sym = data->file + data->shdr[index.symtab].sh_offset;
	nb_entries = data->shdr[index.symtab].sh_size / data->shdr[index.symtab].sh_entsize;
	int i;
	i = 0;
	lst = NULL;
	while (i < nb_entries)
	{
		if ((new = ft_lst_snew(sym, data->strtab)) == NULL)
			ft_printf("malloc error\n");
		find_type(data, new);
		ft_lst_sadd_back(&lst, new);
		sym += 1;
		i++;
	}
	ft_nm(lst);
		return (0);
}
