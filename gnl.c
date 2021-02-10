/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 22:34:12 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/23 16:01:38 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int  ft_strlen(const char *s)
{
	int     i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_strdup(const char *s1)
{
	unsigned int    i;
	unsigned int    j;
	char            *copy;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(copy = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	int     i;
	int     j;
	char    *join;
	int     len1;
	int     len2;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
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

char    *ft_strchr(const char *s, int c)
{
	int     i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char    *ft_substr(char const *s, unsigned int start, int len)
{
	unsigned int    i;
	unsigned int    j;
	char            *sub;

	if (!s)
		return (NULL);
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	j = 0;
	if (!(sub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			while (s[i] && j < len)
				sub[j++] = s[i++];
			sub[j] = '\0';
			return (sub);
		}
		i++;
	}
	return (NULL);
}

int read_line(char **str, char **line)
{
	int i = 0;
	char *tmp;

	if (*str)
	{
		while ((*str)[i] && (*str)[i] != '\n')
			i++;
		if ((*str)[i] == '\n')
		{
			*line = ft_substr(*str, 0, i);
			tmp = *str;
			*str = ft_strdup(*str + i + 1);
			free(tmp);
		}
		else if (str[i] == '\0')
		{
			*line = ft_strdup(*str);
			free(*str);
			*str = NULL;
			return (0);
		}
	}
	return (1);
}

int get_next_line(char **line)
{
	char buff[1025];
	static char *str;
	char *tmp;
	int r;

	while ((r = read(0, buff, 1024)) > 0)
	{
		buff[r] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (r < 0)
		return (-1);
	else if (!r && (str == NULL || str[0] == '\0'))
	{
		*line = ft_strdup("");
		return (0);
	}
	return (read_line(&str, line));
}

int		main()
{
	char	*line;
	int		r = 1;

	while (r == 1)
	{
		r = get_next_line(&line);
		printf("r : %d | line : %s\n", r, line);
		free(line);
	}
}
