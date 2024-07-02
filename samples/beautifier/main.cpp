#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "json.h"
#include "json_beautifier.h"

namespace {

std::string ReadFile(const std::string& filename) {
    std::ifstream file_stream(filename);
    std::stringstream buffer;
    buffer << file_stream.rdbuf();
    return buffer.str();
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Json Beautifier expects a single json file,"  << std::endl
                  << "See the command below:" << std::endl
                  << "\tjson-beautifier [file.json]" << std::endl;
        return 0;
    }

    const auto& file_context = ReadFile(std::string(argv[1]));

    json::JsonBeautifier beautifier;
    const auto& json = json::Json::fromJson(file_context);

    if (!json) {
        std::cout << "Json is not valid!"  << std::endl;
        return 0;
    }

    const auto& beautified_json = beautifier.beautify(*json);

    std::cout << beautified_json << std::endl;

    return 0;
}
