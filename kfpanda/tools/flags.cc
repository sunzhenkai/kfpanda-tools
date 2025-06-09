#include "flags.h"

namespace kfpanda {

DEFINE_string(server, "127.0.0.1:9820", "kfpanda service address");
DEFINE_string(service, "", "service");
DEFINE_int32(count, 1, "count");
DEFINE_string(target, "", "target base (host:port)");
DEFINE_string(target_base, "", "target base (host:port)");
DEFINE_string(target_compare, "", "target compare (host:port)");
DEFINE_string(pb_files, "", "protobuf files");
DEFINE_string(pb_import_pathes, "", "protobuf import pathes");
DEFINE_string(response_class, "", "response pb message");
DEFINE_string(response_body_type, "text", "response body type. one of (text, json, protobuf)");
DEFINE_bool(enable_differ, true, "print differ info");

}  // namespace kfpanda
