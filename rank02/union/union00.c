#include <unistd.h>

int ft_once_in_self(char *s1, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (s1[index] == s1[i])
			return (0);
		i++;
	}
	return (1);
}

int ft_once_in_both(char *s1, char c)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void ft_union(char *s1, char *s2)
{
	int	i;
	// print the 'once in s1'
	i = 0;
	while (s1[i])
	{
		if (ft_once_in_self(s1, i))
		{
			write(1, &s1[i], 1);
		}
		i++;
	}

	// print only the once in both
	i = 0;
	while (s2[i])
	{
		if (ft_once_in_self(s2, i) && ft_once_in_both(s1, s2[i]))
		{
			write(1, &s2[i], 1);
		}
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
