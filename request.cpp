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
   for( int i = 0; i < 10; ++i )
   {
      if( stopSignal.isStopRequired() ) // досрочное прерывание обработки, в реальном примере может быть реализовано наподобие точек прерывания
         return;

      std::this_thread::sleep_for( std::chrono::milliseconds( rand() % 100 ) );
   }
}


Request::Request()
{
   static int unique = 0;
   data = unique;
   unique++;
}
