#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Функция для вывода справки
void printHelp() {
  std::cout << "Application Help:\n";
  std::cout << "Usage: app [options]\n";
  std::cout << "Options:\n";
  std::cout << "  -p <path_to_file>   Path to system configuration file\n";
  std::cout << "  -h                  Display this help message\n";
  std::cout << "  -s <speed>          Simulation speed\n";
  std::cout << "  -t <template_path>  Create system template in specified folder\n";
  std::cout << "\nDescription:\n";
  std::cout << "If no configuration path is provided, the application checks for\n";
  std::cout << "previously running systems and either starts the last active one\n";
  std::cout << "or displays a message if none are found.\n";
}

// Функция для проверки наличия ранее запущенных систем
bool checkForRunningSystems() {
  // Здесь должна быть реальная проверка, но для примера просто возвращаем false
  return false;
}

// Функция для запуска последней активной системы
void startLastActiveSystem() {
  std::cout << "Starting last active system...\n";
  // Реальная логика запуска
}

// Функция для создания шаблона конфигурации
void createTemplate( const std::string& path ) {
  std::cout << "Creating system template in: " << path << "\n";
  // Реальная логика создания шаблона
}

int main( int argc, char* argv[] ) {
  std::string configPath;
  std::string speed;
  std::string templatePath;
  bool helpRequested = false;
  bool templateRequested = false;

  // Парсинг аргументов командной строки
  for( int i = 1; i < argc; ++i ) {
    std::string arg = argv[i];

    if( arg == "-h" ) {
      helpRequested = true;
    }
    else if( arg == "-p" && i + 1 < argc ) {
      configPath = argv[++i];
    }
    else if( arg == "-s" && i + 1 < argc ) {
      speed = argv[++i];
    }
    else if( arg == "-t" && i + 1 < argc ) {
      templatePath = argv[++i];
      templateRequested = true;
    }
  }

  // Обработка запроса справки
  if( helpRequested ) {
    printHelp();
    return 0;
  }

  // Обработка запроса создания шаблона
  if( templateRequested ) {
    createTemplate( templatePath );
    return 0;
  }

  // Основная логика приложения
  if( !configPath.empty() ) {
    std::cout << "Starting system with configuration: " << configPath;
    if( !speed.empty() ) {
      std::cout << " at speed: " << speed;
    }
    std::cout << "\n";
    // Здесь должна быть реальная логика запуска с указанным конфигом
  }
  else {
    if( checkForRunningSystems() ) {
      startLastActiveSystem();
      if( !speed.empty() ) {
        std::cout << "Setting simulation speed: " << speed << "\n";
      }
    }
    else {
      std::cout << "No active systems found and no configuration provided.\n";
      std::cout << "Please specify a configuration file with -p or use -h for help.\n";
    }
  }

  return 0;
}