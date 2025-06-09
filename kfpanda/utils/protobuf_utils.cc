#include "protobuf_utils.h"

#include <fstream>
#include <string>
#include <vector>

namespace kfpanda {

ProtoLoader::ProtoLoader() : importer_(&source_tree_, &error_collector_), message_factory_(importer_.pool()) {}

void ProtoLoader::AddImportPathes(const std::vector<std::string>& import_paths) {
  for (const auto& path : import_paths) {
    source_tree_.MapPath("", path);
  }
}

bool ProtoLoader::LoadProtoFiles(const std::vector<std::string>& proto_files) {
  for (const auto& file : proto_files) {
    if (importer_.Import(file) == nullptr) {
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

}  // namespace kfpanda
