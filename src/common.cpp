#include <common.hpp>

std::string formatString (std::string str, std::string arg1,
                                           std::string arg2,
                                           std::string arg3,
                                           std::string arg4,
                                           std::string arg5,
                                           std::string arg6) {

    // for "value=text" values
    const std::regex substitutesPattern("([\\w_-]+)=([\\wáéíóúÁÉÍÓÚñ_-]*)");

    std::smatch result;

    bool with_name = false;
    if (std::regex_search(arg1, result, substitutesPattern) || std::regex_search(arg2, result, substitutesPattern) ||
        std::regex_search(arg3, result, substitutesPattern) || std::regex_search(arg4, result, substitutesPattern))
    {
        with_name = true;
    }

    std::string finalString = str;

    if (with_name) {
        
        // First, we look for the results
        std::map<std::string, std::string> substitutes;

        if (arg1 != std::string()) {
            std::regex_search(arg1, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }
        if (arg2 != std::string()) {
            std::regex_search(arg2, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }
        if (arg3 != std::string()) {
            std::regex_search(arg3, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }
        if (arg4 != std::string()) {
            std::regex_search(arg4, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }
        if (arg5 != std::string()) {
            std::regex_search(arg5, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }
        if (arg6 != std::string()) {
            std::regex_search(arg6, result, substitutesPattern);
            substitutes.insert(std::pair<std::string,std::string>(result[1], result[2]));
        }

        // Then, we catch each {value} in string and change it with its respective values
        for (auto it = substitutes.begin(); it != substitutes.end(); it++) {
            if (finalString.find("{" + it->first + "}") != std::string::npos) {
                finalString.replace(finalString.find("{" + it->first + "}"), 2 + it->first.length(), it->second);
            }
        }
    } else {
        if (arg1 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg1);
        }
        if (arg2 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg2);
        }
        if (arg3 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg3);
        }
        if (arg4 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg4);
        }
        if (arg5 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg5);
        }
        if (arg6 != std::string()) {
            finalString.replace(finalString.find("{}"), 2, arg6);
        }
    }

    // Last, we return the final string
    return finalString;

}