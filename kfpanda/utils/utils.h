/**
 * @file utils.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-09 13:06:55
 */
#pragma once
#include <absl/status/status.h>
#include <absl/strings/numbers.h>

#include <iostream>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "cppcommon/utils/str.h"
#include "google/protobuf/message.h"
#include "google/protobuf/util/json_util.h"
#include "protos/service/kfpanda/kfpanda.pb.h"

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

inline absl::Status ParseTarget(::kfpanda::URI* dest, const std::string& addr) {
  std::vector<std::string> segs;
  cppcommon::StringSplit(segs, addr, ':');
  if (segs.size() != 2) {
    return absl::InvalidArgumentError("unexpected target address");
  } else {
    dest->set_host(segs[0]);
    int port;
    if (!absl::SimpleAtoi(segs[1], &port)) {
      return absl::InvalidArgumentError("unexpected target port");
    }
    dest->set_port(port);
    return absl::OkStatus();
  }
}
}  // namespace kfpanda
