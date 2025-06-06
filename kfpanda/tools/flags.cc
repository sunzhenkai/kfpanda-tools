#include "flags.h"

namespace kfpanda {

DEFINE_string(server, "127.0.0.1:9820", "kfpanda service address");
DEFINE_string(pb_files, "", "protobuf files");
DEFINE_string(service, "", "service");
DEFINE_int32(count, 1, "count");
DEFINE_string(target, "", "target base (host:port)");
DEFINE_string(target_base, "", "target base (host:port)");
DEFINE_string(target_compare, "", "target compare (host:port)");

}  // namespace kfpanda
