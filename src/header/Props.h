/*
 * Props.h
 *
 *  Created on: Jun 12, 2020
 *      Author: local-admin
 */
#pragma once

#include <string>
#include <sstream>

namespace dsj {

    namespace utils {

        class Props {

        public:
            static std::string getEnvironmentVarAsString(const std::string name);

            static int getEnvironmentVarAsInt(const std::string name);

        public:
            Props();

            Props(std::string propertiesFile) {

            };

            virtual ~Props();
        };
    }
}

