/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:57:13 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 13:04:21 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_BONUS_H
# define PROTOTYPES_BONUS_H

// * =========== Parsing =========== *
// * Parse *
void	parse(char *path);
// * Validate *
void	validate_map(void);
// * Map *
void	parse_map_line(char *line);
// * Elements *
void	check_elements(void);
void	parse_elements(char *line);

// * =========== Helpers =========== *
// * Gnl *
char	*get_next_line(int fd);
// * Char *
int		is_empty_string(char *str);
// * Numbers *
char	*ft_itoa(int n);
// * Strjoin *
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strjoin2(char *s1, char *s2);
// * Static *
t_parse	*get_parse(void);
t_game	*get_game(void);
t_map	*get_map(void);
// * Strdup *
char	*ft_strndup(char *str, size_t n);
char	*ft_strsdup(char *str);
char	*ft_strdup(char *str);
// * Error Handling *
int		report_error(char *msg1, char *msg2);
void	parse_error(char *msg1);
void	clean_exit(int status);
void	cleanup(void);
// * Memory *
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	*track(void *ptr, size_t size);
void	*ft_malloc(size_t size);

#endif