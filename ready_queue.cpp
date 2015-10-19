#include "ready_queue.hpp"

void ReadyQueue::Push( std::unique_ptr<Request> &&request )
{
   std::lock_guard<std::mutex> lock( mMutex );
   mQueue.push( std::move( request ) );
}

std::unique_ptr<Request> ReadyQueue::Pop()
{
   std::unique_ptr<Request> request = nullptr;
   std::lock_guard<std::mutex> lock( mMutex );
   if( !mQueue.empty() )
   {
      request = std::move( mQueue.front() );
      mQueue.pop();
   }
   return request;
}

ReadyQueue::ReadyQueue()
{

}

