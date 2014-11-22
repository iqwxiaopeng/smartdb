#ifndef SMARTDBSTORAGE_H
#define SMARTDBSTORAGE_H

#include "api/SmartdbType.h"
#include "log/Logger.h"
#include "log/Errmsg.h"
#include "storageinterface/Records.h"
#include "storageinterface/Buffer.h"
#include "storageinterface/ColumnDef.h"

extern "C" {
  const char * smartdb_errmsg(SmartdbErr err);
}

#endif
