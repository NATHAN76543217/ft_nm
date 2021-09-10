#include "nm.h"

int ft_section(t_nmdata *data)
{
    int         i;
    t_sec_index section_index;

    i = 0;
    section_index = (t_sec_index){};
    data->shdr = data->file + data->ehdr->e_shoff;
    data->sh_strtab = data->file + data->shdr[data->ehdr->e_shstrndx].sh_offset;
    while (i < data->ehdr->e_shnum)
    {
        if (ft_strcmp(data->sh_strtab + data->shdr[i].sh_name, ".symtab") == 0)
            section_index.symtab = i;
        else if (ft_strcmp(data->sh_strtab + data->shdr[i].sh_name, ".strtab") == 0)
            section_index.strtab = i;
        i++;
    }
    data->strtab = data->file + data->shdr[section_index.strtab].sh_offset;
    ft_symbol(data, section_index);
    return (0);
}

