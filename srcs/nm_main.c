#include "nm.h"
	   #include <sys/types.h>


//TODO initialiser la structure ehdr + ajouter condition dans gnxb pour malloc si null
int main(int ac, char **av)
{
	t_nmdata	data;
	struct stat file_stat;
	int			valid;

	valid = 0;
	data = (t_nmdata){};
	if (ac == 1)
		data.file_name = "a.out"; // a tester
	else
		data.file_name = av[1];
	if ((data.fd = open(data.file_name, O_RDONLY)) < 0)
		return (ft_printf("nm: '%s': No such file\n", data.file_name));
	if (fstat(data.fd, &file_stat) == -1)
		ft_printf("fstat_failed\n");
	else if (S_ISDIR(file_stat.st_mode))
	{
		ft_printf("nm: Warning: '%s' is a directory\n", data.file_name);
		return (0);
	}
	data.file = mmap(NULL, file_stat.st_size, PROT_READ , MAP_SHARED, data.fd, 0);
	if (data.file != MAP_FAILED)
	{
		if ((*(unsigned char *)data.file == ELFMAG0 && *((unsigned char *)data.file + 1) == ELFMAG1 && *((unsigned char *)data.file + 2) == ELFMAG2 && *((unsigned char *)data.file + 3) == ELFMAG3))
		{
			data.ehdr = data.file;
			valid = ft_ehdr(&data);
			if (data.ehdr->e_phoff != 0 && valid)
				ft_phdr(&data);
			if (valid)
				ft_section(&data);
		}
		else if (ft_strncmp((char *)data.file, "!<arch>", 7) == 0)
		{
			ft_printf("ar archive\n");
			
		}
		else if ((*(unsigned char *)data.file == 0xFE  && *((unsigned char *)data.file + 1) == 0xED && *((unsigned char *)data.file + 2) == 0xFA && *((unsigned char *)data.file + 3) == 0xCE))
			ft_printf("Mach-o 32bits format\n");
		else if ((*(unsigned char *)data.file == 0xFE  && *((unsigned char *)data.file + 1) == 0xED && *((unsigned char *)data.file + 2) == 0xFA && *((unsigned char *)data.file + 3) == 0xCF))
			ft_printf("Mach-o 64bits format\n");
		else
			ft_printf("nm: %s: file format not recognized\n", data.file_name);
	}
	munmap(data.file, file_stat.st_size);
	wrdestroy();
	return (0);
}