/**
 * \file ThreadPool.h
 */

#ifndef ATK_CORE_THREADPOOL_H
#define ATK_CORE_THREADPOOL_H

// ================================================================================ Standard Includes
// Standard Includes
// --------------------------------------------------------------------------------
#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

namespace ATK
{
  class Pool
  {
  private:
    // -------------------------------------------------------------------- Internal Types
    using Task_Function_t     = std::function <void()>;

  private:
    // -------------------------------------------------------------------- State
    std::vector<std::thread> threads;
    std::queue<Task_Function_t> task_queue;
    std::mutex queue_mutex;
    std::condition_variable pool_notifier;
    bool should_stop_processing;
    bool is_emergency_stop;

  public:
    Pool( const std::size_t thread_count );
    ~Pool();
    
    template <typename Lambda_t >
    void Add_Task( Lambda_t && function )
    {
      // Add to task queue
      {
        std::unique_lock<std::mutex> lock( queue_mutex );

        // Sanity
        if( should_stop_processing || is_emergency_stop )
            throw std::runtime_error( "ERROR: ATK::Pool::Add_Task() - attempted to add task to stopped pool" );

        // Add our task to the queue
        task_queue.emplace( std::forward< Lambda_t >(function) );
      }

      // Notify the pool that there is work to do
      pool_notifier.notify_one();
    }

    void Emergency_Stop();


  private:
    void Worker();
  };
}

#endif
