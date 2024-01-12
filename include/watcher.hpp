#pragma once

#include <chrono>
#include <functional>
#include <filesystem>
#include <string>
#include <thread>
#include <unordered_map>

class HotWatch {
public:
    std::string path;
    std::chrono::duration<int, std::milli> delay;

    HotWatch(std::string path = "./", std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(1000))
    : path(path), delay(delay) {
        for (auto &file : std::filesystem::recursive_directory_iterator(path)) {
            _paths[file.path().string()] = std::filesystem::last_write_time(file);
        }
    }
    
    void start_loop(const std::function<void(std::string)>& action) {
        do {
            std::this_thread::sleep_for(delay);
            // check deletion
            for (auto it = _paths.begin(); it != _paths.end();) {
                if (!std::filesystem::exists(it->first)) {
                    action(it->first);
                    it = _paths.erase(it);
                } else it++;
            }
            // check for modification and creation
            for (auto& file : std::filesystem::recursive_directory_iterator(path)) {
                auto file_last_write_time = std::filesystem::last_write_time(file);
                if (_paths.find(file.path().string()) == _paths.end() || _paths[file.path().string()] != file_last_write_time) {
                    _paths[file.path().string()] = std::filesystem::last_write_time(file);
                    action(file.path().string());
                }
            }
        } while (_running);
    }
private:
    std::unordered_map<std::string, std::filesystem::file_time_type> _paths;
    bool _running = true;
};
