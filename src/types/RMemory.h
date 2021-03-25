#pragma once
#include <memory>

namespace rocket
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    Ref<T> new_ref(T args) { return std::make_shared(args); }
}