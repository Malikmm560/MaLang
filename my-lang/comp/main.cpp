#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

std::map<std::string, std::string> variables;

void print_now(const std::string& content) {
    std::string clean = content;
    clean.erase(remove_if(clean.begin(), clean.end(), ::isspace), clean.end());

    // If it's a variable
    if (variables.count(clean)) {
        std::cout << variables[clean] << std::endl;
    } else {
        // Check for quoted string
        if (clean.front() == '"' && clean.back() == '"') {
            clean = clean.substr(1, clean.size() - 2);
        }
        std::cout << clean << std::endl;
    }
}

void print_wait(const std::string& args) {
    size_t open_paren = args.find('(');
    size_t comma = args.find(',');
    size_t close_paren = args.find(')');

    if (open_paren == std::string::npos || comma == std::string::npos || close_paren == std::string::npos) return;

    std::string delay_str = args.substr(open_paren + 1, comma - open_paren - 1);
    std::string message = args.substr(comma + 1, close_paren - comma - 1);

    delay_str.erase(remove_if(delay_str.begin(), delay_str.end(), ::isspace), delay_str.end());
    message.erase(remove_if(message.begin(), message.end(), ::isspace), message.end());

    int delay = 0;
    try {
        if (variables.count(delay_str)) {
            delay = std::stoi(variables[delay_str]);
        } else {
            delay = std::stoi(delay_str);
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid delay time: " << delay_str << std::endl;
        return;
    }



    std::this_thread::sleep_for(std::chrono::seconds(delay));

    if (variables.count(message)) {
        std::cout << variables[message] << std::endl;
    } else {
        if (message.front() == '"' && message.back() == '"') {
            message = message.substr(1, message.size() - 2);
        }
        std::cout << message << std::endl;
    }
}

void eval_line(const std::string& line) {
    std::string trimmed = line;
    trimmed.erase(remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());

    if (line.find("publicvar") != std::string::npos) {
        size_t name_start = line.find("var") + 4;
        size_t eq = line.find("=");
        std::string name = line.substr(name_start, eq - name_start);
        std::string val = line.substr(eq + 1);
        name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
        val.erase(remove_if(val.begin(), val.end(), ::isspace), val.end());
        if (val.front() == '"' && val.back() == '"') {
            val = val.substr(1, val.size() - 2);
        }
        variables[name] = val;
    } else if (line.find("print.now(") != std::string::npos) {
        size_t start = line.find("print.now(") + 10;
        size_t end = line.find(")", start);
        std::string content = line.substr(start, end - start);
        print_now(content);
    } else if (line.find("print.wait(") != std::string::npos) {
        size_t start = line.find("print.wait(");
        std::string args = line.substr(start);
        print_wait(args);
    }
}

bool valid_class_structure(const std::string& content) {
    return content.find("public class main") != std::string::npos &&
           content.find("public start()") != std::string::npos;
}

int main(int argc, char* argv[]) {
    std::cout << "MalLang using v1.0" << std::endl;

    if (argc < 2) {
        std::cerr << "Usage: ./mallang <file.mlk>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::string full_content;
    std::string line;
    while (std::getline(file, line)) {
        full_content += line + "\n";
    }
    file.close();

    if (!valid_class_structure(full_content)) {
        std::cerr << "Error: MalLang script must contain 'public class main' and 'public start()'" << std::endl;
        return 1;
    }

    std::istringstream iss(full_content);
    while (std::getline(iss, line)) {
        // Remove braces and empty lines
        std::string trimmed = line;
        trimmed.erase(remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());
        if (trimmed.empty() || trimmed == "{" || trimmed == "}") continue;

        eval_line(line);
    }

    return 0;
}
