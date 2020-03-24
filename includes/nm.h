#ifndef NM_H
# define NM_H
# include "elf.h"
# include "libft.h"
# include <sys/mman.h>
# include <sys/stat.h>

typedef struct  sym_list
{
	unsigned char	*name;
	unsigned long	value;
	char			type;
	unsigned int	sec_ndx;
	int				bind;
	int				T;
	void			*next;
}               t_sym_list;

typedef struct	s_nmdata
{
	void		*file;
	char		*file_name;
	int			fd;
	Elf64_Ehdr	*ehdr;
	Elf64_Phdr	*phdr;
	Elf64_Shdr	*shdr;
	char		*strtab;
	char		*sh_strtab;
}				t_nmdata;

typedef struct section_index
{
	int symtab;
	int strtab;
	int shstrtab;
	int bss;
	int data;
	int text;
}               t_sec_index;

typedef struct section_offset
{
	void *symtab;
	void *strtab;

}       s_off;

/*																			 *\
** --------------------------------------------------------------------------**
** -------------------------------- PROTOTYPES ------------------------------**
** --------------------------------------------------------------------------**
\*																			 */	

int			get_next_xbytes(int fd, void **bytes, unsigned int x);
int			ft_ehdr(t_nmdata *data);
int			ft_phdr(t_nmdata *data);
int			ft_section(t_nmdata *data);
int			ft_symbol(t_nmdata *data, t_sec_index index);
t_sym_list	*ft_lst_snew(Elf64_Sym *sym, char *strtab);
void		ft_lst_sadd_back(t_sym_list **lst, t_sym_list *new);
void		symb_sort(t_sym_list **lst);
int			str_endwith(const char *str, const char *buf);

#endif