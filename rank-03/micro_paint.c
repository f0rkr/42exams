#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
	int			xt;
	int			yt;
	int			xb;
	int			yb;
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

void	ft_draw(int xt, int yt, int xb, int yb)
{
	while (yt <= yb)
	{
		xt = g_r.xt;
		while (xt <= xb)
		{
			if (g_r.op == 'r' && yt >= 0 && xt >= 0 && (((xt == g_r.xt || xt == g_r.xb)) || ((yt == g_r.yt || yt == g_r.yb))))
				g_display.mapzone[yt][xt] = g_r.b_char;
			else if (g_r.op == 'R' && yt >= 0 && xt >= 0)
				g_display.mapzone[yt][xt] = g_r.b_char;
			xt++;
		}
		yt++;
	}
}

int		ft_check_validity(int x, int y)
{
	if (x >= 0 && x <= g_display.width)
		if (y >= 0 && y <= g_display.height)
			return (1);
	return (0);
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
	while (fscanf(fd, "%c %f %f %f %f %c\n", &g_r.op, &g_r.x, &g_r.y, &g_r.width, &g_r.height, &g_r.b_char) == 6)
	{
		g_r.xt = (int) (g_r.x);
		g_r.yt = (int) (g_r.y);
		g_r.xb = g_r.xt + (int) (g_r.width);
		g_r.yb = g_r.yt + (int) (g_r.height);
		if (((int) (g_r.x * 10) % 10) > 0)
			g_r.xt++;
		if (((int) (g_r.y * 10) % 10) > 0)
			g_r.yt++;
		if (g_r.xb >= g_display.width)
			g_r.xb = g_display.width;
		if (g_r.yb >= g_display.height)
			g_r.yb = g_display.height;
		if (g_r.xt < 0)
			g_r.xt = 0;
		if (g_r.yt < 0)
			g_r.yt = 0;
		ft_draw(g_r.xt, g_r.yt, g_r.xb, g_r.yb);
	}
	fclose(fd);
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