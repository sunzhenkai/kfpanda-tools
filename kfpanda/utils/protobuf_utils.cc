#include "protobuf_utils.h"

#include <brpc/controller.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "butil/base64.h"
#include "kfpanda/tools/flags.h"

namespace kfpanda {

ProtoLoader::ProtoLoader() : importer_(&source_tree_, &error_collector_), message_factory_(importer_.pool()) {}

void ProtoLoader::AddImportPathes(const std::vector<std::string>& import_paths) {
  for (const auto& path : import_paths) {
    if (!path.empty()) {
      source_tree_.MapPath("", path);
    }
  }
}

bool ProtoLoader::LoadProtoFiles(const std::vector<std::string>& proto_files) {
  for (const auto& file : proto_files) {
    if (!file.empty() && importer_.Import(file) == nullptr) {
      return false;
    }
  }
  return true;
}

bool ProtoLoader::LoadProtoFromString(const std::string& proto_content, const std::string& filename) {
  std::string temp_file = "/tmp/" + filename;
  std::ofstream out(temp_file);
  if (!out.is_open()) return false;

  out << proto_content;
  out.close();

  bool result = (importer_.Import(temp_file) != nullptr);
  remove(temp_file.c_str());
  return result;
}

google::protobuf::Message* ProtoLoader::CreateMessage(const std::string& type_name) {
  const auto* descriptor = importer_.pool()->FindMessageTypeByName(type_name);
  if (!descriptor) return nullptr;
  return message_factory_.GetPrototype(descriptor)->New();
}

std::shared_ptr<google::protobuf::Message> ParsePbMessage(const std::string& data, bool base64_decode) {
  std::string data_raw;
  if (base64_decode) {
    butil::Base64Decode(data, &data_raw);
  } else {
    data_raw = data;
  }
  auto message = ProtoLoader::Instance().CreateMessage(FLAGS_response_class);
  if (message != nullptr) {
    if (!message->ParseFromString(data_raw)) {
      std::cerr << "parse message from failed, response class: " << FLAGS_response_class << std::endl;
    }
  } else {
    std::cerr << "create message from failed, response class: " << FLAGS_response_class << std::endl;
  }
  return std::shared_ptr<google::protobuf::Message>(message);
}

}  // namespace kfpanda
