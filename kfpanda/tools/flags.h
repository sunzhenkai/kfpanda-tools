/**
 * @file flags.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-06 17:09:53
 */
#pragma once
#include "gflags/gflags.h"

namespace kfpanda {

DECLARE_string(server);
DECLARE_string(service);
DECLARE_int32(count);
DECLARE_string(target);
DECLARE_string(target_base);
DECLARE_string(target_compare);
DECLARE_string(pb_files);
DECLARE_string(response_class);
DECLARE_string(response_body_type);
DECLARE_bool(enable_differ);
}  // namespace kfpanda
