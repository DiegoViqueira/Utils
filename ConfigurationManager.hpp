/*
Configuration Manager 
@Autor: Diego Viqueira
@Date: 16/02/2017
@decription:
	Handler to Configuration
*/

#ifndef __CONFIG_MANAGER_H_
#define __CONFIG_MANAGER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <iostream>




using namespace std;

namespace utils
{ 
	class ConfigManager
	{
	public:

		//Constuctor of Service Task implemetacion
		//@Param: file -  full path included file name to Configuration
		//@Throw std::exception in case file doesnt exist
		ConfigManager(const std::string& file);
	
		//Get Node Value
		//@Param: path to node in XML dot separated Ex: Nodo1.Value
		//@Param: default value in case if the node value conversion fails or node doesnt exist
		

		template<typename T>
		T GetNodeValue(const std::string& path, const T& default_value) {
			try
			{
				return m_tree.get_child(path.c_str()).get_value(default_value);
			}
			catch (const std::exception&)
			{
				return default_value;
			}
			
			
		}


	private:
		string m_conf_file;
		boost::property_tree::ptree m_tree;
	};
}
#endif