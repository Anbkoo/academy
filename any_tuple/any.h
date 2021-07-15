#pragma once
#include <iostream>

class any
	{
	public:
		any(any&& other) noexcept : data(other.data), type_data{&typeid(other.type_data) }
			{
			other.data = nullptr;
			}

		template<class ValueType>
		any(ValueType&& value) noexcept : data(new ValueType{ value }), type_data{&typeid(value) } {}
		any(const any& tmp) : data(tmp.data), type_data(tmp.type_data) {}

		const std::type_info& type() const { return data ? *type_data : typeid(void); }

		bool has_value() const noexcept
			{
			return data;
			}

		void reset() noexcept
			{
			delete data;
			data = nullptr;
			}

		~any()
			{
			reset();
			}

		any& operator=(const any& rhs)
			{
			data = rhs.data;
			return *this;
			}

		template<typename ValueType>
		any& operator=(ValueType&& rhs) 
			{
			type_data = &typeid(rhs);
			data = new ValueType(rhs);
			return *this;
			}

		auto get_data()
			{
			return data;
			}

	private:
		const std::type_info* type_data;
		void* data;
	};

class bad_any_cast : std::exception {
public:
	const char* what() const noexcept override {
		return "bad any cast";
		}
	};


template<class T>
T& any_cast(any& a) {
	if (a.type() != typeid(T)) {
		throw bad_any_cast();
		}
	return *static_cast<T*>(a.get_data());
	}