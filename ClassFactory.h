#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include "DataObject.h"

template <typename T>
class ClassFactory 
{
  public:
    T *getData()
    {
      return &data;
    }
  protected:
    T data;
};
#endif

