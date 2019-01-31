/*
 * FileSysTest.cc
 *
 *  Created on: Mar 20, 2018
 *      Author: sburnwal
 */

#include <iostream>
#include <string>
#include <sstream>
#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>

void testBoostCreateDir();
void testDirCleanup();

void testDirCleanup() {
	boost::system::error_code lErrCode;
	boost::filesystem::path dirPath = "/Users/sburnwal/Projects/Workspaces/temp/y";
	bool x = boost::filesystem::create_directory(dirPath, lErrCode);
	std::cout << "dir created :" << x << std::endl;

	std::string filePath = dirPath.string() + "/y.txt";
	std::cout << "creating file " << filePath <<std::endl;
	std::ofstream ofile;
	ofile.open(filePath);
	ofile.close();

	bool exists = boost::filesystem::exists(filePath);
	if(exists) {
		std::cout << "Removing dirs" << std::endl;
		boost::system::error_code err;
		int count = boost::filesystem::remove_all(dirPath, err);
		std::cout << "Count of files deleted " << count << ", err: " << err.message() << " errcode:" << err.value() << std::endl;
	}
}

void testBoostCreateDir() {
	boost::system::error_code lErrCode;
	boost::filesystem::path dir("/Users/sburnwal/Projects/Workspaces/temp/x");
	bool x = boost::filesystem::create_directory(dir, lErrCode);
	std::cout << x << std::endl;
}
