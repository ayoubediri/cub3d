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

t_texture load_texture(char *path)
{
	t_mlx		*mlx;
	t_texture	texture;

	mlx = get_mlx();
	texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width, &texture.height);
	if (!texture.img_ptr)
	{
		report_error("mlx", "failed to load texture from path");
		printf("Texture path: %s\n", path);
		clean_exit(1);
	}
	texture.addr = mlx_get_data_addr(
		texture.img_ptr, &texture.bpp, &texture.line_length, &texture.endian);
	if (!texture.addr)
	{
		report_error("mlx", "failed to get texture data address");
		clean_exit(1);
	}
	texture.path = path;
	return (texture);
}

void config_textures(void)
{
	t_parse		*parse;
	t_game		*game;

	parse = get_parse();
	game = get_game();
	game->wall_textures[WALL_NORTH] = load_texture(parse->no_texture);
	game->wall_textures[WALL_SOUTH] = load_texture(parse->so_texture);
	game->wall_textures[WALL_EAST] = load_texture(parse->ea_texture);
	game->wall_textures[WALL_WEST] = load_texture(parse->we_texture);
	game->floor_texture = load_texture(FLOOR_TEXTURE_PATH);
	game->ceiling_texture = load_texture(CEILING_TEXTURE_PATH);
	game->sky_texture = load_texture(SKY_TEXTURE_PATH);
}

int mouse_handler(int x, int y, t_mlx *mlx)
{
	double		dx;
	double		angle;
	t_entity	*player;

	(void)mlx;
	dx = x - HALF_WIDTH;
	if (fabs(dx) < 2)
        return (0);
	angle = dx * MOUSE_SENSITIVITY;
	player = get_gameplay()->player.ent;
	rotate_player(player, angle);
	mlx_mouse_move(get_mlx()->mlx, get_mlx()->win, HALF_WIDTH, HALF_HEIGHT);
	return (0);
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
	config_textures();
	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_handler, NULL);
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
