#ifndef NM_H
# define NM_H
# include "elf.h"
# include "libft.h"
int	get_next_xbytes(int fd, void **bytes, unsigned int x);
int	ft_ehdr(int fd, Elf64_Ehdr *ehdr);
int	ft_phdr(int fd, Elf64_Phdr *phdr);

#endif