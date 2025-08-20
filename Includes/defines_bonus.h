/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:27 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/20 10:52:38 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

// * ========= Defines ========== *

# define BUFFER_SIZE 1024

// * ======== Enums ========== *

typedef enum e_parse_state
{
	PARSE_ELEMENTS,
	PARSE_MAP_LINES
}	t_parse_state;

#endif