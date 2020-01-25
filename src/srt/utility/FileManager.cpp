/*******************************************************
 *                                                     *
 *  srt: Basic Ray Tracer                              *
 *                                                     *
 *  FILE MANAGER CLASS FILE                            *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "FileManager.hpp"

// System includes.
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

namespace srt {
	namespace utility {
		/**
		 * @brief Returns the names of all the files in a directory.
		 * 
		 * @param dir - The directory in which search.
		 * @return vector<string> - The vector with the names of the files.
		 */
		vector<string> FileManager::getFiles(const std::string &dir){
			vector<string> files;
			
			for (const auto& entry : directory_iterator(dir))
			{
				files.push_back(entry.path().filename().string());
			}

			return files;
		}

		/**
		 * @brief Writes a string in a file.
		 * 
		 * @param filename - The file on which write.
		 * @param content - The string to write.
		 * @param append - True if the new string must be appended, false otherwise.
		 */
		void FileManager::writeFile(const string &filename, const string &content, const bool append){
			auto flag = append ? fstream::app : fstream::trunc;
			ofstream file(filename, fstream::out | flag);

			file << content;

			file.close();
		}	
	}
}
