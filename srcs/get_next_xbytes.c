#include "libft.h"

int     get_next_xbytes(int fd, unsigned char **bytes, unsigned int x)
{
    int ret;

    if (x == 0)
        return (1);
    if (read(fd, NULL, 0) < 0)
    {
        ft_printf("fd_invalid\n");
        return (-1);
    }
    if (bytes == NULL)
    {
        ft_printf("bytes == NULL\n");
        return (-1);
    }
    *bytes = wrmalloc(x);
    ret = read(fd, *bytes ,x);
    if (ret == 0)
        return (0);
    else if (ret < 1)
    {
        ft_printf("erreur de lecture du fichier\n");
        return (-1);
    }
    return (1);
}

