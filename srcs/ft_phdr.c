#include "nm.h"

int ft_phdr(int fd, Elf64_Phdr *phdr)
{

    if (get_next_xbytes(fd, (void **)&phdr, sizeof(Elf64_Phdr)) < 0)
	{
		wrdestroy();
		return (ft_printf("error\n"));
	}
    if (phdr->p_type == PT_NULL)
        ft_printf("segment NULL\n");
    return (0);
}
