#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
# include <stdio.h>

typedef struct	s_printf
{
	int				width;
	int				precision;
	int				point;
	int				d;
	int				len;
	char			*s;
	int				sign;
	char			specifier;
	int				count;
	unsigned int	x;
}				t_printf;

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

void	ft_putchar(char c)
{
	write(1, &c,1);
}

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("2147483648");
		return ;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	init_vars(t_printf *vars)
{
	vars->len = 0;
	vars->point = 0;
	vars->precision = 0;
	vars->width = 0;
	vars->sign = 0;
	vars->specifier = 0;
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

void	flags(char **s, t_printf *vars, va_list arg)
{
	(*s)++;
	while (*s)
	{
		if (**s == 'd' || **s == 's' || **s == 'x')
		{
			vars->specifier = **s;
			if (**s == 'd')
				vars->d = va_arg(arg, int);
			else if (**s == 's')
				vars->s = va_arg(arg, char *);
			else if (**s == 'x')
				vars->x = va_arg(arg, unsigned int);
			(*s)++;
			break ;
		}
		else if (**s == '.')
		{
			vars->point = 1;
			(*s)++;
			vars->precision = ft_atoi(s);
			(*s)--;
		}
		else if (is_digit(**s))
		{
			vars->width = ft_atoi(s);
			(*s)--;
		}
		(*s)++;
	}
}

void	print_dec(t_printf *vars)
{
	vars->len = nbrlen(vars->d);
	vars->sign = (vars->d < 0) ? 1 : 0;
	vars->d *= (vars->sign) ? -1 : 1;
	if (!vars->d && vars->point && vars->precision == 0)
		vars->len = 0;
	vars->precision -= (vars->precision > vars->len) ? vars->len : vars->precision;
	vars->width -= (vars->width > vars->len + vars->sign + vars->precision) ? vars->len + vars->sign + vars->precision : vars->width;
	while(vars->width)
	{
		ft_putchar(' ');
		vars->count++;
		vars->width--;
	}
	if (vars->sign)
	{
		ft_putchar('-');
		vars->count++;
	}
	while (vars->precision)
	{
		ft_putchar('0');
		vars->count++;
		vars->precision--;
	}
	if (vars->len)
		ft_putnbr(vars->d);
	vars->count += vars->len;
}

void	print_s(t_printf *vars)
{
	vars->len = (vars->s) ? ft_strlen(vars->s) : 6;
	vars->len = (vars->point && vars->len > vars->precision) ? vars->precision : vars->len;
	vars->width -= (vars->width > vars->len) ? vars->len : vars->width;
	while (vars->width)
	{
		ft_putchar(' ');
		vars->count++;
		vars->width--;
	}
	if (!vars->s)
		vars->s = "(null)";
	vars->count += vars->len;
	while (vars->len)
	{
		ft_putchar(*vars->s);
		vars->s++;
		vars->len--;
	}
}

void	*ft_rev(char *hex)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(hex) - 1;
	while (i < len)
	{
		tmp = hex[i];
		hex[i++] = hex[len];
		hex[len--] = tmp;
	}
	return (hex);
}

char		*converter(unsigned int n, char x)
{
	int		i;
	int		temp;
	char	*hex;

	i = 0;
	hex = (char *)malloc(sizeof(char) * 20);
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			hex[i++] = 48 + temp;
		else
			hex[i++] = (x - 33) + temp;
		n /= 16;
	}
	hex[i] = '\0';
	hex = ft_rev(hex);
	return (hex);
}

void	print_x(t_printf *vars)
{
	vars->s = (vars->x == 0) ? "0" : converter(vars->x, 'x');
	vars->len = ft_strlen(vars->s);
	if (!vars->x && vars->point && vars->precision == 0)
		vars->len = 0;
	vars->precision -= (vars->precision > vars->len) ? vars->len : vars->precision;
	vars->width -= (vars->width > vars->len + vars->precision) ? vars->len + vars->precision : vars->width;
	while(vars->width)
	{
		ft_putchar(' ');
		vars->count++;
		vars->width--;
	}
	while (vars->precision)
	{
		ft_putchar('0');
		vars->count++;
		vars->precision--;
	}
	vars->count += vars->len;
	while (vars->len)
	{
		ft_putchar(*vars->s);
		vars->s++;
		vars->len--;
	}
}

void	printing(t_printf *vars)
{
	if (vars->specifier == 'd')
		print_dec(vars);
	else if (vars->specifier == 's')
		print_s(vars);
	else if (vars->specifier == 'x')
		print_x(vars);
}

int		ft_printf(const char *s, ... )
{
	va_list		arg;
	t_printf	vars;

	vars.count = 0;
	va_start(arg, s);
	while(*s)
	{
		while (*s != '%' && *s)
		{
			ft_putchar(*s);
			vars.count++;
			s++;
		}
		if (*s == '%' && *s)
		{
			init_vars(&vars);
			flags((char **)&s, &vars, arg);
			printing(&vars);
		}
	}
	return (vars.count);
}

// #define exp "%d7%x%d%x%d%x%d%x", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648

// int main(void)
// {
// 	printf("\t|R0=%d|\n", printf(exp));
// 	printf("\t|RF=%d|\n", ft_printf(exp));
// }