#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct		s_display
{
	int		width;
	int		height;
	char	b_char;
	char	mapzone[300][300];
}					t_display;

typedef struct		s_rect
{
	char		op;
	float		x;
	float		y;
	float		width;
	float		height;
	char		b_char;
	float			xt;
	float			yt;
	float			xb;
	float			yb;
}					t_rect;

t_display	g_display;
t_rect		g_r;

void    ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

int		ft_check_empty(float x, float y)
{
	if ((((x < g_r.xt) || (g_r.xb < x)) || (y < g_r.yt)) || (g_r.yb < y))
		return (0);
	if (((x - g_r.xt < 1.00000000) || (g_r.xb - x < 1.00000000)) ||
		((y - g_r.yt < 1.00000000 || (g_r.yb - y < 1.00000000))))
		return (2);
	return (1);
}

void	ft_draw(float xt, float yt, float xb, float yb)
{
	int x;
	int y;
	
	y = 0;
	while (y < g_display.height)
	{
		x = 0;
		while (x < g_display.width)
		{
			if (ft_check_empty((float) x, (float) y) == 2 || (ft_check_empty((float) x, (float) y) != 0 && g_r.op == 'R'))
				g_display.mapzone[y][x] = g_r.b_char;
			x++;
		}
		y++;
	}
}

int     ft_readfile(char const *filename)
{
	FILE *fd;
	int i;

	i = 0;
	if ((fd = fopen(filename, "r")) == NULL)
		return (1);
	if (fscanf(fd, "%d %d %c\n", &g_display.width, &g_display.height, &g_display.b_char) != 3)
		return (1);
	while (i < g_display.height)
	{
		memset(g_display.mapzone[i], g_display.b_char, g_display.width);
		i++;
	}
	while ((i = fscanf(fd, "%c %f %f %f %f %c \n", &g_r.op, &g_r.x, &g_r.y, &g_r.width, &g_r.height, &g_r.b_char)) == 6)
	{
		g_r.xb = g_r.x + g_r.width;
		g_r.yb = g_r.y + g_r.height;
		g_r.xt = g_r.x;
		g_r.yt = g_r.y;
		ft_draw(g_r.xt, g_r.yt, g_r.xb , g_r.yb);
	}
	fclose(fd);
	if (i != -1)
		return (1);
	return (0);
}

void    ft_printmap()
{
	int i;

	i = 0;
	while (i < g_display.height)
	{
		ft_putstr(g_display.mapzone[i]);
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