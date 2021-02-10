#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_printf
{
	int				width;
	int				precision;
	int				point;
	int				count;
	int				d;
	char			*s;
	unsigned int	x;
	int				len;
	int				sign;
	int				specifier;
}				t_printf;

void	init_vars(t_printf *vars)
{
	vars->width = 0;
	vars->precision = 0;
	vars->point = 0;
	vars->len = 0;
	vars->sign = 0;
	vars->specifier = 0;
}

int		ft_strlen(char *s)
{
	int	l;

	l = 0;
	if (!s)
		return (0);
	while (*s++)
		l++;
	return (l);
}

int		nbrlen(int	n)
{
	int		l;

	l = 1;
	while (n / 10)
	{
		n /= 10;
		l++;
	}
	return (l);
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi(char **s)
{
	int		a;

	a = 0;
	while (is_digit(**s))
	{
		a = (a * 10) + (**s - '0');
		(*s)++;
	}
	return (a);
}


char	*ft_rev(char *hexa)
{
	char tmp;
	int len;
	int i;

	i = 0;
	len = ft_strlen(hexa) - 1;
	while (i < len)
	{
		tmp = hexa[i];
		hexa[i++] = hexa[len];
		hexa[len--] = tmp;
	}
	return (hexa);
}

char	*converter(unsigned int n)
{
	int mod;
	int i;
	char *hexa;

	i = 0;
	hexa = (char*)malloc(sizeof(char) * 20);
	while (n != 0)
	{
		mod = n % 16;
		if (mod < 10)
			hexa[i] = mod + 48;
		else
			hexa[i] = mod + 87;
		i++;
		n /= 16;
	}
	hexa[i] = '\0';
	hexa = ft_rev(hexa);
	return (hexa);
}


