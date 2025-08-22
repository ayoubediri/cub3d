/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 21:20:12 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	game_loop(void)
{
	t_engine	*engine;

	engine = get_engine();
	game_tick(engine);
	return (0);
}

static int	leave_game(void)
{
	clean_exit(0);
	return (1);
}


// void	rotate_player(t_player *p, double dir)
// {
// 	double	dir_x;
// 	double	dir_y;
// 	double	angle;

// 	if (!p)
// 		return ;
// 	angle = dir * ROT_SPEED;
// 	dir_x = p->ent->dir.x * ;
// 	// p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
// 	// p->dir_y = p->dir_x * sin(angle) + p->dir_y * cos(angle);
// 	// old_planex = p->plane_x;
// 	// p->plane_x = old_planex * cos(angle) - p->plane_y * sin(angle);
// 	// p->plane_y = old_planex * sin(angle) + p->plane_y * cos(angle);
// }

void update_camera(void)
{
	t_gameplay	*gameplay;
	t_camera	*camera;

	gameplay = get_gameplay();
	camera = &gameplay->camera;
	camera->pos.x = gameplay->player.ent->pos.x;
	camera->pos.y = gameplay->player.ent->pos.y;
	camera->dir.x = gameplay->player.ent->dir.x;
	camera->dir.y = gameplay->player.ent->dir.y;
	camera->plane.x = -camera->dir.y * camera->plane_scale;
	camera->plane.y = camera->dir.x * camera->plane_scale;
}

void	game_update(double dt)
{
	(void)dt;

	update_movement();
	update_camera();
	minimap_update(dt);
	entities_update(dt);

	{
        t_gameplay *gp = get_gameplay();
        if (gp && gp->player.ent && gp->player.ent->hp <= 0)
        {
            fprintf(stderr, "Player died\n");
            clean_exit(0);
        }
    }

}

void	game_render(double alpha)
{
	(void)alpha;
	// clear_image();
	raycasting();
	minimap_render();
	put_image();
}

void	start_game(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		report_error("mlx", "failed to initialize session");
		clean_exit(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		report_error("mlx", "failed to create window");
		clean_exit(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line,
			&mlx->endian);
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
