#include <cstdlib>
#include <iostream>
#include <thread>
#include <memory>
#include <string.h>

#include "include/watcher.hpp"
#include "vendor/CLI11.hpp"

void run(std::shared_ptr<std::thread> worker, std::string runner) {
    std::shared_ptr<std::thread> swapper = std::make_shared<std::thread>([runner]() {
        system(runner.c_str());
    });
    std::swap(*worker, *swapper);
    swapper->join();
}

int main(int argc, char** argv) {
    CLI::App app{"Hot reload anything by @kubgus."};

    std::string runner = "echo No runner command! (use -r tag)";
    app.add_option("-r,--run,--runner", runner, "Set command to run on refresh. (ex:\"g++ main.cpp; ./a.out\")");

    std::string extensions = "c;cpp;h;hpp";
    app.add_option("-e,--extension,--extensions", extensions, "Choose which file extensions are monitored. (ex:\"cpp;h;js;py\")");

    std::string directory = "./";
    app.add_option("-d,--dir,--directory", directory, "Choose which directory is monitored. (ex:\"./src/\")");

    CLI11_PARSE(app, argc, argv);

    std::cout << "Hotpot CLI by @kubgus.\n"
              << "Website: https://gustafik.com/\n\n"
              << "Launching!\n";

    std::shared_ptr<std::thread> worker = std::make_shared<std::thread>([runner]() {
        system(runner.c_str());
    });

    HotWatch watcher{ directory };
    std::cout << "Listening for file changes...\n\n";
    watcher.start_loop([worker,runner,extensions](std::string file) {
        for (char* tok = strtok(strdup(extensions.c_str()), ";"); tok != NULL; tok = strtok(NULL, ";"))
            if (file.substr(file.find_last_of(".") + 1) == tok) {
                std::cout << '\n' << "Detected change in " << file << "!\n"
                          << "Refreshing...\n\n";
                run(worker, runner);
            }
    });
    return 0;
}
