/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  FILE MANAGER CLASS FILE                            *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "utility/FileManager.hpp"

// System includes.
#include <filesystem>
#include <fstream>

namespace srt::utility
{

std::vector<std::string> FileManager::getFilesList(const std::string &dir){
	std::vector<std::string> files;
			
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{
		files.push_back(entry.path().filename().string());
	}

	return files;
}

void FileManager::writeFile(
	const std::string &filename, const std::string &content, const bool append)
{
	auto flag = append ? std::fstream::app : std::fstream::trunc;
	std::ofstream file(filename, std::fstream::out | flag);

	file << content;

	file.close();
}	

}
