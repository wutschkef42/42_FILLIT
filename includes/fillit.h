
#ifndef FILLIT_H
# define FILLIT_H
# define MAX_BLOCKS 26
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>

typedef struct s_tetri	t_tetri;

struct			s_tetri
{
	uint64_t		value;
	t_tetri			*next;
	unsigned char	token;
	unsigned char	width;
	unsigned char	height;
	unsigned char	offset_x;
	unsigned char	offset_y;
};

int		load(const int fd, t_tetri *tetris);
int		solve(t_tetri *tetris, const int count, uint16_t *map);
int		check(const t_tetri *tetris, uint16_t *map);
void	touch(const t_tetri *tetris, uint16_t *map);
#endif
