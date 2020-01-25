/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  FILE MANAGER CLASS HEADER                          *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#pragma once

// System libraries includes.
#include <string>
#include <vector>

namespace srt::utility
{

class FileManager 
{

public:

	static std::vector<std::string> getFilesList(const std::string &dir);
	static void writeFile(const std::string &filename, const std::string &content, const bool append = true);
};

}
