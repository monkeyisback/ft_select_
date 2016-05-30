/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:20:23 by jgirard           #+#    #+#             */
/*   Updated: 2014/01/12 22:42:11 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putstr_err(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_error_exit(const char *str)
{
	ft_putstr_err(str);
	write(2, "\n", 1);
	exit(0);
}

char	*ft_strdup(const char *str)
{
	char	*newstr;
	size_t	count;
	size_t	len;

	count = 0;
	len = ft_strlen(str);
	newstr = (char *)malloc(sizeof(char) * (len + 1));
	while (count < len)
	{
		newstr[count] = str[count];
		count++;
	}
	newstr[count] = '\0';
	return (newstr);
}
