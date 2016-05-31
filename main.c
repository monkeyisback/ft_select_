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

int outc(int c)
{
	write(1, &c, 1);
	return (1);
}

void	run_select(t_env *e)
{
	char buffer[3];
	char *res;
	char *tmp;

	/* clear term : */
	res = tgetstr("cl", NULL);
	tputs(res, 0, outc);


	while (1)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
		{
			/* positionne le curseur OU JE VEUX */
			res = tgetstr("cm", NULL);
			tputs(tgoto(res, 1, 1), 1, outc);

			
		}
		else if (buffer[0] == 4)
		{
			ft_putstr("Ctlr+d, on quitte !\n");
			return;
		}
	}


}

int		init_terminal(t_env *e)
{
	if ((e->term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, e->term_name) < 0)
		return (-1);
	if (tcgetattr(0, &(e->term_save)) == -1)
		return (-1);
	if (tcgetattr(0, &(e->term)) == -1)
		return (-1);
	e->term.c_lflag &= ~(ICANON);
	e->term.c_lflag &= ~(ECHO);
	e->term.c_cc[VMIN] = 1;
	e->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(e->term)) == -1)
		return (-1);
	return (1);
}

void	reset_terminal(t_env *e)
{
	tcsetattr(0, 0, &(e->term_save));
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
	//print_args(e);
	run_select(e);
	reset_terminal(e);
	return (0);
}
