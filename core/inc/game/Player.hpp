// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/30 22:38:00 by mc                #+#    #+#             //
//   Updated: 2017/10/02 20:23:20 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "game_util.hpp"
# include "Map.hpp"
# include <string>
# include <list>
# include <climits>

# define INITIAL_BODY_LENGTH 4

# define FOOD_SCORE 3
# define BONUS_SCORE 7 //TODO: this is supposed to be a timer

class Player {
    public:
        Player(
            const std::string &name = "SnakeMan",
            enum player player = PLAYER_A,
            Map * const map = NULL
        );
        Player(Player const &copy);
        ~Player(void);
        Player const &operator=(Player const &copy);

        const std::string &getName() const;
        bool               isAlive() const;
        t_uint             getScore() const;
        enum direction     getDirection() const;

        void               init(t_uint number_of_players);
        void               turn(enum direction direction);
        void               moveForward();

    private:
        void               _move(enum direction direction);
        bool               _eat(game_entity *entity);
        void               _poop();
        void               _die();

        const std::string        _name;
        std::list<game_entity *> _body;
        t_uint                   _score;
        enum direction           _direction;
        enum player              _player;
        t_uint                   _x;
        t_uint                   _y;
        Map              * const _map;
};

#endif // PLAYER_HPP