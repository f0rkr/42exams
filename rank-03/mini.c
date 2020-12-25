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
	char		op[300];
	float		xtl[300];
	float		ytl[300];
    float		xbr[300];
	float		ybr[300];
	float		width;
	float		height;
	char		b_char[300];
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


int     ft_is_rect(int x, int y, int j)
{
    if (x >= (int) g_r.xtl[j] && x <= (int) g_r.xbr[j])
        if (y >= (int) g_r.ytl[j] && y <= (int) g_r.ybr[j])
            return (1);
    return (0);
}

void	ft_draw(int x, int y, int j)
{
	g_display.mapzone[y][x] = g_r.b_char[j];
}

int     ft_readfile(char const *filename)
{
	FILE *fd;
	int i;
    int j;
    int y;
    int x;

    x = 0;
    y = 0;
	i = 0;
    j = 0;
	if ((fd = fopen(filename, "r")) == NULL)
		return (1);
	if (fscanf(fd, "%d %d %c\n", &g_display.width, &g_display.height, &g_display.b_char) != 3)
		return (1);
	while (i < g_display.height)
	{
		memset(g_display.mapzone[i], g_display.b_char, g_display.width);
		i++;
	}
	while ((i = fscanf(fd, "%c %f %f %f %f %c \n", &g_r.op[j], &g_r.xtl[j], &g_r.ytl[j], &g_r.width, &g_r.height, &g_r.b_char[j])) == 6)
	{
        g_r.xbr[j] = g_r.xtl[j] + g_r.width;
        g_r.ybr[j] = g_r.ytl[j] + g_r.height;
        j++;
	}
	if (i != -1)
    {
        fclose(fd);
		return (1);
    }
    i = 0;
    while (y <= g_display.height)
    {
        x = 0;
        while(x <= g_display.width)
        {
            i = 0;
            while (i <= j)
            {
                if (ft_is_rect(x, y, i))
                    ft_draw(x, y, i);
                i++;
            }
            x++;
        }
        y++;
    }
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