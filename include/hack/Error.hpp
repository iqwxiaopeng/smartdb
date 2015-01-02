/*
 * Error.hpp
 *
 *  Created on: 2015/01/03
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_HACK_ERROR_HPP_
#define INCLUDE_HACK_ERROR_HPP_

#include <cstring>
#include <cerrno>

#define STRERROR_THROW(err_class, msg) \
  { \
    throw err_class(std::string("Fatal from Smartdb: ") + msg + ": " + std::strerror(errno)); \
  }


#endif /* INCLUDE_HACK_ERROR_HPP_ */
