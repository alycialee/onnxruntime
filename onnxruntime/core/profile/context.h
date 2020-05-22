// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <thread>
#include <mutex>
#include <string>
#include <unordered_map>

namespace onnxruntime {
namespace profile {

// Singleton class of managing global NVTX profiling information. 
class Context {
 public:
  static Context& GetInstance() {
    static Context instance_;
    return instance_;
  }

  std::string GetThreadTag(const std::thread::id& thread_id) {
    const std::lock_guard<std::mutex> lock(mtx_);
    return thread_tag_.at(thread_id);
  }

  void SetThreadTag(
      const std::thread::id& thread_id, const std::string& tag) {
    const std::lock_guard<std::mutex> lock(mtx_);
    thread_tag_[thread_id] = tag;
  }

 private:
  Context() = default;
  ~Context() = default;
  Context(const Context&) = delete;
  Context& operator=(const Context&) = delete;

  // map from thread's id to its human-readable tag.
  std::unordered_map<std::thread::id, std::string> thread_tag_;
  std::mutex mtx_;
};

}  // namespace profile
}  // namespace onnxruntime