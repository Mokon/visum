/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <memory>

namespace graph {

class Edge;

using BidirectionalEdge = std::pair<std::shared_ptr<Edge>,
      std::shared_ptr<Edge>>;

}
