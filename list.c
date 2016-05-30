/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:28:43 by jgirard           #+#    #+#             */
/*   Updated: 2014/01/12 22:55:02 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_list(t_env *e)
{
	e->args_pivot = (t_arg *)malloc(sizeof(t_arg));
	e->args_pivot->next = NULL;
	e->args_pivot->prev = NULL;
}

void	add_node(t_env *e, char *str)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	new->str = ft_strdup(str);
	if (e->args_pivot->prev == NULL) {
		e->args_pivot->prev = new;
		e->args_pivot->next = new;
		new->prev = e->args_pivot;
		new->next = e->args_pivot;
	} else {
		new->prev = e->args_pivot->prev;
		new->next = e->args_pivot;
		e->args_pivot->prev->next = new;
		e->args_pivot->prev = new;
	}
}

void	print_args(t_env *e)
{
	t_arg	*tmp;
	
	tmp = e->args_pivot->next;
	while (tmp != e->args_pivot) {
		ft_putstr(tmp->str);
		tmp = tmp->next;
	}
}
