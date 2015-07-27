/**
 * \file ThreadPool.cpp
 */

#include "ThreadPool.h"

namespace ATK
{
  Pool::Pool( const std::size_t thread_count )
  : should_stop_processing( false ),
    is_emergency_stop     ( false )
  {
    // Sanity
    if( thread_count == 0 )
      throw std::runtime_error("ERROR: Thread::Pool() -- must have at least one thread");

    // Init pool
    threads.reserve( thread_count );

    for( std::size_t i = 0; i < thread_count; ++i )
      threads.emplace_back( [this](){ Worker(); } );
  }

  Pool::~Pool()
  {
    // Set stop flag
    {
      std::unique_lock<std::mutex> queue_lock( queue_mutex );

      should_stop_processing = true;
    }

    // Wake up all threads and wait for them to exit
    pool_notifier.notify_all();

    for( auto & task_thread: threads )
      task_thread.join();
  }

  // -------------------------------------------------------------------- Emergency_Stop()
  void Pool::Emergency_Stop()
  {
    {
      std::unique_lock<std::mutex> queue_lock( queue_mutex );

      is_emergency_stop = true;
    }
      
    pool_notifier.notify_all();
      
    for( auto & task_thread: threads )
      task_thread.join();
  }

  void Pool::Worker()
  {
    while( true )
    {
      // Retrieve a task
      Task_Function_t task;
      {
        // Wait on queue or 'stop processing' flags
        std::unique_lock<std::mutex> queue_lock( queue_mutex );

        pool_notifier.wait
        (
          queue_lock,

          [this]()
          { return !task_queue.empty()
               ||  should_stop_processing
               ||  is_emergency_stop; }
        );

          // Bail when stopped and no more tasks remain,
          // or if an emergency stop has been requested.
        if(    (task_queue.empty() && should_stop_processing)
            ||  is_emergency_stop )
          return;

        // Retrieve next task
        task = std::move( task_queue.front() );
        task_queue.pop();
      }

      // Execute task
      task();
    }
  }
}

