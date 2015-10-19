#include "stopper.hpp"


Stopper::Stopper()
{
   helper = std::make_shared<Helper>();
}

bool Stopper::isStopRequired()
{
   std::lock_guard<std::mutex> m( helper->mMutex );
   return helper->mStop;
}

void Stopper::Stop()
{
   std::lock_guard<std::mutex> m( helper->mMutex );
   helper->mStop = true;
}

void Stopper::Run()
{
   std::lock_guard<std::mutex> m( helper->mMutex );
   helper->mStop = false;
}

namespace {

Helper::Helper()
{

}

}
