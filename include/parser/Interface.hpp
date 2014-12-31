/*
 * Interface.h
 *
 *  Created on: 2014/11/30
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_PARSER_INTERFACE_H_
#define INCLUDE_PARSER_INTERFACE_H_


namespace Smartdb {

int smartdb_parse();
void * smartdb_reg_parsed_str(const char * str);
void smartdb_delete_parse_buf(void * buf);

}

#endif /* INCLUDE_PARSER_INTERFACE_H_ */
