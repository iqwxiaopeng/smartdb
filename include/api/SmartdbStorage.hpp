#ifndef SMARTDBSTORAGE_H
#define SMARTDBSTORAGE_H

#include "api/SmartdbType.hpp"
#include "log/Logger.hpp"
#include "log/Errmsg.hpp"
#include "storageinterface/Records.hpp"
#include "storageinterface/Buffer.hpp"
#include "storageinterface/ColumnDef.hpp"

extern "C" {
  const char * smartdb_errmsg(SmartdbErr err);
}

#endif
