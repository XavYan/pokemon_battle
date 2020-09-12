#include <languageManager.hpp>
#include <iostream>

LanguageManager::~LanguageManager() {
    texts_.clear();
    supportedLangs_.clear();
}

LanguageManager* LanguageManager::instance_ = nullptr;

LanguageManager* LanguageManager::instance() {
    if (!instance_) {
        instance_ = new LanguageManager ();
    }
    return instance_;
}

void LanguageManager::loadTexts () {
    texts_.clear();

    // Buscamos en el directorio lang/ todos los archivos con extension
    // el idioma establecido
    DIR* dir;
    struct dirent *ent;

    dir = opendir(languagesDirectory.c_str());

    if (dir == NULL) {
        // error
        throw std::system_error(errno, std::system_category(), "error al abrir el archivo de idioma");
    }

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            std::regex aux = std::regex("[a-zA-Z]+_([a-z][a-z]).lang");
            std::cmatch match;
            if (std::regex_search(ent->d_name, match, aux)) {
                if (match[1] == actualLanguage_) {
                    processFileStrings(languagesDirectory + '/' + ent->d_name);
                    // std::cout << "File: " << languagesDirectory + '/' + ent->d_name << '\n';
                }
            }
        }
    }

    closedir(dir);

    // std::cout << "Lista de encuentros: ";
    // for (auto pair: texts_) {
    //     std::cout << "(\"" << pair.first << "\", \"" << pair.second << "\") ";
    // }
    // std::cout << "\n";
}

std::string LanguageManager::getText (const std::string& key) const {
    if (texts_.find(key) != texts_.end()) {
        // std::cout << "DEBUG: Encontrado: Si\n";
        // std::cout << "Found --> " << texts_.at(key) << '\n';
        return texts_.at(key);
    } else {
        // std::cout << "DEBUG: Encontrado: No\n";
        return "";
    }
}

void LanguageManager::changeLanguage (std::string lang) {
    
    if (supportedLangs_.find(lang) != supportedLangs_.end()) {
        loadLanguage(lang);
        loadTexts();
    }
}

LanguageManager::LanguageManager () {
    loadSupportedLanguages();
    loadTexts();
}

void LanguageManager::loadSupportedLanguages() {
    std::ifstream langsFile;
    langsFile.open(supportedLanguagesFile);

    bool first = true;
    while (!langsFile.eof()) {
        char cadena[100];
        langsFile.getline(cadena, 100);
        if (first) {
            loadLanguage(cadena);
            first = false;
        }
        supportedLangs_.insert(cadena);
    }

    langsFile.close();
}

void LanguageManager::loadLanguage (std::string lang) {
    std::cmatch match;
    if (std::regex_search(lang.c_str(), match, langExtensionPattern)) {
        actualLanguage_ = match[1];
    }
}

void LanguageManager::processFileStrings (std::string filename) {
    std::ifstream file;
    file.open(filename);

    if (file) {
        while (!file.eof()) {
            char line [200];
            file.getline(line, 200);
            std::cmatch match;
            if (std::regex_search(line, match, textStringPattern)) {
                texts_.insert(std::pair<std::string, std::string>(match[1], match[2]));
            }
        }
    }

    file.close();
}