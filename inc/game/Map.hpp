// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Map.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/30 15:00:16 by mc                #+#    #+#             //
//   Updated: 2017/10/02 19:21:32 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAP_HPP
# define MAP_HPP

# include "game_util.hpp"
# include <cstdlib>
# include <cstring>
# include <ctime>

# define MIN_WIDTH      9
# define MAX_WIDTH      1000
# define DEFAULT_WIDTH  16

# define MIN_HEIGHT     9
# define MAX_HEIGHT     1000
# define DEFAULT_HEIGHT 16

# ifdef VERBOSE
#  define DEBUG_MAP(map) (map).print()
# else
#  define DEBUG_MAP(map) do {} while(0)
# endif

class Map {
    public:
        Map(
            const t_uint width = DEFAULT_WIDTH,
            const t_uint height = DEFAULT_HEIGHT
        );
        Map(Map const &copy);
        ~Map(void);
        Map const &operator=(Map const &copy);

        void          print() const;
        game_entity   get(t_uint x, t_uint y) const;
        game_entity **getArea() const;
        t_uint        getWidth() const;
        t_uint        getHeight() const;
        bool          growFood(game_entity food);

    private:
        bool          _allocArea();
        void          _freeArea();
        game_entity  *_findEmptySpot();

        game_entity **_area;
        const t_uint  _width;
        const t_uint  _height;
};

#endif // MAP_HPP
