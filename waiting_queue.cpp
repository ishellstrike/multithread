#include "waiting_queue.hpp"

void WaitingQueue::Push( std::unique_ptr<Request> &&request )
{
   std::lock_guard<std::mutex> lock( mMutex );
   mQueue.push( std::move( request ) );
   mCond.notify_one();
}

std::unique_ptr<Request> WaitingQueue::Pop( Stopper &stopper )
{
   std::unique_lock<std::mutex> lock( mMutex );
   while ( mQueue.empty() && !stopper.isStopRequired() ) // условная переменная может создавать ложные пробуждения
      mCond.wait(lock);

   std::unique_ptr<Request> request = nullptr;
   if( !mQueue.empty() )
   {
      request = std::move( mQueue.front() );
      mQueue.pop();
   }

   return request;
}

void WaitingQueue::PossibleStop()
{
   std::lock_guard<std::mutex> lock( mMutex );
   mCond.notify_all();
}

WaitingQueue::WaitingQueue()
{

}
