#pragma once

#include "Core/Base.h"

#include <functional>

namespace Color
{
	namespace Utils
	{
		template <typename T, typename... U>
		size_t GetFunctionAddress(std::function<T(U...)> function)
		{
			typedef T(FunctionType)(U...);
			FunctionType** functionPtr = function.template target<FunctionType*>();
			return (size_t) *functionPtr;
		}
	}

	template <typename... Params>
	class Signal
	{
	public:
		using BindingType = std::function<void(Params...)>();
	public:
		Signal() = default;
		Signal(const Signal&) = default;
		Signal& operator=(const Signal&) = default;
		Signal(std::initializer_list<BindingType> bindings)
			: m_Bindings(bindings) { }

		void Bind(const BindingType& binding)
		{
			m_Bindings.push_back(binding);
		}

		void Unbind(const BindingType& binding)
		{
			size_t idx = Find(binding);

			if (idx == SIZE_MAX)
			{
				return;
			}

			m_Bindings.erase(m_Bindings.begin() + idx);
		}

		void Broadcast(Params... params) const
		{
			for (const BindingType& binding : m_Bindings)
			{
				binding(params...);
			}
		}

		// Returns SIZE_MAX if binding is not bound
		size_t Find(const BindingType& binding) const
		{
			size_t addrFindElem = Utils::GetFunctionAddress(binding);

			for (size_t i = 0; i < m_Bindings.size(); i++)
			{
				if (addrFindElem == Utils::GetFunctionAddress(m_Bindings[i]))
				{
					return i;
				}
			}

			return SIZE_MAX;
		}
	private:
		std::vector<BindingType> m_Bindings;
	};

	#define CL_DECLARE_SIGNAL_TYPE(name, ...) typedef ::Color::Signal<__VA_ARGS__> name
}
