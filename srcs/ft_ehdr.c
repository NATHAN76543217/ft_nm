#include "nm.h"

static int type_of_file(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_type == ET_REL)
		ft_printf("relocatable, ");
	else if (ehdr->e_type == ET_DYN)
		ft_printf("pie executable, ");
	else if (ehdr->e_type == ET_CORE)
		ft_printf("fichier de type core\n");
	else if (ehdr->e_type == ET_EXEC)
		ft_printf("fichier de type executable\n");
	else if (ehdr->e_type == ET_NONE)
		ft_printf("fichier de type inconnue\n");
	else
		ft_printf("illegal file_type value\n");    
	if (ehdr->e_machine == EM_X86_64)
		ft_printf("x86-64, ");
	if (ehdr->e_version == EV_CURRENT)
		ft_printf("version 1 ");
	ft_printf("\nEH size = %d", ehdr->e_ehsize);
	if (ehdr->e_phnum == 0)
		ft_printf("\nNO program header entry ");
	else
		ft_printf("\nPH entries = %d", ehdr->e_phnum);
	
	if (ehdr->e_phoff == 0)
		ft_printf("\nNO programme header table\n");
	else
		printf("\nPH table offset = %lu\n", ehdr->e_phoff);
	ft_printf("PH table sizeof 1 entries = %d", ehdr->e_phentsize);
	if (ehdr->e_shoff == 0)
		ft_printf("\nNO Section header table\n");
	else
		printf("\nSH offset = %lu\n", ehdr->e_shoff);
	if (ehdr->e_shnum == 0)
		ft_printf("NO sections entries");
	else
		ft_printf("SH nb entries = %d", ehdr->e_shnum);
	if (ehdr->e_shstrndx == SHN_UNDEF)
		ft_printf("\nREFERENCE NON DEFINI");
	else
		ft_printf("\nSH strndx = %d", ehdr->e_shstrndx);
	return (0);
}

static int eident_next(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
		ft_printf("LSB ");
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
		ft_printf("MSB ");
	else if (ehdr->e_ident[EI_DATA] == ELFDATANONE)
		ft_printf("unknow endian");
	else
		ft_printf("illegal endian value");
	if (ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		ft_printf("deprecated version ");
	if (ehdr->e_ident[EI_OSABI] == ELFOSABI_LINUX)
	   ft_printf("linux ABI ");
   else
	    ft_printf("other ABI ");
   if (ehdr->e_ident[EI_NIDENT] != EI_NIDENT)
	   ft_printf("e_ident[NIDENT] = %d ", ehdr->e_ident[EI_NIDENT]);
	return (0);
}

int ft_ehdr(t_nmdata *data)
{
	// ft_printf("\nELF HEADER\n\n");
	if ((data->ehdr->e_ident[EI_MAG0] == ELFMAG0 && data->ehdr->e_ident[EI_MAG1] == ELFMAG1 && data->ehdr->e_ident[EI_MAG2] == ELFMAG2 && data->ehdr->e_ident[EI_MAG3] == ELFMAG3)
	|| (ft_strncmp((char *)data->file, "!<arch>", 7) == 0))
	{
		// ft_printf("EFL ");
		if (data->ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		{
			// ft_printf("64-bit ");
			// eident_next(data->ehdr);
			// type_of_file(data->ehdr);
			return (1);
		}
		//else if (data->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
			// ft_printf("binary for 32bits architecture\n");
		else
			ft_printf("invalid architecture\n");
	}
	else
		ft_printf("is not a ELF file\n");
	return (0);
}
