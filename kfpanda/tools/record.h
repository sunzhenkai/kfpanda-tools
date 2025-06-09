/**
 * @file record.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-09 14:52:20
 */
#pragma once
#include <absl/status/status.h>
#include <brpc/controller.h>
#include <cppcommon/utils/str.h>
#include <google/protobuf/message.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "cppcommon/extends/spdlog/log.h"
#include "google/protobuf/util/json_util.h"
#include "kfpanda/tools/client.h"
#include "protos/service/kfpanda/kfpanda.pb.h"

namespace kfpanda {
inline void Record() {
  brpc::Controller controller;
  ::kfpanda::EchoMessage msg;
  ::kfpanda::EchoMessage response;

  msg.set_message("hello kfpanda");
  DebugClient::Instance().Stub()->Echo(&controller, &msg, &response, nullptr);

  std::string js;
  auto s = google::protobuf::util::MessageToJsonString(response, &js);
  if (s.ok()) {
    std::cout << js << std::endl;
  } else {
    CERROR("parse response failed. [error={}]", s.message());
  }
}
}  // namespace kfpanda
