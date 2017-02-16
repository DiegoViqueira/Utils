#include "Utils/ConfigurationManager.hpp"


namespace utils
{ 

ConfigManager::ConfigManager(const std::string& file) :m_conf_file(file), m_tree()
{
	
		read_xml(m_conf_file, m_tree);
		
}

}