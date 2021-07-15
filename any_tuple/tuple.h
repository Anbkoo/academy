#pragma once
#include <iostream>

template<typename T>
class tuple_template
	{
	public:
		tuple_template() = default;
		explicit tuple_template(const T& _t) : t(_t) {}

		auto get_value() const
			{
			return t;
			}
	private:
		T t;
	};

template<typename... Args>
class tuple: public tuple_template<Args>...
	{
	public:
		tuple(Args... _args) : tuple_template<Args>{_args}...{}
	};

template<class... Args >
auto make_tuple(Args&&... args)
	{
	return tuple<Args...>(std::forward<Args>(args)...);
	}

template<typename... Args>
constexpr tuple<Args&...> tie(Args&... args) noexcept
	{
	return tuple<Args&...>(args);
	}

template<>
class tuple<> {};
