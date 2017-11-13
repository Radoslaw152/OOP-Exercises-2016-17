#include <iostream>
#include <queue>
#include <stack>
template<typename T>
bool AvailableElement(std::queue<T> myQueue,const T& key)
{
	while (!myQueue.empty())
	{
		if (myQueue.front() == key)
			return true;
		myQueue.pop();
	}
	return false;
}
template<typename T>
void ReverseQueue(std::queue<T>& myQueue)
{
	std::stack<T> tempStack;
	while (!myQueue.empty())
	{
		tempStack.push(myQueue.front());
		myQueue.pop();
	}
	while (!tempStack.empty())
	{
		myQueue.push(myQueue.top());
		tempStack.pop();
	}
}
template<typename T>
void ReverseStack(std::stack<T>& myStack)
{
	std::queue<T> tempQueue;
	while (!myStack.empty())
	{
		tempQueue.push(myStack.top());
		myStack.pop();
	}
	while (!tempQueue.empty())
	{
		myStack.push(myQueue.front());
		tempQueue.pop();
	}
}
template<typename T>
std::queue<T>& MakePriorityQueue(const std::queue<T>& firstQueue, const std::queue<T>& secondQueue)
{
	std::queue<T> newOne;
	while (!firstQueue.empty() || !secondQueue.empty())
	{
		if (!firstQueue.empty() && !secondQueue.empty() && firstQueue.front() < secondQueue.front())
		{
			newOne.push(secondQueue.front());
			secondQueue.pop();
		}
		else if (!firstQueue.empty() && !secondQueue.empty() && firstQueue.front() >= secondQueue.front())
		{
			newOne.push(firstQueue.front());
			firstQueue.pop();
		}
		else if (firstQueue.empty())
		{
			newOne.push(secondQueue.front());
			secondQueue.pop();
		}
		else
		{
			newOne.push(firstQueue.front());
			firstQueue.pop();
		}
	}
	return newOne;
}
template<typename T>
bool IsQueueSorted(std::queue<T> myQueue)
{
	T temp = myQueue.top();
	myQueue.pop();
	while (!myQueue.empty())
	{
		if (temp > myQueue.top())
		{
			return false;
		}
		temp = myQueue.top();
		myQueue.pop();
	}
	return true;
}
int test()
{

	return 0;
}