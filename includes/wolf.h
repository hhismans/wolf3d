/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 18:50:27 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/05 08:16:29 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BLOCK_SIZE 64
#define CAMERA_HEIGHT 32
#define CAMERA_ANGLE 60
#define PLAN_HEIGHT 200
#define PLAN_WEIGTH 320
#define WX	780
#define WY 400
#define PLAYER_X 1000
#define PLAYER_Y 500
#define DIR_X -1
#define DIR_Y 0
#define FOV 60

typedef struct	s_vector
{
	double x;
	double y;
}				t_vector;

typedef struct	s_player
{
	t_vector pos;
	t_vector plane;
	t_vector dir;
}				t_player;

typedef struct	s_var
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		camx;
	double		rayx;
	double		rayy;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		ddistx;
	double		ddisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			side;
}				t_var;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	int			**map;
	void		*img;
	t_var		v;
}				t_env;

typedef struct	s_ray
{
	t_vector pos;
	t_vector dir;
}				t_ray;

int			**getinfo(int *nbr_line2, char *file);
