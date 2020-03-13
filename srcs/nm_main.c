#include "nm.h"


//TODO initialiser la structure ehdr + ajouter condition dans gnxb pour malloc si null
int main(int ac, char **av)
{
	char *file;
	int fd;
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdr;

	ehdr = NULL;
	phdr = NULL;
	if (ac == 1)
	{
		file = wrmalloc(ft_strlen("a.out") + 1);
		ft_strlcpy(file, "a.out", ft_strlen("a.out") + 1);
	}
	else
		file = av[1];
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_printf("error open file\n"));
	ft_printf("%s: ", file);
	ft_ehdr(fd, ehdr);
	//if (ehdr->e_phoff != NULL)
//ft_phdr(fd, phdr);
	wrdestroy();
	return (0);
}