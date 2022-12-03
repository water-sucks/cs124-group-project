#ifndef _UI_H_
#define _UI_H_

#include <map>
#include <string>

#include "models.hpp"
#include "structures/list.hpp"

typedef std::map<std::string, Item> Items;

Items load_items(std::string filename);
List<Item> get_items(Items store);

#endif