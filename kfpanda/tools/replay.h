
/**
 * @file replay.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:08:13
 */
#pragma once
#include <absl/status/status.h>
#include <brpc/controller.h>
#include <cppcommon/utils/str.h>
#include <google/protobuf/message.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cppcommon/extends/rapidjson/differ.h"
#include "cppcommon/extends/spdlog/log.h"
#include "cppcommon/utils/error.h"
#include "google/protobuf/util/json_util.h"
#include "kfpanda/tools/client.h"
#include "kfpanda/tools/flags.h"
#include "kfpanda/utils/protobuf_utils.h"
#include "kfpanda/utils/utils.h"
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

inline void InitProtoLoader() {
  std::vector<std::string> import_pathes;
  std::vector<std::string> proto_files;
  cppcommon::StringSplit(import_pathes, FLAGS_pb_import_pathes, ',');
  cppcommon::StringSplit(proto_files, FLAGS_pb_files, ',');
  ProtoLoader::Instance().AddImportPathes(import_pathes);
  ProtoLoader::Instance().LoadProtoFiles(proto_files);
}

inline std::shared_ptr<google::protobuf::Message> ParsePbMessage(const std::string &data) {
  auto message = ProtoLoader::Instance().CreateMessage(FLAGS_response_class);
  if (message != nullptr) {
    message->ParseFromString(data);
  }
  return std::shared_ptr<google::protobuf::Message>(message);
}

inline void PrintReplayResponseDiffer(const ::kfpanda::ReplayResponseV2 &response) {
  cppcommon::rapidjson::BatchDiffResultStat stat;
  for (auto &item : response.responses()) {
    cppcommon::rapidjson::DiffResult dr;
    // auto s = cppcommon::rapidjson::DiffJson(stat, {}, item.base().body(), item.compare().body());
    absl::Status s;
    if (FLAGS_response_body_type == "text") {
      auto sa = MessageToString(item.base());
      auto sb = MessageToString(item.compare());
      s = cppcommon::rapidjson::DiffJson(stat, {}, sa.value(), sb.value());
    } else if (FLAGS_response_body_type == "json") {
      s = cppcommon::rapidjson::DiffJson(stat, {}, item.base().body(), item.compare().body());
    } else if (FLAGS_response_body_type == "protobuf") {
      InitProtoLoader();
      auto msg_base = ParsePbMessage(item.base().body());
      auto msg_cmp = ParsePbMessage(item.compare().body());
      if (msg_base == nullptr || msg_cmp == nullptr) {
        s = absl::InternalError("create protobuf message failed: " + FLAGS_response_class);
      } else {
        auto msg_base_str = MessageToString(*msg_base).value();
        auto msg_cmp_str = MessageToString(*msg_cmp).value();
        s = cppcommon::rapidjson::DiffJson(stat, {}, msg_base_str, msg_cmp_str);
      }
    } else {
      s = absl::InternalError("unknown response bod type " + FLAGS_response_body_type);
    }
    if (!s.ok()) {
      spdlog::error("compare failed: {}", s.ToString());
    }
  }
  std::cout << stat.ToString();
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

  if (FLAGS_enable_differ) {
    PrintReplayResponseDiffer(response);
  } else {
    std::string js;
    auto s = google::protobuf::util::MessageToJsonString(response, &js);
    if (s.ok()) {
      std::cout << js << std::endl;
    } else {
      CERROR("parse response failed. [error={}]", s.message());
    }
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
