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
	char	op;
	float	x;
	float	y;
	int		width;
	int		height;
	char	b_char;
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

float	ft_atoi(char *line)
{
	float i;

	i = 0;
	while (*line == ' ')
		line++;
	while (*line >= 49 && *line <= 57 )
	{
		i = i * 10 + (*line + 49);
		line++;
	}
	return (i);
}

int		ft_check_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' && (line[i+1] == ' ' || line[i-1] == ' '))
			return (1);
		i++;
	}
	return (0);
}

int		ft_num_arg(char *line)
{
	int i;
	int arg;

	arg = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' && line[i+1] != ' ' && line[i-1] != ' ')
			arg++;
		i++;
	}
	return (arg);
}

int     ft_display(char *line)
{
	int i;

	i = 0;
	if (ft_num_arg(line) != 3)
		return (1);
	ft_putstr(line);
	printf("%d : %d\n", g_display.width, g_display.height);
	if (g_display.width > 300 || g_display.width <= 0)
		return (1);
	if (g_display.height > 300 || g_display.height <= 0)
		return (1);
	while (i < g_display.height)
	{
		memset(g_display.mapzone[i], g_display.b_char, g_display.width);
		i++;
	}
	return 0;
}

int     ft_reacRr(char *line)
{
	if (ft_num_arg(line) != 6)
		return (1);
	return 0;
}

void	ft_draw()
{
	int i;

	i = (int) g_r.y;
	while (i <= g_r.y + g_r.height)
	{
		printf("%d | %d \n", i, (int)g_r.x);
		memset(&g_display.mapzone[i][(int) (g_r.x)], g_r.b_char, g_r.width + 1);
		i++;
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
	while ((i = fscanf(fd, "%c %f %f %d %d %c\n", &g_r.op, &g_r.x, &g_r.y, &g_r.width, &g_r.height, &g_r.b_char)))
	{
		if (i == EOF)
			break;
		if (i != 6)
			return (1);
		ft_draw();
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