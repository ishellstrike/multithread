#pragma once
#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "request.hpp"

#include <mutex>
#include <queue>
#include <memory>

class ReadyQueue
{
   std::queue<std::unique_ptr<Request>> mQueue;
   std::mutex mMutex;

public:
   void Push(std::unique_ptr<Request> &&request);
   std::unique_ptr<Request> Pop();

   ReadyQueue();
   ReadyQueue( const ReadyQueue& ) = delete;
   ReadyQueue& operator=( const ReadyQueue& ) = delete;
};

#endif // READYQUEUE_H
