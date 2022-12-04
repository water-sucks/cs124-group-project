#ifndef _STORE_H_
#define _STORE_H_

#include "models.hpp"
#include "structures/list.hpp"

Store load_items(std::string filename);
Cart shopping_flow(const Store& store);

#endif
