// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Map.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/30 15:00:18 by mc                #+#    #+#             //
//   Updated: 2017/10/04 19:45:20 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Map.hpp"

/*
** constructor
*/
Map::Map(const t_uint width, const t_uint height) :
    _area(NULL),
    _width(width),
    _height(height)
{
    DEBUG("Map constructor");

    if (!this->_allocArea()) {
        ERROR("error: map malloc bjorked");
        return;
    }

    this->growFood(FOOD);
}

Map::Map(Map const &copy) :
    _area(NULL),
    _width(copy.getWidth()),
    _height(copy.getHeight())
{
    WARNING("Map copy constructor : don't expect this to be useful");

    *this = copy;
}


/*
** destructor
*/
Map::~Map(void)
{
    DEBUG("Map destructor");

    this->_freeArea();
}


/*
** operator overload
*/
Map const      &Map::operator=(Map const &copy)
{
    WARNING("Map operator= : don't expect this to be useful");

    (void)copy;
    return *this;
}


/*
** public
*/
game_entity     Map::get(t_uint x, t_uint y) const
{
    if (x >= this->_width || y >= this->_height) {
        return OUTER_WALL;
    }

    return this->_area[y][x];
}

game_entity   **Map::getArea() const
{
    return this->_area;
}

t_uint          Map::getWidth() const
{
    return this->_width;
}

t_uint          Map::getHeight() const
{
    return this->_height;
}

game_entity    *Map::growFood(game_entity food)
{
    game_entity *empty_spot;

    if (food != FOOD && food != BONUS) {
        return NULL;
    }

    empty_spot = this->_findEmptySpot();
    if (!empty_spot) {
        return NULL;
    }

    *empty_spot = food;

    return empty_spot;
}

void            Map::print() const
{
    DEBUG('+' << std::string(this->_width, '-') << '+');
    for (t_uint y = 0; y < this->_height; y++) {
        DEBUG('|' << reinterpret_cast<const char *>(this->_area[y]) << '|');
    }
    DEBUG('+' << std::string(this->_width, '-') << '+');
}



/*
** private
*/
bool            Map::_allocArea()
{
    this->_area = static_cast<game_entity **>(
        malloc(sizeof(game_entity *) * (this->_height + 1))
    );
    if (!this->_area) {
        return false;
    }
    this->_area[this->_height] = NULL;

    for (t_uint y = 0; y < this->_height; y++) {
        this->_area[y] = static_cast<game_entity *>(
            malloc(sizeof(game_entity) * (this->_width + 1))
        );
        if (!this->_area) {
            return false;
        }
        memset(this->_area[y], EMPTY, this->_width);
        this->_area[y][this->_width] = OUTER_WALL;
    }

    this->_area[0][this->_width / 2] = INNER_WALL;
    this->_area[this->_height - 1][this->_width / 2] = INNER_WALL;
    this->_area[this->_height / 2][0] = INNER_WALL;
    this->_area[this->_height / 2][this->_width - 1] = INNER_WALL;

    return true;
}

void            Map::_freeArea()
{
	if (!this->_area)
		return ;
    for (t_uint y = 0; y < this->_height; y++) {
        free(this->_area[y]);
    }
    free(this->_area);
}

game_entity    *Map::_findEmptySpot()
{
    t_uint        x;
    t_uint        y;
    t_uint        rdm;

    std::srand(static_cast<t_uint>(time(NULL)));
    rdm = static_cast<t_uint>(rand()) % (this->_width * this->_height);
    x = rdm % this->_width;
    y = rdm / this->_width;

    if (this->_area[y][x] == EMPTY) {
        return *(this->_area + y) + x;
    }

    while (y < this->_height) {
        while (x < this->_width) {
            if (this->_area[y][x] == EMPTY) {
                return *(this->_area + y) + x;
            }
            x++;
        }
        x = 0;
        y++;
    }

    for (y = 0; y < this->_height; y++) {
        for (x = 0; x < this->_width; x++) {
            if (this->_area[y][x] == EMPTY) {
                return *(this->_area + y) + x;
            }
        }
    }

    return NULL;
}
