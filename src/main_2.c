/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 06:25:50 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/08 22:14:06 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"

void	set_vars(t_env *e, char *file)
{
	int nbr_line;

	e->map = getinfo(&nbr_line, file);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WX, WY, "wolf");
	e->img = mlx_new_image(e->mlx, WX, WY);
	e->v.posx = 5;
	e->v.posy = 5;
	e->v.dirx = -1;
	e->v.diry = 0;
	e->v.planx = 0;
	e->v.plany = 0.66;
	e->tx_hitler.img = mlx_new_image(e->mlx, 64, 64);
	e->tx_hitler.img = mlx_xpm_file_to_image(e->mlx, "./xpm/hitler.xpm",
			&(e->tx_hitler.w), &(e->tx_hitler.h));
}

void update_fram(t_env *e)
{
	ft_putendl("updating frame begin");
	int x;
	int lineHeight;

	t_point p1;
	t_point p2;
	t_point p3;
	x = 0;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WX, WY);
	while (x < WX)
	{
		lineHeight = raycaster(e, x);
		ft_putendl("just after raycasting");
		ft_putstr("x = ");
		ft_putnbr(x);
		ft_putstr("\nlineHeight = ");
		ft_putnbr(lineHeight);
		ft_putendl("");
		p1.x = x;
		p2.x = x;
		p1.y = WY / 2 + lineHeight / 2;
		p2.y = WY / 2 - lineHeight / 2;
	/*	if (e->v.side)
			ft_drawline_img_c(e->img, p1, p2, BLUE);//rainbow_gen(x));
		else
			ft_drawline_img_c(e->img, p1, p2, BLUE + 0x003300);//rainbow_gen(x));*/
		p3.y = 0;
		p3.x = x;
		ft_drawline_img_c(e->img, p3, p2, 0xA7A37E);//rainbow_gen(x));
		p3.y = WY;
		ft_drawline_img_c(e->img, p3, p1, 0x787746);//rainbow_gen(x));
		x++;
	}
	ft_putendl("just before put image to window");
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_putendl("updating frame end");
}

void rot_cam(t_env *e, double angle)
{
	double oldDirX;
	double oldPlaneX;
   
	oldPlaneX= e->v.planx;
	oldDirX = e->v.dirx;
	e->v.dirx = e->v.dirx * cos(angle) - e->v.diry * sin(angle);
	e->v.diry = oldDirX * sin(angle) + e->v.diry * cos(angle);
	e->v.planx = e->v.planx * cos(angle) - e->v.plany * sin(angle);
	e->v.plany = oldPlaneX * sin(angle) + e->v.plany * cos(angle);
}

int main(int argc, char **argv)
{
	t_env e;

	set_vars(&e, argv[1]);
	mlx_put_image_to_window(e.mlx, e.win, e.tx_hitler.img, 0, 0);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
