#include "Utils/Logger.hpp"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace trivial = boost::log::trivial;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

namespace utils
{ 

	::boost::log::trivial::severity_level cast_enum( Logger::LEVEL lv)
	{
		switch (lv)
		{
			case utils::Logger::LEVEL::trace : return  ::boost::log::trivial::severity_level::trace;
			case utils::Logger::LEVEL::debug : return  ::boost::log::trivial::severity_level::debug;
			case utils::Logger::LEVEL::info : return  ::boost::log::trivial::severity_level::info;
			case utils::Logger::LEVEL::warning : return  ::boost::log::trivial::severity_level::warning;
			case utils::Logger::LEVEL::error : return  ::boost::log::trivial::severity_level::error;
			case utils::Logger::LEVEL::fatal : return  ::boost::log::trivial::severity_level::fatal;
			default: return ::boost::log::trivial::severity_level::debug;
		}
	}

	Logger::Logger()
	{
		
	}
	Logger::Logger(const std::string& Name , Logger::LEVEL lv)
	{

		
		std::string file= Name;
		file += "_%N.log";
		
		logging::core::get()->set_filter(logging::trivial::severity >= cast_enum(lv));
		
		logging::add_common_attributes();
		
		logging::add_file_log
		(
			keywords::file_name =  file.c_str() ,
			keywords::rotation_size = 10 * 1024 * 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::format = (
				expr::stream
				<<"["<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
				<< "] <" << logging::trivial::severity
				<< "> " << expr::smessage
				) ,
			keywords::auto_flush = true
			
		);

		
	}

	void Logger::log(LEVEL lv, const char* msg)
	{

		switch (lv)
		{
		case utils::Logger::trace:
				BOOST_LOG_TRIVIAL(trace) << msg;
			break;
		case utils::Logger::debug:
				BOOST_LOG_TRIVIAL(debug) << msg;
			break;
		case utils::Logger::info:
			BOOST_LOG_TRIVIAL(info) << msg;
			break;
		case utils::Logger::warning:
			BOOST_LOG_TRIVIAL(warning) << msg;
			break;
		case utils::Logger::error:
			BOOST_LOG_TRIVIAL(error) << msg;
			break;
		case utils::Logger::fatal:
				BOOST_LOG_TRIVIAL(fatal) << msg;
			break;
		default:
			BOOST_LOG_TRIVIAL(debug) << msg;
			break;
		}
	
		
		
		
	}

}