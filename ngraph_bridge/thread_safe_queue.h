/*******************************************************************************
 * Copyright 2019 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#ifndef THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE_H_
#pragma once

#include <queue>

#include "absl/synchronization/mutex.h"

using namespace std;
namespace tensorflow {
namespace ngraph_bridge {

template <typename T>
class ThreadSafeQueue {
 public:
  T* GetNextAvailable() {
    T* next = nullptr;
    m_mutex.Lock();
    while (m_queue.empty()) {
      m_cv.Wait(&m_mutex);
    }

    next = m_queue.front();
    m_queue.pop();
    m_mutex.Unlock();
    return next;
  }

  void Add(T* session) {
    m_mutex.Lock();
    m_queue.push(session);
    m_cv.SignalAll();
    m_mutex.Unlock();
  }

 private:
  queue<T*> m_queue;
  absl::CondVar m_cv;
  absl::Mutex m_mutex;
};

}  // namespace ngraph_bridge
}  // namespace tensorflow

#endif  // THREAD_SAFE_QUEUE_H_