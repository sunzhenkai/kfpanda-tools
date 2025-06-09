#include <absl/status/status.h>
#include <brpc/controller.h>
#include <glog/logging.h>

#include <functional>
#include <string>
#include <unordered_map>

#include "cppcommon/utils/error.h"
#include "kfpanda/tools/record.h"
#include "kfpanda/tools/replay.h"
#include "kfpanda/tools/sample.h"
#include "kfpanda/tools/stat.h"
#include "kfpanda/utils/protobuf_utils.h"

std::unordered_map<std::string, std::function<void()>> kFunMaps{
    {"replay", kfpanda::Replay},
    {"stat", kfpanda::Stat},
    {"record", kfpanda::Record},
    {"sample", kfpanda::Sample},
};

absl::Status Init() {
  // kfpanda::InitProtoLoader();
  return absl::OkStatus();
}

int main(int argc, char **argv) {
  cppcommon::OkOrExit(argc >= 2, "unpexpected argument count");
  google::SetCommandLineOption("log_dir", "log");
  google::SetCommandLineOption("graceful_quit_on_sigterm", "true");
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(*argv);
  cppcommon::Assert(google::IsGoogleLoggingInitialized(), "[main] init google logging failed.");

  auto s = Init();
  cppcommon::OkOrExit(s.ok(), s.message());

  auto fun = std::string(argv[1]);
  auto it = kFunMaps.find(fun);
  if (it != kFunMaps.end()) {
    it->second();
  } else {
    cppcommon::OkOrExit(false, "unexpected function: " + fun);
  }

  google::ShutdownGoogleLogging();
  return 0;
}
