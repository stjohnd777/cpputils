/*
 * Props.h
 *
 *  Created on: Jun 12, 2020
 *      Author: local-admin
 */
#pragma once

#include <string>
#include <sstream>

namespace dsj::utils {

    template<typename T>
    T GetEnvVarAs(const std::string name) {
        T value;
        std::string strValue = std::getenv(name.c_str());

        if (strValue.empty()) {
            throw std::invalid_argument("Environment variable is not set.");
        }

        std::stringstream converter;
        converter << strValue;
        converter >> value;

        if (converter.fail()) {
            throw std::invalid_argument("Failed to convert environment variable to requested type.");
        }

        return value;
    }


}


