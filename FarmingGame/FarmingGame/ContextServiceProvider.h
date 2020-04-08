#pragma once

#include <memory>
#include <type_traits>
#include <unordered_map>

#include "ContextServiceInterface.h"

// ------------------------------------------------------------

class CContextServiceProvider
{
public:
	CContextServiceProvider() = default;

	template< typename TService, typename ... TArgs >
	void RegisterService(TArgs& ... InArgs)
	{
		Services[GetServiceUID<TService>()] = std::static_pointer_cast< IContextService >( std::make_shared< TService >(InArgs ...) );
	}

	template< typename TService >
	void UnregisterService()
	{
		Services.erase(GetServiceUID<TService>());
	}

	template< typename TService >
	TService* GetService()
	{
		if (ContainsService< TService >())
		{
			return reinterpret_cast<TService*>(Services.at(GetServiceUID<TService>()).get());
		}

		return nullptr;
	}

	template < typename TService >
	TService& GetServiceRequired()
	{
		// This should crash if the service doesn't exist
		return *GetService<TService>();
	}

private:

	template< typename TService >
	size_t GetServiceUID() const
	{
		return typeid(TService).hash_code();
	}

	template< typename TService >
	bool ContainsService() const
	{
		return Services.find(GetServiceUID<TService>()) != Services.end();
	}

	std::unordered_map< size_t, std::shared_ptr<IContextService>> Services;
};

// ------------------------------------------------------------