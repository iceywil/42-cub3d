/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:21:24 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/14 13:30:12 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_game t_game;
typedef struct s_player t_player;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	int		key_up;
	int		key_down;
	int		key_right;
	int		key_left;

	int		left_rotate;
	int		right_rotate;
	t_game	*game;
} t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*addr;
	char		*dst;
	int			bits_pp;
	int			size_line;
	int			endian;
	t_player	player;

	char		**map;
}	t_game;


//init_game.c
void	ft_init_window(t_game *game);
void	ft_init_null_mlx(t_game *data);
void	ft_free_and_exit(t_game *game);
int		ft_close(t_game *game);

//player.c
void	init_player(t_player *player);
int		key_release(int keys, t_player *player);
int		key_press(int keys, t_player *player);
void	move_player(t_player *player);

//game.c
int		ft_game_loop(t_game *game);

//main.c -> utils
int		keys(int keys, t_game *game);
void	ft_put_pixel(int x, int y, int color, t_game *game);
void	ft_draw_square(int x, int y, int color, t_game *game);

//map.c
int		ft_touch(double px, double py, t_game *game);
char	**ft_get_map(void);
void	ft_draw_map(t_game *game);


#endif
