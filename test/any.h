#pragma once
#include <iostream>

class any
	{
	public:
		any() = default;
		~any()
			{
			reset();
			}

		template<class ValueType>
		any(ValueType&& value) noexcept 
			: data(new ValueType{ value }), type_data{&typeid(value) } {}

		any(const any& tmp) 
			: data(tmp.data), type_data(tmp.type_data) {}

		any(any&& other) noexcept : data(other.data), type_data{ &typeid(other.type_data) }
			{
			any temp;
			swap(other, temp);
			}

		any& operator=(const any& rhs);
		any& operator=(any&& rhs) noexcept;

		template<typename ValueType,
			typename std::enable_if_t < !std::is_same<std::decay_t<ValueType>, any>{}, int >>
		any& operator=(ValueType&& rhs);

		const std::type_info& type() const;
		bool has_value() const noexcept;
		void reset() noexcept;
		auto get_data() const;
		void swap(any& other) noexcept;
		void swap(any& lhs, any& rhs) noexcept;

	private:
		const std::type_info* type_data;
		void* data;
	};

const std::type_info& any::type() const 
	{ 
	return data ? *type_data : typeid(void); 
	}

bool any::has_value() const noexcept
	{
	return data;
	}

void any::reset() noexcept
	{
	delete data;
	data = nullptr;
	}

any& any::operator=(const any& rhs)
	{
	data = rhs.data;
	return *this;
	}

any& any::operator=(any&& rhs) noexcept
	{
	data = std::move(rhs.data);
	rhs.reset();
	return *this;
	}

template<typename ValueType, 
	typename std::enable_if_t <!std::is_same<std::decay_t<ValueType>, any>{}, int>>
any& any::operator=(ValueType&& rhs)
	{
	type_data = &typeid(rhs);
	data = new ValueType(std::forward<ValueType>(rhs));
	return *this;
	}

void any::swap(any& other) noexcept
	{
	data = std::move(other.data);
	type_data = std::move(other.type_data);
	}

void any::swap(any& lhs, any& rhs) noexcept
	{
	lhs.swap(rhs);
	}

auto any::get_data() const
	{
	return data;
	}

class bad_any_cast : std::exception {
public:
	const char* what() const noexcept override {
		return "bad any cast";
		}
	};


template<class T>
const T& any_cast(const any& a) {
	if (a.type() != typeid(T)) {
		throw bad_any_cast();
		}
	return *static_cast<T*>(a.get_data());
	}