/**
 * @file utils.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-09 13:06:55
 */
#pragma once
#include <string>

#include "absl/status/statusor.h"
#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"

namespace kfpanda {
inline absl::StatusOr<std::string> MessageToString(const google::protobuf::Message& message) {
  std::string js;
  auto s = google::protobuf::util::MessageToJsonString(message, &js);
  if (s.ok()) {
    return js;
  } else {
    return s;
  }
}
}  // namespace kfpanda
