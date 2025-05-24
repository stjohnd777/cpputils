/*
 * Utils.h
 *
 *  Created on: Jun 25, 2020
 *      Author: local-admin
 */

#pragma once

#include <string>

namespace dsj::utils {

    std::string random_string(std::string::size_type length);

    std::string random_string_ext(std::string::size_type length);

    std::string random_int(std::string::size_type length);
}


