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
#include <dirent.h>
#include <fstream>

using namespace std;

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
			DIR *dirp;
			struct dirent *directory;

			dirp = opendir(dir.c_str());
			if (dirp){
				while ((directory = readdir(dirp)) != NULL)
					if(directory->d_type  == DT_REG && directory->d_name[0] != '.') // Exclude hidden file.
						files.push_back(directory->d_name);
				
				closedir(dirp);
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
