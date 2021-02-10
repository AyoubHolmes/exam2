#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	unsigned int	j;
	char			*copy;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(copy = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

size_t		ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;
	int		len1;
	int		len2;

	if (s1 && s2)
	{
		i = 0;
		j = 0;
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		if (!(join = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
			return (NULL);
		while (s1[i])
			join[j++] = s1[i++];
		i = 0;
		while (s2[i])
			join[j++] = s2[i++];
		join[j] = '\0';
		return (join);
	}
	return (NULL);
}

static int		ft_intlen(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (((len == 0) ? 1 : len));
}

static char		*ft_convert(int nlen, int n)
{
	char	*a;
    int i = 0;
    int binlen = 0;

    if (nlen < 7)
        binlen = 7 - nlen;
    nlen = 7;
	if (!(a = (char *)malloc((sizeof(char) * nlen + 1))))
		return (NULL);
    while (i < binlen)
    {
        a[i] = '0';
        i++;
    }
	a[nlen] = '\0';
	while (--nlen >= i)
	{
		a[nlen] = n % 10 + 48;
		n = n / 10;
	}
	return (a);
}

char			*ft_itoa(int n)
{
	int		nlen;
	char	*a;

	nlen = ft_intlen(n);
	a = ft_convert(nlen, n);
	return (a);
}

int asciiValueToBinary(int asciiInput)
{
	int binaryNum[8];
	int i = 0;
	int res = 0;
  
    while (asciiInput > 0)
	{
        binaryNum[i] = asciiInput % 2;
        asciiInput = asciiInput / 2;
		i++;
    }
	while (--i >= 0)
		res = (res * 10) + binaryNum[i];
	return (res);
}

unsigned long binaryToDecimal(char *binary, int length)
{
	int i;
	unsigned long decimal = 0;
	unsigned long weight = 1;
	binary += length - 1;
	weight = 1;
	for(i = 0; i < length; ++i, --binary)
	{
		if(*binary == '1')
			decimal += weight;
		weight *= 2;
	}
	return decimal;
}


void binaryToText(char *binary, int binaryLength, char *text, int symbolCount)
{
    int i;
    for(i = 0; i < binaryLength; i+=8, binary += 8)
    {
        char *byte = binary;
        byte[8] = '\0';
        *text++ = binaryToDecimal(byte, 8);
    }
    text -= symbolCount;
}

char *bits(char *binary, char **text, int *p)
{
	int j, i = 8;
	char *bin;
	while (i)
	{
		if (ft_strlen(binary) % i != 0)
			i--;
		else
		{
			int n, a, b, e = 0;
			a = 0;
			n = 8 - i;
			char *zeros = (char *)malloc((sizeof(char) * n + 1));
			zeros[n] = '\0';
			while (--n >= 0)
				zeros[n] = '0';
			j = ft_strlen(binary) / i;
			*p = j;
			bin = (char *)malloc((sizeof(char *) * ((8 * j) + 1)));
			bin = "";
			char **part;
			*text = (char *)malloc((sizeof(char *) * (j + 1)));
			part = (char **)malloc((sizeof(char) * (j + 1)));
			while (a < j)
			{
				b = 0;
				part[a] = (char *)malloc((sizeof(char *) * (8 + 1)));
				while (b < i)
				{
					part[a][b] = binary[e];
					e++;
					b++;
				}
				part[a][b] = '\0';
				part[a] = ft_strjoin(zeros, part[a]);
				bin = ft_strjoin(bin, part[a]);
				a++;
			}
			break ;
		}
	}
	return (bin);
}

void ToEncode(char **av, char *encoded)
{
	char *MESSAGE = av[2];
	char *binary = ft_strdup("");
	char *text;
	char *bin;
	int i = 0;
	int j = 0;
	while (MESSAGE[i])
	{
		if (MESSAGE[i] == '\n')
			MESSAGE[i] = '\0';
		i++;
	}
	i = 0;
	while (MESSAGE[i])
	{
		bin = bits(ft_itoa(asciiValueToBinary(MESSAGE[i])), &text, &j);
		binary = ft_strjoin(binary, bin);
		i++;
	}
	encoded = (char *)malloc((sizeof(char) * (ft_strlen(binary) * 5 + 1)));
	i = 0;
	j = 0;
	while (binary[i])
	{
		if (binary[i] == '1')
		{
			encoded[j] = '0';
			encoded[j + 1] = ' ';
			j += 2;
			while (binary[i] == '1')
			{
				encoded[j] = '0';
				i++;
				j++;
			}
		}
		else if (binary[i] == '0')
		{
			encoded[j] = '0';
			encoded[j + 1] = '0';
			encoded[j + 2] = ' ';
			j += 3;
			while (binary[i] == '0')
			{
				encoded[j] = '0';
				i++;
				j++;
			}
		}
		if (binary[i])
		{
			encoded[j] = ' ';
			j++;
		}
	}
	printf("Binary : %s|len : %lu\nEncoded: %s\n", binary, ft_strlen(binary), encoded);
}

void ToDecode(char **av, int ac, char *encoded)
{
	int i = 2;
	while (i < ac)
	{
		if (av[i + 1])
			av[i + 1] = ft_strjoin(" ",av[i + 1]);
		encoded = ft_strjoin(encoded, av[i]);
		i++;
	}
	i = 0;
	while (encoded[i])
	{
		if (encoded[i] == '0' || encoded[i] == ' ')
			i++;
		else
		{
			printf("put a valid encoded text");
			exit(1);
		}
	}
	i = 0;
	char *binary = (char *)malloc((sizeof(char) * (ft_strlen(encoded) / 3 + 1)));
	int j = 0;
	while (encoded[i])
	{
		if (encoded[i] == '0' && encoded[i + 1] == ' ')
		{
			i += 2;
			while (encoded[i] == '0')
			{
				binary[j] = '1';
				i++;
				j++;
			}
		}
		else if (encoded[i] == '0' && encoded[i + 1] == '0' && encoded[i + 2] == ' ')
		{
			i += 3;
			while (encoded[i] == '0')
			{
				binary[j] = '0';
				i++;
				j++;
			}
		}
		else
			i++;
	}
	char *text;
	binary = bits(binary, &text, &j);
	printf("Binary : %s | len : %lu\n",binary, ft_strlen(binary));
	binaryToText(binary, ft_strlen(binary), text, j);
	printf("Text: %s\n",text);
}


int main(int ac, char **av)
{
    if (ac >= 3)
    {
		char encode = 'e';
		char decode = 'd';
		char *encoded = ft_strdup("");
		if (*av[1] == encode)
			ToEncode(av, encoded);
		else if (*av[1] == decode)
			ToDecode(av, ac, encoded);
    }
    return 0;
}


