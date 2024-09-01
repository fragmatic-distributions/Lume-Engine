#include <iostream>

namespace Util {
	std::string GetFileExtension(const char* File) {
		std::string StringFile = File;
		std::size_t found = StringFile.find_last_of(".");
		std::string FileExtension = StringFile.substr(found + 1);

		return FileExtension;
	}
}