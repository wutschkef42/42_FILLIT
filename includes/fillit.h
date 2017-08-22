/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamusse <plamusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 20:03:40 by plamusse          #+#    #+#             */
/*   Updated: 2017/08/17 20:25:06 by plamusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define MAX_BLOCKS 26
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>

typedef struct s_tetri	t_tetri;

struct					s_tetri
{
	uint64_t		value;
	t_tetri			*next;
	unsigned char	token;
	unsigned char	width;
	unsigned char	height;
	unsigned char	ofst_x;
	unsigned char	ofst_y;
};

int						load(const int fd, t_tetri *tetris);
int						solve(t_tetri *tetris, const int count, uint16_t *map);
int						check(const t_tetri *tetris, uint16_t *map);
void					touch(const t_tetri *tetris, uint16_t *map);
#endif
