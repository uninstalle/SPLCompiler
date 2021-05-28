#include <iostream>
#include <pthread.h>

int main()
{
	// test linux api
	pthread_t t;
	pthread_create(&t, nullptr, [](void* ptr)->void* {
		std::cout << "Hello!";
		return nullptr;
		}, nullptr);
	std::cout << "Hello World";
	
	getchar();
}