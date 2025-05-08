#include "initializable.h"

//---------------------------------------------------------------
//       Initialazable interface implementation:
//---------------------------------------------------------------
bool Initialazable::Init()
{
  if( initialized )
    return true;

  initialized = _Init();
  return initialized;
}
//---------------------------------------------------------------
bool Initialazable::DeInit()
{
  if( !initialized )
    return true;

  initialized = _DeInit();
  return initialized;
}
//---------------------------------------------------------------
bool Initialazable::IsInit()
{
  return initialized;
}
//---------------------------------------------------------------