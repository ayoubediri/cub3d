/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:27:31 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 21:02:06 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

static inline int	bfs_idx(int x, int y, int w)
{
    return (y * w + x);
}

void	bfs_idx_to_xy(int idx, int w, int *x, int *y)
{
    *x = idx % w;
    *y = idx / w;
}

void	bfs_free(t_bfs *bfs)
{
    if (!bfs)
        return ;
    if (bfs->came)
        ft_free(bfs->came);
    if (bfs->queue)
        ft_free(bfs->queue);
    if (bfs->visited)
        ft_free(bfs->visited);
    if (bfs->path)
        ft_free(bfs->path);
    memset(bfs, 0, sizeof(t_bfs));
}

int	bfs_init(t_bfs *bfs, int width, int height)
{
    if (!bfs || width <= 0 || height <= 0)
        return (0);
    memset(bfs, 0, sizeof(t_bfs));
    bfs->width = width;
    bfs->height = height;
    bfs->n = width * height;
    bfs->queue_capacity = bfs->n;
    bfs->path_capacity = bfs->n;
    bfs->visit_stamp = 1;
    bfs->came = (int *)ft_malloc(sizeof(int) * bfs->n);
    bfs->queue = (int *)ft_malloc(sizeof(int) * bfs->queue_capacity);
    bfs->visited = (int *)ft_malloc(sizeof(int) * bfs->n);
    bfs->path = (int *)ft_malloc(sizeof(int) * bfs->path_capacity);
    if (!bfs->came || !bfs->queue || !bfs->visited || !bfs->path)
    {
        bfs_free(bfs);
        return (0);
    }
    memset(bfs->visited, 0, sizeof(int) * bfs->n);
    return (1);
}

static void	bfs_reset_for_run(t_bfs *bfs)
{
    int	i;

    if (!bfs)
        return ;
    bfs->queue_start = 0;
    bfs->queue_end = 0;
    bfs->path_length = 0;
    bfs->visit_stamp++;
    if (bfs->visit_stamp <= 0)
    {
        bfs->visit_stamp = 1;
        i = 0;
        while (i < bfs->n)
        {
            bfs->visited[i] = 0;
            i++;
        }
    }
    i = 0;
    while (i < bfs->n)
    {
        bfs->came[i] = -1;
        i++;
    }
}

static int	bfs_reconstruct_path(t_bfs *bfs)
{
    int	len;
    int	cur;
    int	i;

    if (!bfs || bfs->goal < 0)
        return (0);
    len = 0;
    cur = bfs->goal;
    while (cur != -1)
    {
        len++;
        cur = bfs->came[cur];
    }
    if (len > bfs->path_capacity)
        return (0);
    cur = bfs->goal;
    i = len - 1;
    while (i >= 0)
    {
        bfs->path[i] = cur;
        cur = bfs->came[cur];
        i--;
    }
    bfs->path_length = len;
    return (1);
}

int	bfs_find_path(t_bfs *bfs, t_map *map, int sx, int sy, int tx, int ty)
{
    int			cur;
    int			cx;
    int			cy;
    int			k;
    const int	dx[4] = {-1, 1, 0, 0};
    const int	dy[4] = {0, 0, -1, 1};

    if (!bfs || !map || !map->grid)
        return (0);
    if (sx < 0 || sx >= bfs->width || sy < 0 || sy >= bfs->height)
        return (0);
    if (tx < 0 || tx >= bfs->width || ty < 0 || ty >= bfs->height)
        return (0);
    bfs->start = bfs_idx(sx, sy, bfs->width);
    bfs->goal = bfs_idx(tx, ty, bfs->width);
    if (map->grid[bfs->start] == 1 || map->grid[bfs->goal] == 1)
        return (0);
    bfs_reset_for_run(bfs);
    bfs->queue[bfs->queue_end++] = bfs->start;
    bfs->visited[bfs->start] = bfs->visit_stamp;
    while (bfs->queue_start < bfs->queue_end)
    {
        cur = bfs->queue[bfs->queue_start++];
        if (cur == bfs->goal)
            break ;
        bfs_idx_to_xy(cur, bfs->width, &cx, &cy);
        k = 0;
        while (k < 4)
        {
            int	nx = cx + dx[k];
            int	ny = cy + dy[k];
            int	nid;

            if (nx < 0 || ny < 0 || nx >= bfs->width || ny >= bfs->height)
            {
                k++;
                continue ;
            }
            nid = bfs_idx(nx, ny, bfs->width);
            if (bfs->visited[nid] == bfs->visit_stamp || map->grid[nid] == 1)
            {
                k++;
                continue ;
            }
            bfs->visited[nid] = bfs->visit_stamp;
            bfs->came[nid] = cur;
            bfs->queue[bfs->queue_end++] = nid;
            k++;
        }
    }
    if (bfs->visited[bfs->goal] != bfs->visit_stamp)
        return (0);
    return (bfs_reconstruct_path(bfs));
}
