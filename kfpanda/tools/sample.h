/**
 * @file stat.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:14:01
 */
#pragma once

#include <brpc/controller.h>
#include <cppcommon/extends/spdlog/log.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "kfpanda/tools/client.h"
#include "kfpanda/tools/flags.h"

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

inline void SampleV2() {}
}  // namespace kfpanda
