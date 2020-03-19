#include "nm.h"
	   #include <sys/types.h>


//TODO initialiser la structure ehdr + ajouter condition dans gnxb pour malloc si null
int main(int ac, char **av)
{
	t_nmdata	data;
	char		*file_name;
	int			fd;
	struct stat file_stat;
	int			valid;

	valid = 0;
	data = (t_nmdata){};
	if (ac == 1)
	{
		file_name = wrmalloc(ft_strlen("a.out") + 1);
		ft_strlcpy(file_name, "a.out", ft_strlen("a.out") + 1);
	}
	else
		file_name = av[1];
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (ft_printf("error open file\n"));
	// ft_printf("%s: ", file_name);
	if (fstat(fd, &file_stat) != 0)
		ft_printf("fstat_failed\n");
	else
		printf("file_size = %lu\n", file_stat.st_size);
	data.file = mmap(NULL, file_stat.st_size, PROT_READ , MAP_SHARED, fd, 0);
	if (data.file != MAP_FAILED)
	{
		// ft_printf("mapping success\n");
		data.ehdr = data.file;
		valid = ft_ehdr(data.ehdr);
	}
	else
		ft_printf("mapping failed\n");
	if (data.ehdr->e_phoff != 0 && valid)
	{	ft_phdr(fd, &data);

	}
	if (valid)
		ft_section(fd, &data);

	munmap(data.file, file_stat.st_size);
	wrdestroy();
	return (0);
}