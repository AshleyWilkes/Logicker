#pragma once

template<typename T>
concept exists = std::is_void_v<T> || ! std::is_void_v<T>;
