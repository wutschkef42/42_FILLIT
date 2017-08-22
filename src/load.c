/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamusse <plamusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 19:43:58 by plamusse          #+#    #+#             */
/*   Updated: 2017/08/20 15:21:54 by plamusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
** Calculate tetrimino coordinates [x_min, x_max, y_min, y_max]
** relative to 5 x 4 board
*/

void	get_coord(const char *str, char *crd)
{
	int	i;

	i = 0;
	crd[0] = 3;
	crd[1] = 0;
	crd[2] = 3;
	crd[3] = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i % 5 < crd[0])
				crd[0] = i % 5;
			if (i % 5 > crd[1])
				crd[1] = i % 5;
			if (i / 5 < crd[2])
				crd[2] = i / 5;
			if (i / 5 > crd[3])
				crd[3] = i / 5;
		}
		i++;
	}
}

/*
** consumes 21 byte string representing a tetrimino and
** constructs t_tetri node representation
*/

t_tetri	build_piece(const char *str, const char token)
{
	t_tetri	tetri;
	char	m[4];
	int		x;
	int		y;

	get_coord(str, m);
	tetri.width = m[1] - m[0] + 1;
	tetri.height = m[3] - m[2] + 1;
	tetri.token = token;
	tetri.value = 0;
	tetri.next = NULL;
	y = 0;
	while (y < tetri.height)
	{
		x = 0;
		while (x < tetri.width)
		{
			if (str[m[0] + x + (m[2] + y) * 5] == '#')
				tetri.value |= (1L << (16 * (y + 1) - x - 1));
			x++;
		}
		y++;
	}
	return (tetri);
}

/*
** Counts number of horizontally/ vertrically connected pixels
** in block. 6-8 connections prove block is valid tetrimino.
*/

int		count_connections(const char *str)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				count++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				count++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				count++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				count++;
		}
		i++;
	}
	return (count == 6 || count == 8);
}

/*
** Parses 21 string byte representing a tetrimino and
** validates input format
*/

int		parse_block(const char *str, const int count)
{
	int i;
	int active_pixels;

	active_pixels = 0;
	i = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (!(str[i] == '#' || str[i] == '.'))
				return (1);
			if (str[i] == '#' && ++active_pixels > 4)
				return (2);
		}
		else if (str[i] != '\n')
			return (3);
		i++;
	}
	if (count == 21 && str[20] != '\n')
		return (4);
	if (!(count_connections(str)))
		return (5);
	return (0);
}

/*
** loads input from file, constructs tetriminos and stores
** them in tetrimino array
*/

int		load(const int fd, t_tetri *tetris)
{
	char	buf[22];
	int		count;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (((count = read(fd, buf, 21)) >= 20) && i <= 26)
	{
		len += count;
		if (parse_block(buf, count) != 0)
			return (0);
		tetris[i] = build_piece(buf, (char)i + 'A');
		count = i - 1;
		while (count >= 0)
		{
			if (tetris[count].value == tetris[i].value)
				tetris[i].next = tetris + count;
			count--;
		}
		i++;
	}
	if (count != 0 || (len + 1) % 21 != 0)
		return (0);
	return (i);
}
