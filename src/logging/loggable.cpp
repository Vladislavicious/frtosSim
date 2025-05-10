#include "loggable.h"

//---------------------------------------------------------------
//       Loggable interface implementation:
//---------------------------------------------------------------
Loggable::Loggable() :
  logger{ nullptr }
{
}
//---------------------------------------------------------------
void Loggable::SetLogger( LoggerInterface* Logger )
{
  logger = Logger;
}
//---------------------------------------------------------------