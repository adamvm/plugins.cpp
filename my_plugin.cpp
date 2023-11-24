
#include "plugin_api.h"
#include <iostream>

// Concrete class implementing the plugin interface
class MyPlugin : public PluginAPI {
public:
    void execute() override {
        std::cout << "MyPlugin executed" << std::endl; // Implementation of the execute function
    }
};

extern "C" PluginAPI* create_plugin() {
    return new MyPlugin(); // Factory function to create a plugin instance
}
