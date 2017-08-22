/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamusse <plamusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 19:51:04 by plamusse          #+#    #+#             */
/*   Updated: 2017/08/17 20:27:08 by plamusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
** Check if tetrimino can be placed on map at coord (x,y)
*/

inline int	check(const t_tetri *trs, uint16_t *map)
{
	return (!(*(uint64_t *)(map + trs->ofst_y)
				& (trs->value >> trs->ofst_x)));
}

/*
** Toggles tetrimino (places and removes them from map)
*/

inline void	touch(const t_tetri *trs, uint16_t *map)
{
	*(uint64_t *)
		(map + trs->ofst_y) ^= trs->value >> trs->ofst_x;
}

/*
** Recursive algorithm determines wether given tetriminos can
** be placed on map of dimension size x size
*/

int			attempt(t_tetri *trs, const int size, uint16_t *map)
{
	int		pos;

	if (trs->token == 0)
		return (1);
	pos = (trs->next ? (trs->next->ofst_x + trs->next->ofst_y * size) : 0);
	trs->ofst_y = pos / size;
	while (trs->ofst_y <= size - trs->height)
	{
		trs->ofst_x = (trs->ofst_y == pos / size ? pos % size : 0);
		while (trs->ofst_x <= size - trs->width)
		{
			if (check(trs, map))
			{
				touch(trs, map);
				if (attempt(trs + 1, size, map))
					return (1);
				touch(trs, map);
			}
			trs->ofst_x++;
		}
		trs->ofst_y++;
	}
	trs->ofst_x = 0;
	trs->ofst_y = 0;
	return (0);
}

/*
** Recursive backgracking algorithm calculates minimum
** square into which a set of tetriminos can be arranged
*/

int			solve(t_tetri *trs, const int count, uint16_t *map)
{
	int		size;

	size = 2;
	while (size * size < count * 4)
		size++;
	while (!attempt(trs, size, map) && size <= 16)
	{
		ft_bzero(map, sizeof(uint16_t) * 16);
		size++;
	}
	return (size == 17 ? 0 : size);
}
