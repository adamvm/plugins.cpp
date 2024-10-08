#pragma once

// Abstract class for the plugin interface
class PluginAPI {
public:
    virtual void execute() = 0; // Pure virtual function for execution
    virtual ~PluginAPI() {} // Virtual destructor
};

extern "C" PluginAPI* create_plugin(); // Function to create a plugin instance

