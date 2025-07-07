/**
 * @file stat.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:14:01
 */
#pragma once

#include <brpc/controller.h>
#include <cppcommon/extends/spdlog/log.h>
#include <protos/service/kfpanda/kfpanda.pb.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "kfpanda/tools/client.h"
#include "kfpanda/tools/flags.h"
#include "kfpanda/utils/protobuf_utils.h"
#include "kfpanda/utils/utils.h"

namespace kfpanda {
inline void Sample() {
  auto channel = GenServerChannel();
  brpc::Controller cntl;
  cntl.http_request().uri() = "/api/debug/sample";
  cntl.http_request().SetHeader("Content-Type", "application/json");
  cntl.http_request().set_method(brpc::HTTP_METHOD_POST);

  std::string bd = fmt::format(R"({{"service":"{}","count":{}}})", FLAGS_service, FLAGS_count);
  cntl.request_attachment().append(bd);
  channel->CallMethod(NULL, &cntl, NULL, NULL, NULL);
  if (!cntl.Failed()) {
    std::cout << cntl.response_attachment().to_string() << std::endl;
  } else {
    CERROR("request stat failed. [erro={}]", cntl.ErrorText());
  }
}

inline void SampleV2() {
  brpc::Controller controller;
  controller.set_timeout_ms(1000 * 60 * 15);  // 15min

  ::kfpanda::SampleRequest request;
  ::kfpanda::SampleResponse response;

  request.set_service(FLAGS_service);
  request.set_count(FLAGS_count);

  Client::Instance().Stub()->Sample(&controller, &request, &response, nullptr);

  for (auto &rsp : response.data()) {
    kfpanda::RecordRequest req;
    req.ParseFromString(rsp);

    if (FLAGS_response_body_type == "protobuf") {
      std::string js;
      auto s = google::protobuf::util::MessageToJsonString(req, &js);
      std::cout << js << std::endl;
      auto m = ParsePbMessage(req.data());
      if (m != nullptr) {
        auto sor = MessageToString(*m);
        std::cout << sor.value() << std::endl;
      } else {
        std::cerr << "parse message body failed" << std::endl;
      }
    } else if (FLAGS_response_body_type == "json") {
      std::cout << std::string(req.data()) << std::endl;
    } else {
      std::cout << std::string(req.data()) << std::endl;
    }
  }
}
}  // namespace kfpanda
