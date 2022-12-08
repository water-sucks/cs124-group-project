#ifndef _FLOWS_H_
#define _FLOWS_H_

#include "cart.hpp"
#include "store.hpp"
#include "structures/list.hpp"

List<Item> giving_flow();
Cart shopping_flow(const Store& store);

#endif
