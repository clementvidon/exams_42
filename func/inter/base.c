#include <unistd.h>

int	ft_check_double(char *str1, int str1_index, char c)
{
	int	i;

	i = 0;
	while (i < str1_index)
	{
		if (str1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_inter(char	*str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str2[j] == str1[i])
			{
				if (!ft_check_double(str1, i, str2[j]))
				{
					write(1, &str1[i], 1);
					break ;
				}
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		ft_inter(av[1], av[2]);
	}
	write(1, "\n", 1);
	return (0);
}
