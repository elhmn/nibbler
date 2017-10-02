// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   game_util.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/30 22:46:24 by mc                #+#    #+#             //
//   Updated: 2017/10/02 00:11:55 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAME_UTIL_HPP
# define GAME_UTIL_HPP

# include "log.hpp"

# define ABS(x) ((x) > 0 ? (x) : (-x))

typedef unsigned int t_uint;

enum game_entity : char {
    OUTER_WALL = '\0',
    INNER_WALL = 'w',
    FRUIT = 'f',
    BONUS = 'b',
    SNAKE_A = '1',
    SNAKE_B = '2',
    SNAKE_C = '3',
    SNAKE_D = '4',
    EMPTY = ' ',
};

enum direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE,
};

enum player {
    PLAYER_A = 0,
    PLAYER_B = 1,
    PLAYER_C = 2,
    PLAYER_D = 3,
};
# define MAX_PLAYERS 4


#endif // GAME_UTIL_HPP