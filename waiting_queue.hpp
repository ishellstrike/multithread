#pragma once
#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H
#include "request.hpp"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

class WaitingQueue
{
   std::queue<std::unique_ptr<Request>> mQueue;
   std::mutex mMutex;
   std::condition_variable mCond;

public:
   void Push( std::unique_ptr<Request> &&request );
   std::unique_ptr<Request> Pop( Stopper &stopper );
   void PossibleStop();

   WaitingQueue();
   WaitingQueue( const WaitingQueue& ) = delete;
   WaitingQueue& operator=( const WaitingQueue& ) = delete;
};

#endif //WAITING_QUEUE_H
