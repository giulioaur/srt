/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  FILE MANAGER CLASS HEADER                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/

#ifndef S_UTILITY_FILEMANAGER_S
#define S_UTILITY_FILEMANAGER_S

// System libraries includes.
#include <string>
#include <vector>

namespace srt {
namespace utility {
class FileManager {

public:
	// METHODS

	static std::vector<std::string> getFiles(const std::string &dir);
	static void writeFile(const std::string &filename, const std::string &content, const bool append = true);
};
}
}

#endif
