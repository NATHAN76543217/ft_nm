#include "nm.h"

int ft_section(t_nmdata *data)
{
    int         i;
    t_sec_index section_index;

    i = 0;
    section_index = (t_sec_index){};
    data->shdr = data->file + data->ehdr->e_shoff;
    //shdr_strtab = &shdr[ehdr->e_shstrndx]; // file + ehdr->e_shoff + (ehdr->e_shstrndx * sizeof(Elf64_Shdr));
    data->sh_strtab = data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset;
    while (i < data->ehdr->e_shnum)
    {
        // printf("name = %-20s\t", data->sh_strtab + data->shdr[i].sh_name);
      /*  if (data->shdr[i].sh_type == SHT_SYMTAB)
            printf("type = %s\n", "SHT_SYMTAB");
        else
            printf("type = other\n");
      */  if (ft_strcmp(data->sh_strtab + data->shdr[i].sh_name, ".symtab") == 0)
            section_index.symtab = i;
        else if (ft_strcmp(data->sh_strtab + data->shdr[i].sh_name, ".strtab") == 0)
            section_index.strtab = i;
        i++;
    }
    data->strtab = data->file + data->shdr[section_index.strtab].sh_offset;
    ft_symbol(data, section_index);
    return (0);
}

int	ft_phdr(t_nmdata *data)
{
    int i;

    i = 0;
    // ft_printf("\n\nPROGRAM HEADERS\n");
    // printf("\nsize of phdr = %lu\n", sizeof(Elf64_Phdr));
    while (i < data->ehdr->e_phnum)
    {
    	data->phdr = data->file + data->ehdr->e_phoff + (i * data->ehdr->e_phentsize);
      /*  if (data->phdr->p_type == PT_NULL)
            ft_printf("segemnt [%d] : segment NULL\n", i);
        else if (data->phdr->p_type == PT_LOAD)
            ft_printf("segment [%d] : segment LOAD\n", i);
        else if (data->phdr->p_type == PT_DYNAMIC)
            ft_printf("segment [%d] : segment DYNAMIC\n", i);
        if (data->phdr->p_type == PT_NOTE)
            ft_printf("segment [%d] : segment NOTE\n", i);
        else if (data->phdr->p_type == PT_INTERP)
            ft_printf("segment [%d] : segment INTERP \n", i);           
        else if (data->phdr->p_type == PT_PHDR)
            ft_printf("segment [%d] : segment PHDR\n", i);
        else if (data->phdr->p_type == PT_SHLIB)
            ft_printf("segment [%d] : segment SHLIB\n", i);
        else if (data->phdr->p_type == PT_TLS)
            ft_printf("segment [%d] : segment TLS\n", i);
        else if (data->phdr->p_type == PT_LOOS)
            ft_printf("segment [%d] : segment LOOS\n", i);
        else if (data->phdr->p_type == PT_HIOS)
            ft_printf("segment [%d] : segment HIOS\n", i);
        else if (data->phdr->p_type == PT_LOPROC)
            ft_printf("segment [%d] : segment LOPROC\n", i);
        else if (data->phdr->p_type == PT_HIPROC)
            ft_printf("segment [%d] : segment HIPROC\n", i);
        else if (data->phdr->p_type == PT_GNU_EH_FRAME)
            ft_printf("segment [%d] : segment PT_GNU_EH_FRAME\n", i);
        else if (data->phdr->p_type == PT_GNU_STACK)
            ft_printf("segment [%d] : segment PT_GNU_STACK\n", i);
        else
            ft_printf("segment [%d] : other segment\n", i);*/
        i++;
    }
    data->phdr = data->file + data->ehdr->e_phoff + (i * data->ehdr->e_phentsize);
    return (0);
}
