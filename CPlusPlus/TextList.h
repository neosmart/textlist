/*
* A C++ text list generator
* Author: Mahmoud Al-Qudsi <mqudsi@neosmart.net>
* Copyright (C) 2015 - 2017 by NeoSmart Technologies
* This code is released under the terms of the MIT License
* Project and documentation at https://github.com/neosmart/textlist
*/

#pragma once

#include <string>
#include <deque>
#include <sstream>
#include <iostream>

namespace NeoSmart
{
	namespace TextList
	{
#define ENUM_FLAG_OPERATOR(T,X) inline T operator X (T lhs, T rhs) { return (T) (static_cast<::std::underlying_type_t <T>>(lhs) X static_cast<::std::underlying_type_t <T>>(rhs)); } 
#define ENUM_FLAGS(T) \
    enum class T; \
    inline T operator ~ (T t) { return (T) (~static_cast<::std::underlying_type_t <T>>(t)); } \
    ENUM_FLAG_OPERATOR(T,|) \
    ENUM_FLAG_OPERATOR(T,^) \
    ENUM_FLAG_OPERATOR(T,&) \
    enum class T

		ENUM_FLAGS(ListFormat)
		{
			OxfordSeparator = 1,
			None = 2,
			Default = ListFormat::OxfordSeparator,
		};

		template<class T>
		static std::string Make(const T& entities, ListFormat formatting = ListFormat::Default, std::string conjunction = "and", std::string separator = ",")
		{
			bool oxfordComma = ((formatting & ListFormat::OxfordSeparator) == ListFormat::OxfordSeparator) || conjunction.empty();
			std::string space = " ";

			std::stringstream sb;
			auto buffer = std::deque<typename T::value_type>();

			for (const auto &e : entities)
			{
				buffer.push_back(e);
				if (buffer.size() < 4)
				{
					continue;
				}

				//three elements have been guaranteed put aside
				auto t = buffer.front();
				buffer.pop_front();
				sb << t << separator << space;
			}

			if (buffer.size() >= 1)
			{
				sb << buffer.front();
				buffer.pop_front();
			}

			//remember, buffer count has dropped
			if (buffer.size() == 1) //means guaranteed only ever two entries
			{
				if (conjunction.empty())
				{
					sb << separator << space << buffer.front();
					buffer.pop_front();
				}
				else
				{
					sb << space << conjunction << space << buffer.front();
					buffer.pop_front();
				}
			}
			else if (buffer.size() == 2)
			{
				sb << separator << space << buffer.front() << (oxfordComma ? separator.c_str() : "") << space;
				buffer.pop_front();

				if (conjunction.empty())
				{
					sb << buffer.front();
					buffer.pop_front();
				}
				else
				{
					sb << conjunction << space << buffer.front();
					buffer.pop_front();
				}
			}
			return sb.str();
		}
	}
}
