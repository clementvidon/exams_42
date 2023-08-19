#include <unistd.h>

int	ft_match_once(char *str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (str[index] == str[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_match_none(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
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
		if (ft_match_once(s1, i))
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (ft_match_once(s2, i) && ft_match_none(s1, s2[i]))
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
}
