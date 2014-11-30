/*
 * ParseError.h
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_ERR_PARSEERROR_H_
#define INCLUDE_ERR_PARSEERROR_H_

#include <stdexcept>
#include <string>

namespace Smartdb {

class ParseError : public std::runtime_error {
public:
  ParseError(const std::string & what)
  : std::runtime_error(what)
  {}

  virtual ~ParseError() {}
};

} /* namespace Smartdb */

#endif /* INCLUDE_ERR_PARSEERROR_H_ */
