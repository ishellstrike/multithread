#pragma once
#ifndef STOPPER_H
#define STOPPER_H
#include <mutex>
#include <memory>

namespace {

struct Helper
{
   bool mStop = false;
   std::mutex mMutex;

   Helper();
   Helper( const Helper& ) = delete;
   Helper& operator=( const Helper& ) = delete;
};

}

class Stopper
{
   std::shared_ptr<Helper> helper;

public:
   Stopper();

   bool isStopRequired();
   void Stop();
   void Run();
};

#endif STOPPER_H
