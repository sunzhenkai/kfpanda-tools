/**
 * @file client.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:13:16
 */
#pragma once
#include <brpc/channel.h>

#include <memory>

#include "cppcommon/partterns/singleton.h"
#include "cppcommon/utils/error.h"
#include "kfpanda/client/client.h"
#include "kfpanda/tools/flags.h"

namespace kfpanda {
class Client : public KfpandaClient, public cppcommon::Singleton<kfpanda::Client> {
 public:
  Client() : KfpandaClient("kfpanda-tools", FLAGS_server) {
    auto s = Init();
    cppcommon::OkOrExit(s.ok(), "connecting to server failed");
  }
};

inline std::shared_ptr<brpc::Channel> GenChannel() {
  std::shared_ptr<brpc::Channel> ret = std::make_shared<brpc::Channel>();
  brpc::ChannelOptions options;
  options.protocol = brpc::PROTOCOL_HTTP;
  auto s = ret->Init(FLAGS_server.c_str(), &options);
  cppcommon::OkOrExit(s == 0, "Fail to initialize channel");
  return ret;
}
}  // namespace kfpanda
