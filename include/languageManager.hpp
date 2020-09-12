#pragma once

#include <fstream>
#include <map>
#include <string>
#include <set>

#include <sys/types.h> // para clase DIR
#include <dirent.h> // para struct dirent

#include <regex>

class LanguageManager {
private:
    std::string filename_;
    std::map <std::string, std::string> texts_;
    std::set<std::string> supportedLangs_;

    std::string actualLanguage_;

    static LanguageManager* instance_;

    // Constants
    const std::regex langExtensionPattern = std::regex("([a-z][a-z])_[A-Z][A-Z]");
    const std::regex textStringPattern = std::regex("([a-zA-Z]+): *\"([{}\\w-% .áéíóúÁÉÍÓÚ,/¿?:¡!ñ\\(\\)']*)\"");
    const std::string supportedLanguagesFile = "./langs.txt";
    const std::string languagesDirectory = "./lang";

public:

    ~LanguageManager();

    static LanguageManager* instance();

    void loadTexts ();

    std::string getText (const std::string& key) const;

    void changeLanguage (std::string lang);

private:
    LanguageManager ();

    void loadSupportedLanguages ();
    void loadLanguage (std::string lang);
    void processFileStrings (std::string filename);
};