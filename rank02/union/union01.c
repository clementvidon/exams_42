#include <unistd.h>

int	ft_once_in_self(char *str, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (str[i] == str[index])
			return (0);
		i++;
	}
	return (1);
}

int	ft_only_in_second(char *s1, char *s2, char c)
{
	int i;

	i = 0;
	while (s2[i] && s1[i])
	{
		if (s1[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int	i;

	i = 0; // s1 -> once_in_s1
	while (s1[i])
	{
		if(ft_once_in_self(s1, i))
			write(1, &s1[i], 1);
		i++;
	}

	i = 0; // s2 -> once_in_s1 + only_in_second
	while (s2[i])
	{
		if(ft_once_in_self(s2, i) && ft_only_in_second(s1, s2, s2[i]))
			write(1, &s2[i], 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
	ft_union(av[1], av[2]);
	}
	write(1, "\n", 1);
	return (0);
}
