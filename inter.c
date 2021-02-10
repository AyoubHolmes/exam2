/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 05:38:53 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/04 13:51:35 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		exist(char *s, char c)
{
	int		i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	char	res[256];
	int		i;
	int		len;

	if (ac == 3)
	{
		i = 0;
		len = 0;
		
		while (i < 256)
			res[i++] = 0;
		i = 0;
		while (av[1][i])
		{
			if (exist(res, av[1][i]) == 0)
			{
				if (exist(av[2], av[1][i]) == 1)
				{
					res[len] = av[1][i];
					len++;
					write(1, &av[1][i], 1);
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
