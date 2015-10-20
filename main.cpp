#include "waiting_queue.hpp"
#include "ready_queue.hpp"
#include "stopper.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <functional>

void Consumer( WaitingQueue &waiting, ReadyQueue &ready, Stopper &stopper )
{
   static int counter = 0;
   int unique = counter;
   counter++;

   while( !stopper.isStopRequired() )
   {
      std::cout << " C. Trying to pop request by " << unique << std::endl;
      std::unique_ptr<Request> request = waiting.Pop( stopper );
      if( !request )
      {
         std::cout << " C. Pop request empty. Stop" << std::endl;
         continue;
      }

      std::cout << " C. Request #" << request->data << " processing by " << unique << std::endl;
      ProcessRequest( request.get(), stopper );
      std::cout << " C. Request #" << request->data << " done by " << unique << std::endl;
      ready.Push( std::move( request ) );
   }
   std::cout << " C. Consumer thread " << unique << " exit" << std::endl;
}

void Producer( WaitingQueue &waiting, Stopper &stopper )
{
   static int counter = 0;
   int unique = counter;
   counter++;

   while( !stopper.isStopRequired() )
   {
      std::cout << " PR. Trying to get request by " << unique << std::endl;
      Request *request = GetRequest( stopper );
      if(!request)
      {
         std::cout << " PR. Get request empty. Stop " << unique << std::endl;
         continue;
      }

      std::cout << " PR. New request #" << request->data << " by " << unique << std::endl;
      waiting.Push( std::unique_ptr<Request>( request ) );
   }
   std::cout << " PR. Producer thread " << unique << " exit" << std::endl;
}



int main()
{
   std::vector<std::thread> producers;
   std::vector<std::thread> consumers;

   WaitingQueue wq;
   ReadyQueue rq;
   Stopper stp;

   for( int i = 0; i < 4; ++i )
      producers.emplace_back( Producer, std::ref( wq ), std::ref( stp ) );

   for( int i = 0; i < 2; ++i )
      producers.emplace_back( Consumer, std::ref( wq ), std::ref( rq ), std::ref( stp ) );


   std::thread th( [&]()
   {
      std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
      std::cout << "Timer expire" << std::endl;
      stp.Stop();
      wq.PossibleStop();
   } );
   th.join();

   std::for_each( producers.begin(), producers.end(), [](std::thread &th){ th.join(); } );
   std::for_each( consumers.begin(), consumers.end(), [](std::thread &th){ th.join(); } );
   return 0;
}

