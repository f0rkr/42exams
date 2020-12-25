#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct		s_display
{
	int		w;
	int		h;
	char	b_char;
	char	mapzone[300][300];
}					t_display;

typedef struct		s_rect
{
	char		op;
	float		x;
	float		y;
	float		r;
	char		b_char;
}					t_rect;

t_display	g_d;
t_rect		g_r;

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

float	square(float x)
{
	return (x * x);
}

float	ft_dist(float x1, float y1, float x2, float y2)
{
	float dstx;
	float dsty;

	dstx = square(x1 - x2);
	dsty = square(y1 - y2);
	return (dstx + dsty);
}

int		ft_check(float x, float y)
{
	float distance;

	distance = sqrtf(ft_dist(x, y, g_r.x, g_r.y));
	distance = g_r.r - distance;
	if (distance >= 0.0000000)
	{
		if (distance >= 1.0000000)
			return (1);
		return (2);
	}
	return (0);
}

void	ft_draw()
{
	int	x;
	int y;

	y = 0;
	while (y < g_d.h)
	{
		x = 0;
		while (x < g_d.w)
		{
			if (ft_check((float)x, (float)y) == 2 || (ft_check((float)x, (float)y) == 1 && g_r.op == 'C'))
				g_d.mapzone[y][x] = g_r.b_char;
			x++;
		}
		y++;
	}
}
int		ft_readfile(char *filename)
{
	FILE *fd;
	int i;

	i = 0;
	if ((fd = fopen(filename, "r")) == NULL)
		return (1);
	if (fscanf(fd, "%d %d %c\n", &g_d.w, &g_d.h, &g_d.b_char) != 3)
		return (1);
	while (i < g_d.h)
	{
		memset(g_d.mapzone[i], g_d.b_char, g_d.w);
		i++;
	}
	while ((i = fscanf(fd, "%c %f %f %f %c\n", &g_r.op, &g_r.x, &g_r.y, &g_r.r, &g_r.b_char)) == 5)
	{
		ft_draw();
	}
	if (i != -1)
		return (1);
	return (0);
}

void    ft_printmap()
{
	int i;

	i = 0;
	while (i < g_d.h)
	{
		ft_putstr(g_d.mapzone[i]);
		ft_putstr("\n");
		i++;
	}
}

int     main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	if (ft_readfile(argv[1]))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	ft_printmap();
	return (0);
}