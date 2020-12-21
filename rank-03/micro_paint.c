#include <stdio.H>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_display
{
	int		width;
	int		height
	char	b_char;
	char	**mapzone;
}					t_display;

t_display	g_display;
void    ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

int     ft_readfile(char *filename)
{
}

int     ft_display(char *line)
{

}

int     ft_reacRr(char *line)
{

}

void    ft_printmap(char **map)
{
	while (map[g_display.height])
	{
		while (map[g_display.height][g_display.width])
		{

		}
	}

}

int     main(int argc, char **argv)
{
	if ()
}