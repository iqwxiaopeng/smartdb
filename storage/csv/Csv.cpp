/*
 * Csv.cpp
 *
 *  Created on: 2014/11/04
 *      Author: nakatani.sho
 */

#include <stdio.h>
#include "Csv.h"
#include "datastruct/Records.h"
#include "mem/Buffer.h"
#include "hack/Assert.h"

namespace Smartdb {

Csv::Csv()
: read_buf(10 * 1e6)
{
}

Csv::~Csv() {
	// TODO Auto-generated destructor stub
}

SmartdbErr Csv::read_records(Records &records, size_t n_records) {
  FILE *fp = fopen()
  fread();
  //freadでread_buf埋める

  /*
  lines in read_buf.readline()
      cols in lines.split(',')
        size_t col_idx;
        for (size_t i = 0; i < records.coldefs.size(); ++i)
          col_idx = cols.search(records.coldefs[i].name);
        records.columns[col_idx]->add(cols[col_idx]);
        */
  return NO_ERR;
}

} /* namespace Smartdb */
