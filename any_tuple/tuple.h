#pragma once
#include <iostream>

template<typename... Args>
class tuple;

template<typename T, typename... Args>
class tuple<T, Args...>
	{
	public:
		template <std::size_t i>
		friend class get_index;

		friend class tuple<T&, Args&...>;
		friend class tuple<Args&...>;;

		tuple(const T& _t, const Args&... _args) : t(_t), args{ _args... }{};
		tuple(const tuple<T, Args...>&) = default;
		tuple(tuple<T, Args...>&&) = default;

		// copy
		template < class... _Args>
		constexpr tuple & operator=(const tuple<_Args...>&rhs)
			{
			t = rhs.t;
			args = rhs.args;
			return *this;
			}

		// move
		template <class... _Args>
		constexpr tuple& operator=(tuple<_Args...>&& rhs)
			{
			t = rhs.t;
			args = rhs.args;
			return *this;
			}


	private:
		T t;
		[[no_unique_address]] tuple<Args...> args;
	};

template <>
class tuple<> {};

template <std::size_t i>
class get_index
	{
	public:

	template<typename T, typename... Args>
	static auto get_ind(tuple<T, Args...>& t)
		{
		return get_index<i - 1>::get_ind(t.args);
		}
	};


template <>
class get_index<0>
	{
	public:
		template<typename T, typename... Args>
		static auto get_ind(tuple<T, Args...>& t)
			{
			return t.t;
			}
	};

template <std::size_t i, template <typename... Args> typename tuple, typename... Args>
auto get(tuple<Args...>& t)
	{
	return get_index<i>::get_ind(t);
	}

template<class... Args >
auto make_tuple(Args&&... args)
	{
	return tuple<Args...>(std::forward<Args>(args)...);
	}


template<typename... Args>
constexpr tuple<Args&...> tie(Args&... args) noexcept
	{
	return tuple<Args&...>(args...);
	}
