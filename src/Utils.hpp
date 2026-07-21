#ifndef LABELEDCHECKPOINTS_UTILS_H
#define LABELEDCHECKPOINTS_UTILS_H

#include <Geode/Geode.hpp>
using namespace geode::prelude;

namespace lcheckpoints::utils {
    inline std::string removeQuotes(const std::string& str) {
        if (str.size() >= 2 && str.starts_with('"') && str.ends_with('"')) {
            return str.substr(1, str.size() - 2);
        }
        return str;
    }

    inline bool imageFromFntExists(std::filesystem::path fntFilePath) {
        auto result = geode::utils::file::readString(fntFilePath);
        if (!result.isOk())
            return false;

        auto contents = result.unwrap();
        auto lines = geode::utils::string::split(contents, "\n");

        for (auto &&line : lines) {
            log::debug("Line: {}", line);
            if (line.starts_with("page")) {
                log::debug("that line starts with \"page\"!");
                auto tokens = geode::utils::string::split(line, " ");

                for (auto &&token : tokens) {
                    if (token.starts_with("file=")) {
                        auto parts = geode::utils::string::split(token, "=");
                        if (parts.size() < 2)
                            return false;

                        auto fileNameTokenValue = parts.at(1);
                        auto fileName = removeQuotes(fileNameTokenValue);
                        auto path = fntFilePath.parent_path() / fileName;

                        std::error_code existCode;
                        std::error_code regularFileCode;

                        if (std::filesystem::exists(path, existCode)
                            && std::filesystem::is_regular_file(path, regularFileCode))
                            return true;

                        if (existCode) {
                            log::error("Failed to determine whether file exists: {}", existCode.message());
                            return false;
                        }

                        if (regularFileCode) {
                            log::error("Failed to determine whether path exists as a regular file: {}", regularFileCode.message());
                            return false;
                        } 
                    }
                }
            }
        }

        return false;
    }
}

#endif