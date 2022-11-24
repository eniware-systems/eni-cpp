//
// Created by mvonkeil on 4/12/22.
//

#include <eni/util.h>

#include <map>
#include <set>
#include <string>
#include <vector>

namespace eni {

static_assert(container_type<std::vector<unsigned char>>);
static_assert(container_type<std::string>);
static_assert(container_type<std::set<int>>);
static_assert(container_type<std::map<int, int>>);

}// namespace eni