#pragma once

template <class Type>
shared_ptr<Type> MakeStrongPtr(weak_ptr <Type> pWeakPtr) {
	if (!pWeakPtr.expired()) {
		return shared_ptr<Type>(pWeakPtr);
	}
	else {
		return shared_ptr<Type>();
	}
}