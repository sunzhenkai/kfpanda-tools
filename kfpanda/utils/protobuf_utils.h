
/**
 * @file protobuf_utils.h
 * @brief
 * @author zhenkai.sun
 * @date 2025-06-09 13:46:02
 */
#pragma once

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/util/json_util.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cppcommon/partterns/singleton.h"
#include "cppcommon/utils/str.h"
#include "kfpanda/tools/flags.h"

namespace kfpanda {
std::shared_ptr<google::protobuf::Message> ParsePbMessage(const std::string& data, bool base64_decode = true);

class DummyErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector {
 public:
  inline void RecordError(absl::string_view filename, int line, int column, absl::string_view message) {
    std::cerr << "Error in " << filename << " @ " << line << ":" << column << " - " << message << std::endl;
  }
  inline void RecordWarning(absl::string_view filename, int line, int column, absl::string_view message) {
    std::cerr << "Warning in " << filename << " @ " << line << ":" << column << " - " << message << std::endl;
  }
};

class ProtoLoader : public cppcommon::Singleton<ProtoLoader> {
 public:
  explicit ProtoLoader();
  void AddImportPathes(const std::vector<std::string>& import_paths);
  bool LoadProtoFiles(const std::vector<std::string>& proto_files);
  bool LoadProtoFromString(const std::string& proto_content, const std::string& filename = "dynamic.proto");
  google::protobuf::Message* CreateMessage(const std::string& type_name);

 private:
  google::protobuf::compiler::DiskSourceTree source_tree_;
  google::protobuf::compiler::Importer importer_;
  google::protobuf::DynamicMessageFactory message_factory_;
  DummyErrorCollector error_collector_{};
};

inline void InitProtoLoader() {
  if (!FLAGS_pb_import_pathes.empty()) {
    std::vector<std::string> import_pathes;
    cppcommon::StringSplit(import_pathes, FLAGS_pb_import_pathes, ',');
    ProtoLoader::Instance().AddImportPathes(import_pathes);
  }
  if (!FLAGS_pb_files.empty()) {
    std::vector<std::string> proto_files;
    cppcommon::StringSplit(proto_files, FLAGS_pb_files, ',');
    ProtoLoader::Instance().LoadProtoFiles(proto_files);
  }
}
}  // namespace kfpanda
