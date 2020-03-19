#include "nm.h"




//revoir les types des symboles
//comparer avec d'autres travaux

void    ft_nm(t_nmdata *data, t_sec_index index, t_sym_list *lst)
{
	symb_sort(&lst);
	while (lst != NULL)
	{
		// if (lst->T == STT_NOTYPE)
			// ft_printf("T = %d | B = %d | sname = %s\n", lst->T, lst->bind, data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name);
			// ft_printf("T = %d | B = %d\n", lst->T, lst->bind);
		if (*(lst->name) != '\0' && lst->value != NULL)
			printf("%016x %c %s\n", (unsigned int)lst->value, lst->type, lst->name);
		else if (*(lst->name) != '\0' && lst->value == NULL)
			printf("%16s %c %s\n", "", lst->type, lst->name);

		lst = lst->next;
	}
}

void	ft_bind(t_sym_list *lst)
{
	if (lst->bind == STB_WEAK)
		lst->type = 'v';
	else if (lst->bind == STB_GLOBAL)
		lst->type = ft_toupper(lst->type);
	else if (lst->bind == STB_LOCAL)
		lst->type = ft_tolower(lst->type);

}

void	find_type(t_nmdata *data, t_sym_list *lst)
{
	//relocation for I
	if(lst->sec_ndx == SHN_UNDEF)
		lst->type = 'U';
	else if(lst->sec_ndx == SHN_LORESERVE)
		lst->type = '?';
	else if(lst->sec_ndx == SHN_LOPROC)
		lst->type = '?';
	else if(lst->sec_ndx == SHN_HIPROC)
		lst->type = '?';
	else if(lst->sec_ndx == SHN_LIVEPATCH)
		lst->type = '?';
	else if(lst->sec_ndx == SHN_ABS)
		lst->type = 'A';
	else if(lst->sec_ndx == SHN_COMMON)
		lst->type = 'C';
	else if(lst->sec_ndx == SHN_HIRESERVE)
		lst->type = '?';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".text") == 0)
		lst->type = 't';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name,".init") == 0)
		lst->type = 't';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name,".fini") == 0)
		lst->type = 't';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".bss") == 0)
		lst->type = 'b';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".data") == 0)
		lst->type = 'd';
	if (str_endwith(lst->name, ".c") == 1)
		lst->name = data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset;
	ft_bind(lst);
}

int     ft_symbol(t_nmdata *data, t_sec_index index)
{
	Elf64_Sym *sym;
	int nb_entries;
	t_sym_list *lst;
	t_sym_list *new;

	if (index.symtab == 0)
	{
		ft_printf("symtab not found\n");
		return (0);
	}
	else if (index.strtab == 0)
	{
		ft_printf("strtab not found\n");
		return (0);
	}
	/*printf("symtab section_header is at offset : %lld\n", data->shdr[index.symtab].sh_offset);
	printf("strtab section_header is at offset : %lld\n", data->shdr[index.strtab].sh_offset);
	printf("strtab section have size of : %lld\n", data->shdr[index.strtab].sh_size);
	*/sym = data->file + data->shdr[index.symtab].sh_offset;
	// printf("symtab sizeof 1 entry : %lld\n", data->shdr[index.symtab].sh_entsize);
	nb_entries = data->shdr[index.symtab].sh_size / data->shdr[index.symtab].sh_entsize;
	// ft_printf("symtab nb_entries = %d\n", nb_entries);
	int i;
	i = 0;
	lst = NULL;
	while (i < nb_entries)
	{
		//printf("symbol name = %-25s\t%lld\n", (char *)(file + shdr[index.strtab].sh_offset + sym->st_name), ELF64_ST_TYPE(sym->st_info));
		if ((new = ft_lst_snew(sym, data->strtab)) == NULL)
			ft_printf("malloc error\n");
		find_type(data, new);
		ft_lst_sadd_back(&lst, new);
		sym += 1;
		i++;
	}
	ft_nm(data, index, lst);
		return (0);
}
