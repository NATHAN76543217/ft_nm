#include "nm.h"

//TODO initialiser la structure ehdr + ajouter condition dans gnxb pour malloc si null
//TODO virer fonction phdr (non uttilise)

int ft_ehdr(t_nmdata *data)
{
	if (data->ehdr->e_ident[EI_MAG0] == ELFMAG0 && data->ehdr->e_ident[EI_MAG1] == ELFMAG1 && data->ehdr->e_ident[EI_MAG2] == ELFMAG2 && data->ehdr->e_ident[EI_MAG3] == ELFMAG3)
	{
		if (data->ehdr->e_ident[EI_CLASS] == ELFCLASS64)
			return (1);
		else
			ft_printf("invalid architecture\n");
	}
	else
		ft_printf("is not a ELF file\n");
	return (0);
}

int		isElf(t_nmdata *data)
{
	if ((*(unsigned char *)data->file == ELFMAG0 && *((unsigned char *)data->file + 1) == ELFMAG1 && *((unsigned char *)data->file + 2) == ELFMAG2 && *((unsigned char *)data->file + 3) == ELFMAG3))
		return 1;
	else if (ft_strncmp((char *)data->file, "!<arch>\n", 7) == 0)
		return 2;
	else if ((*(unsigned char *)data->file == 0xFE  && *((unsigned char *)data->file + 1) == 0xED && *((unsigned char *)data->file + 2) == 0xFA && *((unsigned char *)data->file + 3) == 0xCE))
		ft_printf("Mach-o 32bits format\n");
	else if ((*(unsigned char *)data->file == 0xFE  && *((unsigned char *)data->file + 1) == 0xED && *((unsigned char *)data->file + 2) == 0xFA && *((unsigned char *)data->file + 3) == 0xCF))
		ft_printf("Mach-o 64bits format\n");
	else
		ft_printf("nm: %s: file format not recognized\n", data->file_name);
	return 0;
}

int		cleanExit(t_nmdata *data, int ret)
{
	munmap(data->file, data->file_stat.st_size);
	wrdestroy();
	return ret;
}

int	checkFileStat(t_nmdata *data)
{
	if ((data->fd = open(data->file_name, O_RDONLY)) < 0)
	{
		ft_printf("nm: '%s': No such file\n", data->file_name);
		return (EXIT_FAILURE);
	}
	if (fstat(data->fd, &(data->file_stat)) == -1)
	{
		ft_printf("fstat_failed\n");
		return (EXIT_FAILURE);
	}
	else if (S_ISDIR(data->file_stat.st_mode))
	{
		ft_printf("nm: Warning: '%s' is a directory\n", data->file_name);
		return (EXIT_FAILURE);
	}
	else if (!S_ISREG(data->file_stat.st_mode))
	{
		ft_printf("nm: Warning: '%s' is not an ordinary file\n", data->file_name);
		return (EXIT_FAILURE);
	}
	else if (data->file_stat.st_size == 0)
		return (EXIT_FAILURE);
	else if (data->file_stat.st_size < 4 && data->file_stat.st_size > 0)
	{
		ft_printf("nm: %s: file truncated\n", data->file_name);
		return (EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
	t_nmdata	data;
	int			valid;
	int			ret;

	valid = 0;
	data = (t_nmdata){};
	if (ac == 1)
		data.file_name = "a.out";
	else
		data.file_name = av[1];
	if (checkFileStat(&data) == EXIT_FAILURE)
		return EXIT_FAILURE;
	data.file = mmap(NULL, data.file_stat.st_size, PROT_READ , MAP_SHARED, data.fd, 0);
	if (data.file == MAP_FAILED)
		ft_printf("nm: Warning: '%s' is not an ordinary file\n", data.file_name);

	ret = isElf(&data);
	if (ret == 1)
	{
		data.ehdr = data.file;
		valid = ft_ehdr(&data);
		if (data.ehdr->e_phoff != 0 && valid)
			data.phdr = data.file + data.ehdr->e_phoff + (data.ehdr->e_phnum * data.ehdr->e_phentsize);
		if (valid)
			ft_section(&data);
	}
	else if (ret == 2)
	{
		data.ar_size = data.file_stat.st_size;
		data.is_ar = 1;
		interp_ar(&data);
	}
	else
		return cleanExit(&data, EXIT_FAILURE);
	return (cleanExit(&data, EXIT_SUCCESS));
}