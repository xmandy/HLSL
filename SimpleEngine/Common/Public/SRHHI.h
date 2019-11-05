#pragma once

#include <string>
#include <cstdint>

namespace Common
{
	class SRTTI
	{
	public:
		using IdType = std::uint64_t;
		
		virtual ~SRTTI() = default;

		virtual std::uint64_t TypeIdInstance() const = 0;

		virtual SRTTI* QueryInterface(const IdType)
		{
			return nullptr;
		}

		virtual bool Is(IdType) const
		{
			return false;
		}

		virtual bool Is(const std::string&) const
		{
			return false;
		}

		template <typename T>
		T* As() const
		{
			return (Is(T::TypeIdClass())) ? reinterpret_cast<T*>(const_cast<SRTTI*>(this));
		}

		virtual std::string ToString() const
		{
			return "SRTTI";
		}

		virtual bool Equals(const SRTTI* rhs) const
		{
			return this == rhs;
		}
	};

#define SRTTI_DECLARATIONS(Type, ParentType)\
	public:\
		static std::string TypeName() { return std::string(#Type); }\
		static IdType TypeIdClass() { return RunTimeTypeId; }\
		virtual IdType TypeIdInstance() const override { return Type::TypeIdClass(); }\
		virtual Common::SRTTI* QueryInterface(const IdType Id) override\
		{\
			return (Id == RunTimeTypeId ? reinterpret_cast<Common::SRTTI*>(this) : ParentType::QueryInterface(Id));\
		}\
		virtual bool Is(SRTTI::IdType Id) const override\
		{\
			return (Id == RunTimeTypeId ? true : ParentType::Is(Id));\
		}\
		virtual bool Is(const std::string& Name) const override\
		{\
			return (Name == TypeName() ? true : ParentType::Is(Name));\
		}\
	private:\
		static IdType RunTimeTypeId;


#define SRTTI_DEFINITIONS(Type)\
	SRTTI::IdType Type::RunTimeTypeId == reinterpret_cast<SRTTI::IdType>(&Type::RunTimeTypeId);
	



}