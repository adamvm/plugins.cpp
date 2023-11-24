
#include "plugin_api.h"
#include <iostream>
#include <dlfcn.h> // For dynamic loading

int main() {
    void* handle = dlopen("./libmyplugin.so", RTLD_LAZY); // Load the plugin library
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // Load the symbol for creating a plugin instance
    typedef PluginAPI* (*create_t)();
    create_t create_plugin = (create_t) dlsym(handle, "create_plugin");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'create_plugin': " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    // Create an instance of the plugin
    PluginAPI* plugin = create_plugin();
    plugin->execute(); // Execute the plugin

    // Clean up
    delete plugin;
    dlclose(handle);
    return 0;
}
