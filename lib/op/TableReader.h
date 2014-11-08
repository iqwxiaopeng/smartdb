#ifndef INCLUDE_OP_TABLE_READER_H_
#define INCLUDE_OP_TABLE_READER_H_

#include "operator.h"

namespace Smartdb {

class TableReader : public Operator {
	void read();
};

}

#endif /* INCLUDE_OP_TABLE_READER_H_ */
