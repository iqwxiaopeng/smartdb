/*
 * AllocError.hpp
 *
 *  Created on: 2015/01/03
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_ERR_ALLOCERROR_HPP_
#define INCLUDE_ERR_ALLOCERROR_HPP_

#include <stdexcept>
#include <string>

namespace Smartdb {

class AllocError : public std::runtime_error {
public:
  AllocError(const std::string & what)
  : std::runtime_error(what)
  {}

  virtual ~AllocError() {}
};

} /* namespace Smartdb */

#endif /* INCLUDE_ERR_ALLOCERROR_HPP_ */
