
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

/*
** Initializes empty map 
*/

char	*init_map(int dim)
{
	char	*str;
	int		x;
	int		y;

	str = ft_strnew((dim + 1) * dim);
	y = 0;
	while (y < dim)
	{
		x = 0;
		while (x < dim)
		{
			str[y * (dim + 1) + x] = '.';
			x++;
		}
		str[y * (dim + 1) + x] = '\n';
		y++;
	}
	return (str);
}

/*
** fills and prints a string representation of the solution
*/

void	print_map(t_tetri *t, int count, int size)
{
	char	*str;
	int		x;
	int		y;

	str = init_map(size);
	while (count > 0)
	{
		y = 0;
		while (y < t->height)
		{
			x = 0;
			while (x < t->width)
			{
				if ((t->value >> (16 * (y + 1) - x - 1)) & 1)
					str[(t->offset_y + y) * (size + 1) + x + t->offset_x] = t->token;
				x++;		
			}
			y++;
		}
		t++;
		count--;
	}
	ft_putstr(str);
	ft_strdel(&str);
}

int		main(int argc, char **argv)
{
	t_tetri		tetris[MAX_BLOCKS + 1];
	uint16_t	map[16];
	int			count;
	int			size;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit [data]");
		return (1);
	}
	if ((count = load(open(argv[1], O_RDONLY), tetris)) == 0)
	{
		ft_putstr("error loading input");
		return (1);
	}
	ft_bzero(map, sizeof(uint16_t) * 16);
	if ((size = solve(tetris, count, map)) == 0)
	{
		ft_putstr("error running algorithm");
		return (1);
	}
	print_map(tetris, count, size);
	return (0);


}
