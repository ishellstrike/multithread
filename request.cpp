#include "request.hpp"
#include <thread>
#include <stdlib.h>

Request *GetRequest( Stopper stopSignal ) throw()
{
   std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 1000 ) );
   return stopSignal.isStopRequired() ? nullptr : new Request();
}


void ProcessRequest( Request *, Stopper stopSignal ) throw()
{
   if( stopSignal.isStopRequired() )
      return;
   std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 1000 ) );
}


Request::Request()
{
   static int unique = 0;
   data = unique;
   unique++;
}
