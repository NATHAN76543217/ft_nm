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
			if (ft_strcmp(lste->name, tmp->name) > 0)
			{
				*list = swap(lste, tmp);
				sorted = 0;
			}
			list = (t_sym_list **)&(*list)->next;
		}
	}
}
	// t_sym_list *un;
	// t_sym_list *deux;
	// t_sym_list **zero;

	// int sorted;

	// un = lst;
	// sorted = 0;
	// if (!lst)
	// 	return (NULL);
	// if (lst->next == NULL)
	// 	return (lst);
	// un = lst;
	// deux = lst->next;
	// while (sorted == 0)
	// {
	// 	un = zero;
	// 	deux = un->next;
	// 	sorted = 1;
	// 	while (deux != NULL)
	// 	{
	// 		if (ft_strcmp(un->name, deux->name) > 0)
	// 		{
	// 			deux = un->next;
	// 			un->next = deux->next;
	// 			deux->next = un;
	// 			sorted = 0;
	// 		}
	// 		un = deux;
	// 		deux->next;
	// 	}
	// 	if (ft_strcmp(un->name, deux->name) > 0)
	// 	{
	// 		deux = un->next;
	// 		un->next = deux->next;
	// 		deux->next = un;
	// 		un = deux;
	// 		sorted = 0;
	// 	}
	// }


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
	lst->sec_ndx = (void*)sym->st_shndx;
	lst->next = NULL;
	return (lst);
}