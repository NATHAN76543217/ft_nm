#include "nm.h"



static	t_sym_list	*swap(t_sym_list *ptr1, t_sym_list *ptr2)
{
	t_sym_list	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

void	symb_sort(t_sym_list **lst)
{
	t_sym_list	**list;
	t_sym_list	*lste;
	t_sym_list	*tmp;
	int			sorted;

	sorted = 0;
	if (lst == NULL || *lst == NULL)
		return ;
	while (sorted != 1)
	{
		sorted = 1;
		list = lst;
		while ((*list) != NULL && (*list)->next != NULL)
		{
			lste = *list;
			tmp = lste->next;
			if (ft_strcmp((char *)lste->name, (char *)tmp->name) > 0)
			{
				*list = swap(lste, tmp);
				sorted = 0;
			}
			list = (t_sym_list **)&(*list)->next;
		}
	}
}

void    ft_lst_sadd_back(t_sym_list **lst, t_sym_list *new)
{
	t_sym_list *one;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		one = *lst;
		while (one->next != NULL)
			one = one->next;
		one->next = new;
	}
	
}

t_sym_list *ft_lst_snew(Elf64_Sym *sym, char *strtab)
{
	t_sym_list *lst;

	lst = wrmalloc(sizeof(t_sym_list));
	lst->name = (unsigned char *)(strtab + sym->st_name);
	lst->type = ' ';
	lst->bind = ELF64_ST_BIND(sym->st_info);
	lst->T = ELF64_ST_TYPE(sym->st_info);
	lst->value = sym->st_value;
	lst->sec_ndx = sym->st_shndx;
	lst->next = NULL;
	return (lst);
}