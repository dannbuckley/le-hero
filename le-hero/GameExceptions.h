/**
 * GameExceptions.h
 * Copyright (c) 2020 Daniel Buckley
 */

#pragma once

#include <exception>

namespace le_hero {
    namespace exception {
        struct unsuccessful_lua_parse_error : public std::exception {
            const char* what() const throw() {
                return "Encountered an error while parsing a Lua game file. See 'log.txt' for more info.";
            }
        };

        struct unexpected_type_error : public std::exception {
            const char* what() const throw() {
                return "Unexpected type encountered when parsing Lua file. See 'log.txt' for more info.";
            }
        };
    }
}