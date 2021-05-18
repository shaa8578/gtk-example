#include "worker.h"

#include <fstream>

//------------------------------------------------------------------------------
bool worker::searchWord(const std::string& filePath, const std::string& word) {
  std::ifstream reader(filePath);
  if (reader.is_open() == false) return false;

  /** Максимальная длина строки */
  static const size_t STR_MAXIMUM_LENGTH = 4096U;
  char buffer[STR_MAXIMUM_LENGTH];
  bool is_finded(false);
  while (reader.eof() == false) {
    reader.getline(buffer, STR_MAXIMUM_LENGTH);
    std::string line(buffer);
    if ((is_finded = (line.find(word) != line.npos)))
      break;
    else
      continue;
  }
  reader.close();
  return is_finded;
}
