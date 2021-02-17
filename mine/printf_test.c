#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include <stdarg.h>

typedef struct		s_printf
{
	int				width;
	int				point;
	int				precision;
	int				count;
	int				d;
	char			*s;
	unsigned int	x;
	int				len;
	int				sign;
	int				specifier;
}					t_printf;

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
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int		nbrlen(int n)
{
	int l;

	l = 1;
	while (n / 10)
	{
		l++;
		n /= 10;
	}
	return (l);
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi(char **s)
{
	int a;

	a = 0;
	while(is_digit(**s))
	{
		a = (a * 10) + (**s - '0');
		(*s)++;
	}
	return (a);
}

char	*ft_rev(char *s)
{
	int i;
	int len;
	char tmp;

	i = 0;
	len = ft_strlen(s) - 1;
	while (i < len)
	{
		tmp = s[i];
		s[i++] = s[len];
		s[len--] = tmp;
	}
	return (s);
}

char	*converter(unsigned int n)
{
	int mod;
	int i;
	char *hexa;

	hexa = (char*)malloc(sizeof(char) * 20);
	i = 0;
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

void	flags(char **format, t_printf *vars, va_list lst)
{
	(*format)++;
	while(*format)
	{
		if (**format == 'd' || **format == 's' || **format == 'x')
		{
			vars->specifier = **format;
			if (vars->specifier == 'd')
				vars->d = va_arg(lst, int);
			else if (vars->specifier == 's')
				vars->s = va_arg(lst, char *);
			else if (vars->specifier == 'x')
				vars->x = va_arg(lst, unsigned int);
			(*format)++;
			break;
		}
		else if (**format == '.')
		{
			vars->point = 1;
			(*format)++;
			vars->precision = ft_atoi(format);
			(*format)--;
		}
		else if (is_digit(**format))
		{
			vars->width = ft_atoi(format);
			(*format)--;
		}
		(*format)++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar(*s);
			s++;
		}
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

void	print_dec(t_printf *vars)
{
	vars->len = nbrlen(vars->d);
	
	vars->sign = (vars->d < 0) ? 1 : 0;
	vars->d *= (vars->sign) ? -1 : 1;
	if (!vars->d && vars->point && vars->precision == 0) 
		vars->len = 0;
	vars->precision -= (vars->precision > vars->len) ? vars->len : vars->precision;
	vars->width -= (vars->width > vars->precision + vars->len + vars->sign) ? vars->precision + vars->len + vars->sign : vars->width;
	//printf("%d     %d    %d\n",vars->len, vars->precision, vars->width);
	vars->count += vars->width;
	while (vars->width)
	{
		ft_putchar(' ');
		vars->width--;
	}
	if (vars->sign)
	{
		ft_putchar('-');
		vars->count++;
	}
	vars->count += vars->precision;
	while (vars->precision)
	{
		ft_putchar('0');
		vars->precision--;
	}
	vars->count += vars->len;
	if (vars->len)
		ft_putnbr(vars->d);
}

void	print_s(t_printf *vars)
{
	vars->len = (vars->s) ? ft_strlen(vars->s) : 6;
	vars->len = (vars->point && vars->len > vars->precision) ? vars->precision: vars->len;
	vars->width -= (vars->width > vars->len) ? vars->len : vars->width;
	vars->count += vars->width;
	while (vars->width)
	{
		ft_putchar(' ');
		vars->width--;
	}
	if (!vars->s)
		vars->s = "(null)";
	vars->count += vars->len;
	while(vars->len)
	{
		ft_putchar(*vars->s);
		vars->s++;
		vars->len--;
	}
}

void	print_x(t_printf *vars)
{
	int i;

	i = 0;
	vars->s = (vars->x == 0) ? "0" : converter(vars->x);
	vars->len = ft_strlen(vars->s);
	if (!vars->x && vars->point && vars->precision == 0) 
		vars->len = 0;
	vars->precision -= (vars->precision > vars->len) ? vars->len : vars->precision;
	vars->width -= (vars->width > vars->precision + vars->len) ? vars->precision + vars->len : vars->width;
	vars->count += vars->width;
	while (vars->width)
	{
		ft_putchar(' ');
		vars->width--;
	}
	vars->count += vars->precision;
	while (vars->precision)
	{
		ft_putchar('0');
		vars->precision--;
	}
	vars->count += vars->len;
	while (i < vars->len)
	{
		ft_putchar(vars->s[i]);
		i++;
	}
	if (vars->x != 0)
		free(vars->s);
}

void	printing(t_printf *vars)
{
	if (vars->specifier == 'd')
		print_dec(vars);
	else if (vars->specifier == 'x')
		print_x(vars);
	else if (vars->specifier == 's')
		print_s(vars);
}

int		ft_printf(const char *format, ...)
{
	t_printf vars;
	va_list lst;

	va_start(lst, format);
	vars.count = 0;
	while(*format)
	{
		while (*format != '%' && *format)
		{
			ft_putchar(*format);
			vars.count++;
			format++;
		}
		if (*format == '%' && *format)
		{
			init_vars(&vars);
			flags((char **)&format, &vars, lst);
			printing(&vars);
		}
	}
	return (vars.count);
}
/* int main()
{
	printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
} */