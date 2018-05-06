#pragma once

template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction(void) { return new SubType; }

template<class BaseClass, class IdType>
class GenericObjectFactory {
	typedef BaseClass* (*ObjectCreationFunction)(void);
	map<IdType, ObjectCreationFunction> m_CreateFunctions;

public:
	template <class SubClass>
	bool Register(IdType id) {
		auto findIt = m_CreateFunctions.find(id);
		if (findIt == m_CreateFunctions.end()) {
			m_CreateFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
			return true;
		}

		return false;
	}

	BaseClass* Create(IdType id) {
		auto findIt = m_CreateFunctions.find(id);
		if (findId != m_CreateFunctions.end()) {
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return NULL;
	}
};