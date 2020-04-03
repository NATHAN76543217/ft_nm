// #include "nm.h"
#include "libft.h"

int     str_endwith(const char *str, const char *buf)
{
	int size;
	int bsize;

	if (!str || !buf)
		return (0);
	size = ft_strlen(str);
	bsize = ft_strlen(buf);
	if (bsize > size)
		return (0);
	while (bsize >= 0)
	{
		if (str[size] != buf[bsize])
			return (0);
		size--;
		bsize--;
	}
	return (1);
}

int	ft_natoi(const char *str, int n)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((*(str + i) == ' ' || (*(str + i) >= '\t' && *(str + i) <= '\r')) && i < n)
		i++;
	if ((*(str + i) == '+' || *(str + i) == '-') && i < n)
		(*(str + i++) == '-') ? sign = -1 : 0;
	while (ft_isdigit(*(str + i)) && i < n)
	{
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		result = result * 10 + (*(str + i++) - '0');
	}
	result *= sign;
	return (result);
}
