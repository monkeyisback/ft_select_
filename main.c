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

void	clear_term(t_env *e)
{
	char *res;

	res = tgetstr("cl", NULL);
	tputs(res, 0, outc);
}

void	print_line(char *str, int x, int y, int mode)
{
	char *res;

	if (mode == 0)
		res = tgetstr("cm", NULL);
	else if (mode == 1)
		res = tgetstr("mr", NULL);
	else if (mode == 2)
		res = tgetstr("us", NULL);
	tputs(tgoto(res, x, y), 1, outc);
	printf("%s\n", str);
	res = tgetstr("me", NULL);
	write(0, res, ft_strlen(res));
}

int		screen_lines()
{
	struct winsize sz;
	
	ioctl(0, TIOCGWINSZ, &sz);
	return (sz.ws_row);
}

void	calc_word_align(t_env *e)
{
	char *res;
	t_arg *ptr;
	int scr_y;
	int sum_words;
	int i;
	int pos;
	int selected_index;

	ptr = e->args_pivot->next;
	scr_y = screen_lines();
	sum_words = sum_elements(e->args_pivot);
	i = 0;
	pos = 0;
	selected_index = get_elm_index(e->args_pivot, e->cursor_pos);
	while (ptr != NULL && ptr != e->args_pivot)
	{
		ptr->screen_y = -1;
		if (i >= selected_index + 1 - (scr_y / 2) && pos < scr_y)
		{
			ptr->screen_y = pos;
			pos++;
		}
		ptr = ptr->next;
		i++;
	}
}

void	cursor_pos(t_env *e)
{
	char *res;

	res = tgetstr("cm", NULL);
	tputs(tgoto(res, 1, e->cursor_pos->screen_y), 1, outc);
}

void	print_term(t_env *e)
{
	t_arg *ptr;

	ptr = e->args_pivot->next;
	clear_term(e);
	calc_word_align(e);
	while (ptr != NULL && ptr != e->args_pivot)
	{
		if (ptr->screen_y > -1)
		{
			print_line(ptr->str, 1, ptr->screen_y, ptr->is_selected);
		}
		ptr = ptr->next;
	}
	cursor_pos(e);
}

void	run_select(t_env *e)
{
	char buffer[3];
	char *res;
	char *tmp;

	while (1)
	{
		read(0, buffer, 1);

		if (buffer[0] == ' ') 
		{
			e->cursor_pos->is_selected = (e->cursor_pos->is_selected == 0) ? 1 : 0;
			print_term(e);
		}
		else if (buffer[0] == 27)
		{
			read(0, buffer, 2);
			buffer[2] = buffer[1];
			buffer[1] = buffer[0];
			buffer[0] = 27;

			if (buffer[2] == 'B') {
				e->cursor_pos = e->cursor_pos->next;
				if (e->cursor_pos == e->args_pivot)
					e->cursor_pos = e->args_pivot->next;
			}
			if (buffer[2] == 'A') {
				e->cursor_pos = e->cursor_pos->prev;
				if (e->cursor_pos == e->args_pivot)
					e->cursor_pos = e->args_pivot->prev;
			}

			print_term(e);

			//printf("[%s], prev: %p, current: %p, next: %p | Pivot : %p [pivprev : %p | pivnext : %p]\n", e->cursor_pos->str, e->cursor_pos->prev, e->cursor_pos, e->cursor_pos->next, e->args_pivot, e->args_pivot->prev, e->args_pivot->next);
		}
		else if (buffer[0] == 4)
		{
			ft_putstr("Ctlr+d, on quitte !\n");
			return;
		}
	}
}

int		init_terminal(t_env *e, t_term *term, t_term *term_save)
{
	if ((e->term_name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, e->term_name) < 0)
		return (-1);
	if (tcgetattr(0, term_save) == -1)
		return (-1);
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (-1);
	e->current_lines = screen_lines();
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	*e;
	int		i;
	t_term	term;
	t_term	term_save;

	e = (t_env *)malloc(sizeof(t_env));
	ft_get_env(e);
	init_list(e);
	i = 1;
	while (i < argc)
	{
		add_node(e, argv[i]);
		i++;
	}
	e->cursor_pos = e->args_pivot->next;
	if (!init_terminal(e, &term, &term_save))
	{
		ft_error_exit("can't initialize termcaps");
	}
	init_signals(e);
	//print_args(e);
	run_select(e);
	tcsetattr(0, 0, &term_save);
	return (0);
}
