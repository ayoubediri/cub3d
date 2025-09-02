/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:23:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/24 20:24:09 by yjazouli         ###   ########.fr       */
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

void des_enemy_textures(void)
{
	t_texture	**enemy;
	t_mlx		*mlx;

	enemy = enemy_texture();
	if (!enemy)
		return;
	mlx = get_mlx();
	mlx_destroy_image(mlx->mlx, enemy[0][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[0][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[0][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[1][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[2][3].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][0].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][1].img_ptr);
	mlx_destroy_image(mlx->mlx, enemy[3][3].img_ptr);
}

int	leave_game(int exit_code)
{
	t_game	*game;
	t_mlx	*mlx;

	game = get_game();
	mlx = get_mlx();
	if (game->gameplay.pellet_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->gameplay.pellet_texture.img_ptr);
	if (game->gameplay.ghost_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->gameplay.ghost_texture.img_ptr);
	for (int i = 0; i < WALL_TOTAL; i++)
	{
		if (game->wall_textures[i].img_ptr)
			mlx_destroy_image(mlx->mlx, game->wall_textures[i].img_ptr);
	}
	des_enemy_textures();
	if (game->floor_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->floor_texture.img_ptr);
	if (game->ceiling_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->ceiling_texture.img_ptr);
	if (game->sky_texture.img_ptr)
		mlx_destroy_image(mlx->mlx, game->sky_texture.img_ptr);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
	stop_background_music();
	clean_exit(exit_code);
	return (1);
}

void	update_camera(void)
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

void	stop_background_music(void)
{
	t_gameplay	*gameplay;

	gameplay = get_gameplay();
	if (gameplay->start_game_sound)
		kill(gameplay->pid_sound, SIGKILL);
	gameplay->start_game_sound = 0;
}

void	lose_screen(void)
{
	t_mlx		*mlx;
	t_texture	lose_texture;

	mlx = get_mlx();
	lose_texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx, LOSE_TEXTURE_PATH,
			&lose_texture.width, &lose_texture.height);
	if (!lose_texture.img_ptr)
	{
		fprintf(stderr, "Failed to load lose texture\n");
		leave_game(1);
	}
	lose_texture.addr = mlx_get_data_addr(lose_texture.img_ptr,
			&lose_texture.bpp, &lose_texture.line_length, &lose_texture.endian);
	if (!lose_texture.addr)
	{
		fprintf(stderr, "Failed to get lose texture data address\n");
		mlx_destroy_image(mlx->mlx, lose_texture.img_ptr);
		leave_game(1);
	}
	stop_background_music();
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_put_image_to_window(mlx->mlx, mlx->win, lose_texture.img_ptr, HALF_WIDTH
		- 256, HALF_HEIGHT - 256);
	mlx_do_sync(mlx->mlx);
	system("aplay -q " LOSE_SOUND_PATH " &");
	mlx_destroy_image(mlx->mlx, lose_texture.img_ptr);
	sleep(4);
}

void	game_update(double dt)
{
	t_gameplay	*gp;

	update_movement();
	update_camera();
	minimap_update(dt);
	ghosts_update(dt);
	timers_update(dt);
	{
		gp = get_gameplay();
		if (gp && gp->player.ent && gp->player.ent->hp <= 0)
		{
			lose_screen();
			fprintf(stderr, "Player died\n");
			leave_game(0);
		}
	}
}

static void	draw_crosshair(void)
{
    int		cx = HALF_WIDTH;
    int		cy = HALF_HEIGHT;
    int		len = 8;
    int		gap = 2;
    uint32_t	color = 0xFFFFFFFF;
    int		i;

    i = gap + 1;
    while (i <= len)
    {
        pixel_put(cx + i, cy, color);
        pixel_put(cx - i, cy, color);
        i++;
    }
    i = gap + 1;
    while (i <= len)
    {
        pixel_put(cx, cy + i, color);
        pixel_put(cx, cy - i, color);
        i++;
    }
    pixel_put(cx, cy, color);
}

void	game_render(double alpha)
{
	(void)alpha;
	// clear_image();
	raycasting();
	minimap_render();
	render_health_ui();
	draw_crosshair();
	put_image();
}

t_texture	load_texture(char *path)
{
	t_mlx		*mlx;
	t_texture	texture;

	mlx = get_mlx();
	memset(&texture, 0, sizeof(t_texture));
	texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width,
			&texture.height);
	if (!texture.img_ptr)
	{
		report_error("mlx", "failed to load texture from path");
		printf("Texture path: %s\n", path);
		leave_game(1);
	}
	texture.addr = mlx_get_data_addr(texture.img_ptr, &texture.bpp,
			&texture.line_length, &texture.endian);
	if (!texture.addr)
	{
		report_error("mlx", "failed to get texture data address");
		leave_game(1);
	}
	texture.path = path;
	return (texture);
}

t_texture	**enemy_texture(void)
{
	static t_texture enemy1[4];
	static t_texture enemy2[4];
	static t_texture enemy3[4];
	static t_texture enemy4[4];
	static t_texture *enemy[4] = {enemy1, enemy2, enemy3, enemy4};
	return (enemy);
}

void	init_ghosts_textures(void)
{
	t_game		*game;
	t_texture	**enemy_textures;
	int			idx;
	int			i;

	game = get_game();
	enemy_textures = enemy_texture();
	i = 0;
	while (i < game->gameplay.ghost_count)
	{
		idx = game->gameplay.ghosts[i].ent->tex_idx;
		if (idx < 0 || idx >= 4)
			idx = 0;
		game->gameplay.ghosts[i].ent->texture = &enemy_textures[idx][0];
		i++;
	}
}

void	config_textures(void)
{
	t_parse		*parse;
	t_game		*game;
	t_texture	**enemy;

	parse = get_parse();
	game = get_game();
	enemy = enemy_texture();
	enemy[0][0] = load_texture(ENEMY1_TEXTURE_MED);
	enemy[0][1] = load_texture(ENEMY1_TEXTURE_DOWN);
	enemy[0][2] = enemy[0][0];
	enemy[0][3] = load_texture(ENEMY1_TEXTURE_UP);
	enemy[1][0] = load_texture(ENEMY2_TEXTURE_MED);
	enemy[1][1] = load_texture(ENEMY2_TEXTURE_DOWN);
	enemy[1][2] = enemy[1][0];
	enemy[1][3] = load_texture(ENEMY2_TEXTURE_UP);
	enemy[2][0] = load_texture(ENEMY3_TEXTURE_MED);
	enemy[2][1] = load_texture(ENEMY3_TEXTURE_DOWN);
	enemy[2][2] = enemy[2][0];
	enemy[2][3] = load_texture(ENEMY3_TEXTURE_UP);
	enemy[3][0] = load_texture(ENEMY4_TEXTURE_MED);
	enemy[3][1] = load_texture(ENEMY4_TEXTURE_DOWN);
	enemy[3][2] = enemy[3][0];
	enemy[3][3] = load_texture(ENEMY4_TEXTURE_UP);
	game->wall_textures[WALL_NORTH] = load_texture(parse->no_texture);
	game->wall_textures[WALL_SOUTH] = load_texture(parse->so_texture);
	game->wall_textures[WALL_EAST] = load_texture(parse->ea_texture);
	game->wall_textures[WALL_WEST] = load_texture(parse->we_texture);
	game->floor_texture = load_texture(FLOOR_TEXTURE_PATH);
	game->ceiling_texture = load_texture(CEILING_TEXTURE_PATH);
	game->sky_texture = load_texture(SKY_TEXTURE_PATH);
	game->gameplay.ghost_texture = load_texture(GHOST_TEXTURE_PATH);
	game->gameplay.pellet_texture = load_texture(PELLET_TEXTURE_PATH);
	game->gameplay.door_texture_close = load_texture(DOOR_TEXTURE_CLOSE_PATH);
	init_ghosts_textures();
}

int	mouse_handler(int x, int y, t_mlx *mlx)
{
	double		dx;
	double		angle;
	t_entity	*player;

	(void)mlx;
	(void)y;
	dx = x - HALF_WIDTH;
	if (fabs(dx) < 2)
		return (0);
	angle = dx * MOUSE_SENSITIVITY;
	player = get_gameplay()->player.ent;
	rotate_player(player, angle);
	mlx_mouse_move(get_mlx()->mlx, get_mlx()->win, HALF_WIDTH, HALF_HEIGHT);
	return (0);
}

void	start_screen(void)
{
	t_mlx		*mlx;
	t_gameplay	*gameplay;
	t_texture	*texture;

	mlx = get_mlx();
	gameplay = get_gameplay();
	gameplay->start_game_sound = 0;
	texture = &gameplay->start_screen_texture;
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx,
			START_SCREEN_TEXTURE_PATH, &texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		report_error("mlx", "failed to load start screen texture");
		leave_game(1);
	}
	gameplay->start_screen_texture.addr = mlx_get_data_addr(gameplay->start_screen_texture.img_ptr,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!gameplay->start_screen_texture.addr)
	{
		report_error("mlx", "failed to get start screen texture data address");
		leave_game(1);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, gameplay->start_screen_texture.img_ptr, HALF_WIDTH - 256, HALF_HEIGHT - 256);
	system("aplay -q " START_SCREEN_SOUND_PATH " &");
	sleep(3);
	mlx_destroy_image(mlx->mlx, gameplay->start_screen_texture.img_ptr);
}

void	*start_music_thread(void *arg)
{
	t_gameplay	*gameplay;

	(void)arg;
	gameplay = get_gameplay();
	while (gameplay->start_game_sound)
	{
		gameplay->pid_sound = fork();
		if (gameplay->pid_sound == 0)
		{
			execlp("aplay", "aplay", "-q", BACKGROUND_MUSIC_PATH, NULL);
			leave_game(1);
		}
		waitpid(gameplay->pid_sound, NULL, 0);
	}
	return (NULL);
}

void	start_music(void)
{
	t_gameplay	*gameplay;
	pthread_t	thread;

	gameplay = get_gameplay();
	gameplay->start_game_sound = 1;
	gameplay->pid_sound = 0;
	pthread_create(&thread, NULL, start_music_thread, NULL);
	pthread_detach(thread);
}

void	start_game(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		report_error("mlx", "failed to initialize session");
		leave_game(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		report_error("mlx", "failed to create window");
		leave_game(1);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line,
			&mlx->endian);
	start_screen();
	config_textures();
	mlx_mouse_hide(mlx->mlx, mlx->win);
	start_music();
	mlx_hook(mlx->win, 6, 1L << 6, mouse_handler, NULL);
	mlx_hook(mlx->win, 17, 1L << 17, leave_game, NULL);
	mlx_hook(mlx->win, 2, 1L << 0, on_keypress, NULL);
	mlx_hook(mlx->win, 3, 1L << 1, on_keyrelease, NULL);
	mlx_loop_hook(mlx->mlx, game_loop, NULL);
	mlx_loop(mlx->mlx);
}
