

#include "libft.h"
#include "fillit.h"

/*
** Check if tetrimino can be placed on map at coord (x,y)
*/

inline int	check(const t_tetri *tetris, uint16_t *map)
{
	return (!(*(uint64_t *)(map + tetris->offset_y) & (tetris->value >> tetris->offset_x)));
}


/*
** Toggles tetrimino (places and removes them from map)
*/

inline void	touch(const t_tetri *tetris, uint16_t *map)
{
	*(uint64_t *)(map + tetris->offset_y) ^= tetris->value >> tetris->offset_x;	
}

/*
** Recursive algorithm determines wether given tetriminos can
** be placed on map of dimension size x size
*/

int			attempt(t_tetri *tetris, const int size, uint16_t *map)
{
	int pos;

	if (tetris->token == 0)
		return (1);
	pos = (tetris->next ? (tetris->next->offset_x + tetris->next->offset_y * size) : 0);
	tetris->offset_y = pos / size;
	while (tetris->offset_y <= size - tetris->height)
	{
		tetris->offset_x = (tetris->offset_y == pos / size ? pos % size : 0);
		while (tetris->offset_x <= size - tetris->width)
		{
			if (check(tetris, map))
			{
				touch(tetris, map);
				if (attempt(tetris + 1, size, map))
					return (1);
				touch(tetris, map);
			}
			tetris->offset_x++;
		}
		tetris->offset_y++;
	}
	tetris->offset_x = 0;
	tetris->offset_y = 0;
	return (0);
}

/*
** Recursive backgracking algorithm calculates minimum
** square into which a set of tetriminos can be arranged
*/

int		solve(t_tetri *tetris, const int count, uint16_t *map)
{
	int	size;

	size = 2;
	while (size * size < count * 4)
		size++;
		while (!attempt(tetris, size, map) && size <= 16)
		{
			ft_bzero(map, sizeof(uint16_t) * 16);
			size++;
		}
		return (size == 17 ? 0 : size);
}
