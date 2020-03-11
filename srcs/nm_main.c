#include "nm.h"

int type_of_file(int fd, Elf64_Ehdr *EHDR)
{
    if (EHDR->e_type == ET_REL)
        ft_printf("relocatable \n");
    else if (EHDR->e_type == ET_DYN)
        ft_printf("pie executable\n");
    else if (EHDR->e_type == ET_CORE)
        ft_printf("fichier de type core\n");
    else if (EHDR->e_type == ET_EXEC)
        ft_printf("fichier de type executable\n");
    else if (EHDR->e_type == ET_NONE)
        ft_printf("fichier de type incnnue\n");
    else
        ft_printf("illegal file_type value\n");    

    return (0);
}

int eident_next(int fd, Elf64_Ehdr *EHDR)
{
    if (EHDR->e_ident[EI_DATA] == ELFDATA2LSB)
        ft_printf("LSB ");
    else if (EHDR->e_ident[EI_DATA] == ELFDATA2MSB)
        ft_printf("MSB ");
    else if (EHDR->e_ident[EI_DATA] == ELFDATANONE)
        ft_printf("unknow endian");
    else
        ft_printf("illegal endian value");

    return (0);
}

int ft_ehdr(int fd, Elf64_Ehdr *EHDR)
{
    if (get_next_xbytes(fd, (void **)&EHDR, sizeof(Elf64_Ehdr)) < 0)
    {
        wrdestroy();
        return (ft_printf("error\n"));
    }
    if (EHDR->e_ident[EI_MAG0] == ELFMAG0 && EHDR->e_ident[EI_MAG1] == ELFMAG1 && EHDR->e_ident[EI_MAG2] == ELFMAG2 && EHDR->e_ident[EI_MAG3] == ELFMAG3)
    {
        ft_printf("EFL ");
        if (EHDR->e_ident[EI_CLASS] == ELFCLASS32)
            ft_printf("binary for 32bits architecture\n");
        else if (EHDR->e_ident[EI_CLASS] == ELFCLASS64)
        {
            ft_printf("64-bit ");
            eident_next(fd, EHDR);
            type_of_file(fd, EHDR);
        }
        else
            ft_printf("invalid architecture\n");
    }
    else
        ft_printf("is not a ELF file\n");
    return (0);
}

//TODO initialiser la structure EHDR + ajouter condition dans gnxb pour malloc si null
int main(int ac, char **av)
{
    char *file;
    int fd;
    Elf64_Ehdr *EHDR;

    EHDR = NULL;
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
    ft_ehdr(fd, EHDR);
    wrdestroy();
    return (0);
}