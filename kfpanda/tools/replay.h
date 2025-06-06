
/**
 * @file replay.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:08:13
 */
#pragma once
#include <brpc/controller.h>

#include <iostream>
#include <string>

#include "cppcommon/extends/spdlog/log.h"
#include "cppcommon/utils/error.h"
#include "google/protobuf/util/json_util.h"
#include "kfpanda/tools/client.h"
#include "kfpanda/tools/flags.h"
#include "protos/service/kfpanda/kfpanda.pb.h"

namespace kfpanda {
inline void ReplayV1() {
  brpc::Controller controller;
  ::kfpanda::ReplayRequest request;
  ::kfpanda::ReplayResponse response;

  request.set_service(FLAGS_service);
  request.mutable_option()->set_count(FLAGS_count);
  auto target = FLAGS_target.empty() ? FLAGS_target_base : FLAGS_target;
  request.mutable_target()->set_host(target);

  Client::Instance().Stub()->Replay(&controller, &request, &response, nullptr);

  std::string js;
  auto s = google::protobuf::util::MessageToJsonString(response, &js);
  if (s.ok()) {
    std::cout << js << std::endl;
  } else {
    CERROR("parse response failed. [error={}]", s.message());
  }
}

inline void ReplayV2() {
  brpc::Controller controller;
  ::kfpanda::ReplayRequestV2 request;
  ::kfpanda::ReplayResponseV2 response;

  request.set_service(FLAGS_service);
  request.mutable_option()->set_count(FLAGS_count);
  request.mutable_target_base()->set_host(FLAGS_target_base);
  request.mutable_target_compare()->set_host(FLAGS_target_compare);

  Client::Instance().Stub()->ReplayV2(&controller, &request, &response, nullptr);
  std::string js;
  auto s = google::protobuf::util::MessageToJsonString(response, &js);
  if (s.ok()) {
    std::cout << js << std::endl;
  } else {
    CERROR("parse response failed. [error={}]", s.message());
  }
}

inline void Replay() {
  cppcommon::OkOrExit(!FLAGS_service.empty(), "service should not be empty");
  if (FLAGS_target_compare.empty()) {
    auto target = FLAGS_target.empty() ? FLAGS_target_base : FLAGS_target;
    cppcommon::OkOrExit(!target.empty(), "target(or target base) should not be empty");
    ReplayV1();
  } else {
    cppcommon::OkOrExit(!FLAGS_target_base.empty(), "target base should not be empty");
    ReplayV2();
  }
}

}  // namespace kfpanda
