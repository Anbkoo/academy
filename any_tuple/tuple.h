#pragma once
#include <iostream>

template<typename... Args>
class tuple;

template<typename T, typename... Args>
class tuple<T, Args...>
	{
	public:
		tuple(const T& _t, Args... _args) : t(_t), args{ _args... }{};

		constexpr tuple<Args...>& get_rest() & noexcept 
			{
			return (*this).args;
			}
		
		constexpr tuple<Args...>&& get_rest() && noexcept 
			{
			return std::move((*this).args);
			}

		template < class... _Args>
		constexpr tuple & operator=(tuple<_Args...>&rhs) noexcept
		{
			t = rhs.t;
			get_rest() = rhs.get_rest();
			return *this;
		}

		template <class... _Args>
		constexpr tuple& operator=(tuple<_Args...>&& rhs) noexcept
			{
			t = std::move(rhs.t);
			get_rest() = std::move(rhs).get_rest();
			return *this;
			}

		
		T t;
		tuple<Args...> args;
	};

template <>
class tuple<> {};

template<typename T>
class tuple<T>
	{
	public:
		tuple() = default;
		explicit tuple(const T& _t) : t(_t) {}

		template <typename U>
		constexpr tuple& operator=(tuple<U>&& rhs) noexcept
			{
			t = std::move(rhs.t);
			return *this;
			}

		template <typename U>
		constexpr tuple& operator=(const tuple<U>& rhs) noexcept
			{
			t = std::move(rhs.t);
			return *this;
			}

		T t;
	};



template <std::size_t i>
class get_index
	{
	public:

	template<typename T, typename... Args>
	static auto get_ind(tuple<T, Args...>* t)
		{
		return get_index<i - 1>::get_ind(&t->args);
		}
	};


template <>
class get_index<0>
	{
	public:
		template<typename T, typename... Args>
		static auto get_ind(tuple<T, Args...>* t)
			{
			return t->t;
			}
	};

template <std::size_t i, template <typename... Args> typename tuple, typename... Args>
auto get(tuple<Args...>& t)
	{
	return get_index<i>::get_ind(&t);
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

