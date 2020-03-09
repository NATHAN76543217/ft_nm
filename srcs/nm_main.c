#include "nm.h"

int main(int ac, char **av)
{
    char *file;
    int fd;
    unsigned char *BF;

    if (ac == 1)
    {
        file = wrmalloc(ft_strlen("a.out") + 1);
        ft_strlcpy(file, "a.out", ft_strlen("a.out") + 1);
        ft_printf("file = |%s|", file);
    }
    else
        file = av[1];

    if ((fd = open(file, O_RDONLY)) < 0)
        return (ft_printf("error open file\n"));
    if ( get_next_xbytes(fd, &BF, 4) < 0)
    {
        wrdestroy();
        return (ft_printf("error\n"));
    }
    if (BF[0] == 0x7f && BF[1] == 'E' && BF[2] == 'L' && BF[3] == 'F')
    {
        ft_printf("is a EFL file\n");

    }
    else
        ft_printf("is not a ELF file\n");
    wrdestroy();
    return (0);
}