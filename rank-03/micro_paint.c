#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_display
{
	int		width;
	int		height;
	char	b_char;
	char	mapzone[300][300];
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

int     ft_readfile(char const *filename)
{
	FILE *fd;
	char line[100];
	int flag;

	flag = 0;
	if ((fd = fopen(filename, "r")) == NULL)
		return (1);
	while ((fscanf(fd, "%[^\n]\n%*c", line)) != EOF)
	{
		if (ft_check_space(line))
			retrun (1);
		if (*line == 'r' || *line == 'R')
		{
			if (ft_reacRr(line))
				return (1);
			flag = 1;
		}
		if ((*line >= 48 && *line <= 57) && flag == 0)
		{
			if (ft_display(line))
				return (1);
			flag = 1;
		}
		else
			return (1);
	}
	fclose(fd);
	return (0);
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

	arg = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i+1] != ' ' && line[i-1] != ' '))
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
	g_display.width = ft_atoi(*line);
	g_display.height = ft_atoi(*line);
	g_display.b_char = ft_atoi(*line);
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