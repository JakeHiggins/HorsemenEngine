#pragma once

template <class Type>
shared_ptr<Type> MakeStrongPtr(weak_ptr <Type> pWeakPtr) {
	if (!pWeakPtr.expired()) {
		return shared_ptr<Type>(pWeakPtr);
	}
	else {
		return shared_ptr<Type>();
	}
};

template<class T>
const char* toCString(T val) {
	printf(std::to_string(val).c_str());
	return std::to_string(val).c_str();
};

template<class T>
string toString(T val)
{
	return std::to_string(val);
};