#include "DoubleBuffer.h"
#include "Buffer.h"

#include <vector>

std::array<DoubleBuffer<std::shared_ptr<Buffer>>, 2> doubleBuffer;