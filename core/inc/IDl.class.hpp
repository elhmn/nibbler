/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDl.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmbarga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:32:57 by bmbarga           #+#    #+#             */
//   Updated: 2017/10/03 22:09:05 by mc               ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef IDL_CLASS_HPP
# define IDL_CLASS_HPP

# include <iostream>
# include "nibbler.hpp"

# define UNIT 20

class		IDl
{
	public:

//operator overload
	IDl	&operator=(IDl const &rhs);

//destructors
	virtual ~IDl(void) {};

//actions
 	virtual void	print(Map const map) = 0;
	virtual key		keyEvent(void) = 0;
};

//those functions must be implemented for each library
extern "C" IDl			*dl_init(void);
extern "C" void			dl_close(IDl *dl);

#endif
