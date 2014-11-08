/*
 * Class.h
 *
 *  Created on: 2014/11/08
 *      Author: nakatani.sho
 */

#ifndef LIB_HACK_CLASS_H_
#define LIB_HACK_CLASS_H_

#define PREVENT_DEFAULT_CONSTRUCTOR(klass) \
  private: klass();
#define PREVENT_COPY_CONSTRUCTOR(klass) \
  private: klass(const klass&);
#define PREVENT_OBJECT_ASSIGNMENT(klass) \
  private: klass& operator=(const klass&);
#define PREVENT_CLASS_DEFAULT_METHODS(klass) \
  PREVENT_DEFAULT_CONSTRUCTOR(klass); \
  PREVENT_COPY_CONSTRUCTOR(klass); \
  PREVENT_OBJECT_ASSIGNMENT(klass); \

 #endif /* LIB_HACK_CLASS_H_ */
