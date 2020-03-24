#include "nm.h"




//revoir les types des symboles
//comparer avec d'autres travaux
//test work : ../lib/x86_64-linux-gnu/libpthread.so.0
//../lib/x86_64-linux-gnu/libpthread-2.28.so:

void    ft_nm(t_nmdata *data, t_sym_list *lst)
{
	symb_sort(&lst);

	while (lst != NULL)
	{

		if (*(lst->name) != '\0' && (lst->value != 0 || (lst->value == 0 && (lst->type == 't' || lst->type == 'T' || lst->type == 'A' || lst->type == 'n' || lst->type == 'b'))))
		{
			// printf("T = %d | B = %d |\n", lst->T, lst->bind);
			// printf(" sname = %s | sh_flag = %lu\n", data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, data->shdr[lst->sec_ndx].sh_flags);
			// ft_printf("sec nxd = %d\n ", lst->sec_ndx); 
			// if (lst->type != 'A' && lst->type != 'U')
				// ft_printf("| SHT =  %d\n", data->shdr[lst->sec_ndx].sh_type);
			printf("%016x %c %s\n", (unsigned int)lst->value, lst->type, lst->name);
		}
		else if (*(lst->name) != '\0' && lst->value == 0)
		{
			// printf("T = %d | B = %d |\n", lst->T, lst->bind);
			// printf(" sname = %s | sh_flag = %lu\n", data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, data->shdr[lst->sec_ndx].sh_flags);
			// ft_printf("sec nxd = %d\n ", lst->sec_ndx); 
			// if (lst->type != 'A' && lst->type != 'U' )
				// ft_printf("| SHT =  %d\n", data->shdr[lst->sec_ndx].sh_type);
			printf("%16s %c %s\n", "", lst->type, lst->name);
		}
		lst = lst->next;
	}
}

void	ft_bind(t_sym_list *lst)
{
	if (lst->bind == STB_WEAK)
	{
		if (lst->T == STT_OBJECT)
			lst->type = 'v';
		else 
			lst->type = 'w';
		(lst->value != 0 && lst->type != 'i') ? (lst->type = ft_toupper(lst->type)) : 0;
	}
	else if (lst->bind == STB_GLOBAL)
		(lst->type != 'i') ? (lst->type = ft_toupper(lst->type)) : 0;
	else if (lst->bind == STB_LOCAL)
		lst->type = ft_tolower(lst->type);

}

void	find_type(t_nmdata *data, t_sym_list *lst)
{
	//relocation for I
	if(lst->sec_ndx == SHN_UNDEF)
		lst->type = 'U';
	else if(lst->sec_ndx == SHN_ABS)
		lst->type = 'A';
	else if(lst->sec_ndx == SHN_COMMON)
		lst->type = 'C';
	else if(data->shdr[lst->sec_ndx].sh_flags == SHF_ALLOC)
		lst->type = 'r';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_PROGBITS)
	{
		if (ft_strncmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".gnu.warning.pthr", 17) == 0)
			lst->type = 'n';
		else if (ft_strncmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".debug", 6) == 0)
			lst->type = 'n';
		else if (lst->T == STT_OBJECT)
			lst->type = 'd';
		else if (lst->T == STT_GNU_IFUNC)
			lst->type = 'i';
		else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".data") == 0)
			lst->type = 'd';
		// else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".text") == 0)
			// lst->type = 't';
		else
			lst->type = 't';
	}
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_GROUP)
		lst->type = 'n';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_INIT_ARRAY)
		lst->type = 't';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_FINI_ARRAY)
		lst->type = 't';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_DYNAMIC)
		lst->type = 'd';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".bss") == 0)
		lst->type = 'b';
	else
		lst->type = '?';
	/*else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".text") == 0)
		lst->type = 't';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name,".init") == 0)
		lst->type = 't';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name,".fini") == 0)
		lst->type = 't';
	
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".data") == 0)
		lst->type = 'd';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".got.plt") == 0)
		lst->type = 'd';
	else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".dynamic") == 0)
		lst->type = 'd';
	// else if (ft_strcmp(data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset + data->shdr[lst->sec_ndx].sh_name, ".rodata") == 0)
	else if (data->shdr[lst->sec_ndx].sh_flags == SHF_RO_AFTER_INIT)
		lst->type = 'r';
	else if (data->shdr[lst->sec_ndx].sh_type == SHT_PROGBITS && lst->type == ' ')
		lst->type = 't';*/
	if (str_endwith((char*)lst->name, ".c") == 1)
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
		ft_printf("nm: %s: no symbols\n", data->file_name);
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
	ft_nm(data, lst);
		return (0);
}
