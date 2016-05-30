/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:18:31 by jgirard           #+#    #+#             */
/*   Updated: 2014/01/12 22:56:10 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	init_terminal(t_env *e)
{
	if ((e->term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, e->term_name) < 0)
		return (-1);
	if (tcgetattr(0, &(e->term_save)) == -1)
		return (-1);
	if (tcgetattr(0, &(e->term)) == -1)
		return (-1);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	*e;
	int		i;

	e = (t_env *)malloc(sizeof(e));
	init_list(e);
	i = 1;
	while (i < argc)
	{
		add_node(e, argv[i]);
		i++;
	}
	if (!init_terminal(e))
	{
		ft_error_exit("can't initialize termcaps");
	}
	return (0);
}
