//============================================================================
// Name        : Asn1Utils.hpp
// Author      : Diego Viqueira
// Version     :
// Description : ASN1 Encoder / Decoder
//============================================================================

#ifndef _ASN1_UTILS_HPP_
#define _ASN1_UTILS_HPP_

// General Includes
#include <sstream>
#include <vector>
#include <string.h>
#include <math.h>       /* pow */
#include <exception>


typedef unsigned char UInt8;

//============================================================================
//                      CLASSES
//============================================================================

namespace asn1
{

namespace utils
{
	// Will only be supporting int values up to this max
	const  int MAX_ASN_INT_BYTES = 4;
	const int MAX_ASN_INT_VALUE = (int)pow(2, MAX_ASN_INT_BYTES*8)-1; 
	
	
	const std::string encode_int_asn1(int integer_value)
	{
		std::string temp_str;
		
		if (integer_value <= MAX_ASN_INT_VALUE)
		{
			// First encode the integer in the temp buffer
			UInt8 temp[sizeof(int)] ;
			
			int i,j,octets_needed;

			/*
			 * First encode the integer in the temp buffer
			 */

			for( i = sizeof( int ) - 1; i >= 0; --i )
			{
					temp[ i ] = (UInt8)( integer_value & 0xFF );
					integer_value = integer_value >> 8;
			}

			/*
			 * Discard any octets which are not needed (according to X.209)
			 */

			for( j = 0; j < sizeof( int ) - 1; ++j )
			{
					if( temp[ j ] == 0 && ( temp[ j + 1 ] & 0x80 ) == 0 )
					{
							/* Discard temp[ j ] */
					}
					else if( temp[ j ] == 0xFF && ( temp[ j + 1 ] & 0x80 ) != 0 )
					{
							/* Discard temp[ j ] */
					}
					else
					{
							/* temp[ j ] is needed */
							break;
					}
			}			
			
			/*
			 * Now we know how many octets are needed to encode the integer
             */

			 octets_needed = sizeof( int ) - j;
			 
			 for( i = 0; i < octets_needed; ++i )
			 {
                 temp_str+=temp[ j + i ];
             }
              
			  
			
			return temp_str;
		}
		else
		{
			throw "Integer value too large ";
		}
		
		return temp_str;
	}
	
	
	const UInt8 TAG_BOOLEAN 		= 0x01;
	const UInt8 TAG_INTEGER 		= 0x02;
	const UInt8 TAG_OCTET_STRING 	= 0x04;
	const UInt8 TAG_STRING 		= 0x16;
	const UInt8 TAG_SEQUENCE 		= 0x30;

	struct TLV
	{
		TLV(UInt8 iTag,int iLen,const std::string& iValue):tag(iTag),len(iLen),value(iValue){};
		UInt8 tag;
		int   len;
		std::string value;
	};

	typedef std::vector<TLV> TLVS;

	template<class CharT = char, class Traits = std::char_traits<CharT> >
	class MakeTLV
	{
		/// ostringstream que se usa para construir el string.
		mutable std::basic_ostringstream<CharT,Traits>	m_oOss;


	public:
		/// conversión implícita a string. operador()
		operator std::basic_string<CharT,Traits>() const {
			return m_oOss.str();
		}

		/// conversion implicita a TLVS operador >>
		const MakeTLV& operator >> (const int int_t) const {
				std::cout <<"ASNUMBER"<<endl;

				m_oOss<< TAG_INTEGER << (UInt8)sizeof(UInt8) << static_cast<unsigned int>(int_t);
			return *this;
		}


		/// Especialización para los Int operador << OVELOADING
		const MakeTLV& operator<< (const int int_t) const {
	
				m_oOss<< TAG_INTEGER << (UInt8)sizeof(UInt8) << encode_int_asn1(int_t) ;
			return *this;
		}

		/// Especialización para los const char* operador << OVELOADING
		const MakeTLV& operator<< (const char* str ) const {
				int length=strlen(str);

				m_oOss<< TAG_OCTET_STRING << (UInt8)length << str ;
			return *this;
		}

		/// Especialización para los strings operador << OVELOADING
		const MakeTLV& operator<< (const std::string str ) const {
				m_oOss<< TAG_STRING << (UInt8)str.length() << str ;
			return *this;
		}

		/// Especialización para los vector<int> - TODO operador << OVELOADING
		const MakeTLV& operator<< (const std::vector<int> int_vect ) const {
				m_oOss<< TAG_SEQUENCE << (UInt8)int_vect.size() << int_vect.data() ;
			return *this;
		}

		/// Especialización para los const bool operador << OVELOADING
		const MakeTLV& operator<< (const  bool bol ) const {
				m_oOss<< TAG_BOOLEAN << (UInt8)sizeof(bol) << bol ;
			return *this;
		}
		
		/// Especialización para un TLV
		const MakeTLV& operator<< (const  TLV& otlv ) const {
				m_oOss<< otlv.tag << (UInt8)otlv.len << otlv.value ;
			return *this;
		}


	};


	/// \typedef MakeTLVstring Para evitar usar '<>'
	typedef MakeTLV<char,std::char_traits<char> >		MakeTLVstring;


/*! @} */



}//end namespace utils

}//end namespace asn1


#endif
