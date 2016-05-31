/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 20:38:02 by jgirard           #+#    #+#             */
/*   Updated: 2016/01/30 22:56:10 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	refresh_sizes(t_env *e) {
	e->term_size_c = tgetnum("co");
	e->term_size_l = tgetnum("li");
}

int		align_get_start_c(t_env *e)
{
	return ((e->term_size_c > 5) ? 1: 0);
}

// WIP : donner les positions des mots
void	align_words(t_env *e) {
	int max_c;
	int max_l;
	int cur_c;
	int cur_l;

	// bornes actuelles, si il y a la place on laisse du vide
	refresh_sizes(e);
	max_c = (e->term_size_c > 5) ? e->term_size_c - 2: e->term_size_c;
	max_l = (e->term_size_l >= 3) ? e->term_size_c - 2: e->term_size_l;
	cur_c = align_get_start_c(e);
	cur_l = (e->term_size_l >= 3) ? 1: 0;

	// on donne les pos de depart et de fin aux caracteres
	t_arg	*tmp;
	
	tmp = e->args_pivot->next;
	while (tmp != e->args_pivot) {
		// position du depart du texte - pas la derniere ligne
		if (cur_l < max_l) {
			// le mot rentre ...
			if (cur_c + ft_strlen(tmp->str) + 1 < max_c) {
				tmp->pos_word_begin_c = cur_c;
				tmp->pos_word_end_c = cur_c + ft_strlen(tmp->str);
				tmp->pos_word_l = cur_l;
			}
			// ... PAS
			else {
				cur_l++;
				cur_c = = align_get_start_c(e);
				tmp->pos_word_begin_c = align_get_start_c(e);
				if (cur_c + ft_strlen(tmp->str) + 1 < max_c) {
					tmp->pos_word_end_c = cur_c + ft_strlen(tmp->str);
				} else {
					tmp->pos_word_end_c = max_c - 3;
				}
			}
		}
		// position de depart du texte - derniere ligne
		else if (cur_l == max_l) {

		}
		tmp = tmp->next;
	}
}