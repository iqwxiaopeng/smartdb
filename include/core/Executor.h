/*
 * Executor.h
 *
 *  Created on: 2014/12/19
 *      Author: nakatani.sho
 */

#ifndef LIB_CORE_EXECUTOR_H_
#define LIB_CORE_EXECUTOR_H_

#include "api/SmartdbType.h"
#include "hack/Class.h"

namespace Smartdb {

class Executor {
public:
  Executor(size_t n_workers);
  virtual ~Executor();

  /**
   * Asynchronously run operator.
   * @param op Operator to be run.
   * @param i_worker `op` runs at ith worker.
   * @param scheduler Used to call `scheduler.async_run_callback()` after `op` finishes to run.
   * @note Only main thread is allowed to call this function.
   */
  //void async_run(Operator * const op, size_t i_worker, Scheduler & scheduler);

  PREVENT_CLASS_DEFAULT_METHODS(Executor);
};

} /* namespace Smartdb */

#endif /* LIB_CORE_EXECUTOR_H_ */
