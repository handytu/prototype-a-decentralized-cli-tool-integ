#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

// CLI Tool Integrator Prototype

// CLI Tool Interface
class CLI_Tool {
public:
    virtual std::string get_name() = 0;
    virtual std::string execute(std::string command) = 0;
};

// Decentralized CLI Tool Manager
class CLI_Manager {
private:
    std::map<std::string, CLI_Tool*> tools;

public:
    void add_tool(CLI_Tool* tool) {
        tools[tool->get_name()] = tool;
    }

    std::string execute_tool(std::string tool_name, std::string command) {
        if (tools.find(tool_name) != tools.end()) {
            return tools[tool_name]->execute(command);
        }
        return "Tool not found";
    }
};

// CLI Tool 1 Example (e.g., a calculator)
class CLI_Calculator : public CLI_Tool {
public:
    std::string get_name() override {
        return "calculator";
    }

    std::string execute(std::string command) override {
        std::stringstream ss(command);
        std::string operand1, operator_, operand2;
        ss >> operand1 >> operator_ >> operand2;
        double result;
        if (operator_ == "+") {
            result = std::stod(operand1) + std::stod(operand2);
        } else if (operator_ == "-") {
            result = std::stod(operand1) - std::stod(operand2);
        } else if (operator_ == "*") {
            result = std::stod(operand1) * std::stod(operand2);
        } else if (operator_ == "/") {
            result = std::stod(operand1) / std::stod(operand2);
        } else {
            return "Invalid operator";
        }
        return std::to_string(result);
    }
};

// CLI Tool 2 Example (e.g., a file manager)
class CLI_FileManager : public CLI_Tool {
public:
    std::string get_name() override {
        return "file_manager";
    }

    std::string execute(std::string command) override {
        std::stringstream ss(command);
        std::string action, file_path;
        ss >> action >> file_path;
        if (action == "create") {
            std::ofstream file(file_path);
            if (file.is_open()) {
                return "File created successfully";
            } else {
                return "Failed to create file";
            }
        } else if (action == "delete") {
            if (std::remove(file_path.c_str()) == 0) {
                return "File deleted successfully";
            } else {
                return "Failed to delete file";
            }
        } else {
            return "Invalid action";
        }
    }
};

int main() {
    CLI_Manager manager;

    CLI_Calculator calculator;
    manager.add_tool(&calculator);

    CLI_FileManager file_manager;
    manager.add_tool(&file_manager);

    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        size_t space_pos = command.find(' ');
        std::string tool_name = command.substr(0, space_pos);
        std::string tool_command = command.substr(space_pos + 1);
        std::cout << manager.execute_tool(tool_name, tool_command) << std::endl;
    }

    return 0;
}