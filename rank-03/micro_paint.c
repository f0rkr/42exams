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

int		ft_check_validity(float x, float y, float xb, float yb)
{
	if (x >= 0 && x < g_display.width)
		if (y >= 0 && y < g_display.height)
			return (1);
	return (0);
}

int		ft_check_empty(float x, float y, float xb, float yb)
{
	if ((x == g_r.xt || x == xb) || (y == g_r.yt || y == yb))
		return (1);
	return (0);
}

void	ft_draw(float xt, float yt, float xb, float yb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (yt <= yb)
	{
		xt = g_r.x;
		while (xt <= xb)
		{
			j++;
			if (g_r.op == 'r' && ft_check_validity(xt, yt, xb, yb) && ft_check_empty(xt, yt, xb, yb))
				g_display.mapzone[(int)yt][(int)xt] = g_r.b_char;
			else if (g_r.op == 'R' && ft_check_validity(xt, yt, xb, yb))
				g_display.mapzone[(int)yt][(int)xt] = g_r.b_char;
			else
			{
				if (ft_check_validity(xt, yt, xb, yb))
					printf("NO: %c:%c %f:%f %f:%f %f %f check_validity: %d check_empty: %d\n", g_r.op, g_r.b_char, g_r.xt, xt, g_r.yt, yt, g_r.xb, g_r.yb, ft_check_validity(xt, yt, xb, yb), ft_check_empty(xt, yt, xb, yb));
			}
			
			xt++;
		}
		i++;
		yt++;
	}
	// printf("%c : %d %d\n", g_r.b_char, i, j);
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
		if (((int) (g_r.x * 10) % 10) > 0)
		{
			g_r.x++;
		}
		if (((int) (g_r.y * 10) % 10 ) > 0)
		{
			g_r.y++;
		}
		g_r.xt = (int) g_r.x;
		g_r.yt = (int) g_r.y;
		// printf("%c %f %f %f %f\n", g_r.op, g_r.x, g_r.y, g_r.width, g_r.height);
		// printf("%c %f %f %f %f\n", g_r.op, g_r.xt, g_r.yt, g_r.xb, g_r.yb);
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