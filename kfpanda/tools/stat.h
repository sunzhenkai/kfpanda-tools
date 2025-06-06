/**
 * @file stat.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:14:01
 */
#pragma once

#include "kfpanda/tools/client.h"
#include <brpc/controller.h>
#include <cppcommon/extends/spdlog/log.h>
#include <iostream>

namespace kfpanda {
inline void Stat() {
  auto channel = GenChannel();
  brpc::Controller cntl;
  cntl.http_request().uri() = "/api/debug/stat";
  cntl.http_request().set_method(brpc::HTTP_METHOD_GET);
  channel->CallMethod(NULL, &cntl, NULL, NULL, NULL);
  if (!cntl.Failed()) {
    std::cout << cntl.response_attachment().to_string() << std::endl;
  } else {
    CERROR("request stat failed. [erro={}]", cntl.ErrorText());
  }
}
} // namespace kfpanda
