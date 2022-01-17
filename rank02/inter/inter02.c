






#include <unistd.h>

int	ft_isdouble(char c, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isfirst(int index, char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && i < index)
	{
		if (s1[i] == s1[index])
			return (0);
		i++;
	}
	return (1);
}

void	ft_inter(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_isfirst(i, s1) && ft_isdouble(s1[i], s2))
			write(1, &s1[i++], 1);
		else
			i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_inter(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}




