#include "plugin_api.h"
#include <iostream>
#include <dlfcn.h>
#include <memory>

class LibraryHandle {
public:
    LibraryHandle(const char* filename)
        : handle_(dlopen(filename, RTLD_LAZY)) {
        if (!handle_) {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
            throw std::runtime_error("Failed to open library");
        }
    }

    ~LibraryHandle() {
        if (handle_) {
            dlclose(handle_);
        }
    }

    void* get() const { return handle_; }

    LibraryHandle(const LibraryHandle&) = delete;
    LibraryHandle& operator=(const LibraryHandle&) = delete;
    LibraryHandle(LibraryHandle&&) = delete;
    LibraryHandle& operator=(LibraryHandle&&) = delete;

private:
    void* handle_;
};

int main() {
    try {
        LibraryHandle handle("./libmyplugin.so");

        typedef PluginAPI* (*create_t)();
        create_t create_plugin = (create_t) dlsym(handle.get(), "create_plugin");
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol 'create_plugin': " << dlsym_error << '\n';
            return 1;
        }

        std::unique_ptr<PluginAPI> plugin(create_plugin());
        plugin->execute(); // Execute the plugin

        return 0;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
