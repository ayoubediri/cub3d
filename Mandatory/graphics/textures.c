/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiri <adiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 06:26:24 by adiri             #+#    #+#             */
/*   Updated: 2025/09/15 17:24:27 by adiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_wall_textures(void)
{
	static t_texture	wall_textures[WALL_TOTAL];

	return (wall_textures);
}



t_texture	load_texture(char *path)
{
	t_mlx		*mlx;
	t_texture	texture;

	mlx = &get_game()->mlx;
	ft_memset(&texture, 0, sizeof(t_texture));
	texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width,
			&texture.height);
	if (!texture.img_ptr)
	{
		report_error("mlx", "failed to load texture from path");
		leave_game(1);
	}
	texture.addr = mlx_get_data_addr(texture.img_ptr, &texture.bpp,
			&texture.len_line, &texture.endian);
	if (!texture.addr)
	{
		report_error("mlx", "failed to get texture data address");
		mlx_destroy_image(mlx->mlx, texture.img_ptr);
		leave_game(1);
	}
	texture.path = path;
	return (texture);
}



void	setup_textures(void)
{
	t_game		*game;
	t_texture	*wall_textures;

	game = get_game();
	wall_textures = get_wall_textures();
	wall_textures[WALL_NORTH] = load_texture(game->parse.no_texture);
	wall_textures[WALL_SOUTH] = load_texture(game->parse.so_texture);
	wall_textures[WALL_EAST] = load_texture(game->parse.ea_texture);
	wall_textures[WALL_WEST] = load_texture(game->parse.we_texture);
}


void	destroy_wall_textures(t_mlx *mlx)
{
	t_texture	*wall_textures;
	int			i;

	wall_textures = get_wall_textures();
	i = 0;
	while (i < WALL_TOTAL)
	{
		if (wall_textures[i].img_ptr)
			mlx_destroy_image(mlx->mlx, wall_textures[i].img_ptr);
		i++;
	}
}



void	calc_tex_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)ray->wall->width);
	if (ray->side == 0 && ray->dir_x < 0)
		ray->tex_x = ray->wall->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		ray->tex_x = ray->wall->width - ray->tex_x - 1;
	if (ray->tex_x >= ray->wall->width)
		ray->tex_x = ray->wall->width - 1;
	else if (ray->tex_x < 0)
		ray->tex_x = 0;
}
