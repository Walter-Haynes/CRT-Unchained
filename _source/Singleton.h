#pragma once

template <typename T>
///<summary> Manager class based on: https://gist.github.com/daniebker/2299755 </summary>
class Singleton
{
public:
	static T* Instance();

private:
	Singleton(Singleton const&);

protected:
	static T* instance_;

	Singleton()
	{
		instance_ = static_cast<T*>(this);
	}

	~Singleton()
	{
		delete instance_;
		instance_ = nullptr;
	}
};

template <typename T>
T* Singleton<T>::instance_ = nullptr;

template <typename T>
T* Singleton<T>::Instance()
{
	if (instance_ != nullptr) return instance_;

	return instance_ = new T();
}
