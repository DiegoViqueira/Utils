/*
Logger
@Autor: Diego Viqueira
@Date: 16/02/2017
@decription:
	File Logger Class
*/

#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <string>
#include <iostream>
#include <boost/filesystem/path.hpp>


using namespace std;

namespace utils
{ 
	class Logger
	{
		
	public:

		//Enum of Log Levels
		enum LEVEL
		{
			trace,
			debug,
			info,
			warning,
			error,
			fatal
		};
		
		//Constuctor of Service Task implemetacion
		//Default Constructor
		Logger();

		//Constuctor of Service Task implemetacion
		//@Param: Path -  path of log files
		//@Param: Name -  Name of File Written for the Logger without extension
		//@Param: level_filter -  Logger Level filter
		Logger( boost::filesystem::path const&  Path, const std::string& Name , Logger::LEVEL level_filter);
		
		//log Function
		//@Param: level - enum of Levels of log 
		//@Param: msg - message to print in the file
		void log( LEVEL lv, const char* msg);
	
	};
}
#endif