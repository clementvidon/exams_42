#include <unistd.h>
#include <stdio.h>

int	ft_first_in_self(int index, char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < index)
	{
		if (str[i] == str[index])
			return (0);
		i++;
	}
	return (1);
}

int	ft_first_in_both(int index, char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && i < index)
	{
		if (s1[i] == s2[index])
			return (0);
		i++;
	}
	i = 0;
	while (s2[i] && i < index)
	{
		if (s2[i] == s2[index])
			return (0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_first_in_self(i, s1))
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (ft_first_in_both(i, s1, s2))
			write(1, &s2[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		ft_union(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}
