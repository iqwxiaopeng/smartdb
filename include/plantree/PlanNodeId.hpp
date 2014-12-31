/*
 * OperatorType.h
 *
 *  Created on: 2014/12/22
 *      Author: nakatani.sho
 */

#ifndef INCLUDE_PLANTREE_PLANNODEID_H_
#define INCLUDE_PLANTREE_PLANNODEID_H_

namespace Smartdb {

enum OperatorInputType {
  // Operator with single input
  /**
   * should get all the input records when starting calculation.
   * @example simple sort, simple aggregation, etc...
   */
  BLOCK = 1,
  /**
   * can process each record before getting all inputs.
   * @example filter, projection, etc...
   */
  STREAM,

  // Operator with double inputs
  /**
   * should get all the input records from both children operators when starting calculation.
   * @example UNION
   */
  BLOCK_BLOCK,
  /**
   * should get all the input records from one child operator.
   * After that, each record from another child operator can be processed without waiting for all.
   * @example INNER JOIN
   */
  BLOCK_STREAM,
  /**
   * can process each record from both children operators any time.
   * @example UNION ALL
   */
  STREAM_STREAM,
};

#define OPERATOR_INPUT_TYPE_OF(plan_node_id) \
  _BEGIN_BLOCK_OPERATOR < plan_node_id < _END_BLOCK_OPERATOR ? BLOCK : \
  _BEGIN_STREAM_OPERATOR < plan_node_id < _END_STREAM_OPERATOR ? STREAM : \
  _BEGIN_BLOCK_BLOCK_OPERATOR < plan_node_id < _END_BLOCK_BLOCK_OPERATOR ? BLOCK_BLOCK : \
  _BEGIN_BLOCK_STREAM_OPERATOR < plan_node_id < _END_BLOCK_STREAM_OPERATOR ? BLOCK_STREAM : \
  _BEGIN_STREAM_STREAM_OPERATOR < plan_node_id < _END_STREAM_STREAM_OPERATOR ? STREAM_STREAM : \
  NULL_OPERATOR


enum PlanNodeId {
  NULL_OPERATOR = 0,

  // Block operator
  _BEGIN_BLOCK_OPERATOR,
  TABLE_READER,
  _END_BLOCK_OPERATOR,

  // Stream operator
  _BEGIN_STREAM_OPERATOR,
  _END_STREAM_OPERATOR,

  // Block-block operator
  _BEGIN_BLOCK_BLOCK_OPERATOR,
  _END_BLOCK_BLOCK_OPERATOR,

  // Block-stream operator
  _BEGIN_BLOCK_STREAM_OPERATOR,
  _END_BLOCK_STREAM_OPERATOR,

  // Stream-stream operator
  _BEGIN_STREAM_STREAM_OPERATOR,
  _END_STREAM_STREAM_OPERATOR,
};

}


#endif /* INCLUDE_PLANTREE_PLANNODEID_H_ */
