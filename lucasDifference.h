#pragma once
//gotta change name to lucas math because this is what it will become haha
#include <string>
using namespace std;

//These are difference functions which returns the absolute difference between two variables
int difference(int a, int b)
{
	int absoluteDifference;
	int displacement = a - b;
	if (displacement < 0)
	{
		absoluteDifference = displacement * -1
	}
	else
	{
		absoluteDifference = displacement;
	}
	return absoluteDifference; 
}

float difference(float a, float b)
{
	float absoluteDifference;
	float displacement = a - b;
	if (displacement < 0)
	{
		absoluteDifference = displacement * -1
	}
	else
	{
		absoluteDifference = displacement;
	}
	return absoluteDifference;
}

double difference(double a, double b)
{
	double absoluteDifference;
	double displacement = a - b;
	if (displacement < 0)
	{
		absoluteDifference = displacement * -1
	}
	else
	{
		absoluteDifference = displacement;
	}
	return absoluteDifference;
}

//These below tests whether the difference passes a test and returns the bool value, true for passed, false for fail
bool difference(int a, int b, string c, int d)
{
	int absoluteDifference = difference(a, b);
	bool flag; 
	switch (c)
	{
	case "==":
		if (absoluteDifference == d)
		{
			flag = true; 
		}
		else
		{
			flag = false
		}
		break;
	case "!=":
		if (absoluteDifference != d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<=":
		if (absoluteDifference <= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">=":
		if (absoluteDifference >= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<":
		if (absoluteDifference < d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">":
		if (absoluteDifference > d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;

	case default:
		flag = false; 
		break;
	}



	return flag;
}

bool difference(float a, float b, string c, float d)
{
	float absoluteDifference = difference(a, b);
	bool flag;
	switch (c)
	{
	case "==":
		if (absoluteDifference == d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "!=":
		if (absoluteDifference != d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<=":
		if (absoluteDifference <= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">=":
		if (absoluteDifference >= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<":
		if (absoluteDifference < d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">":
		if (absoluteDifference > d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;

	case default:
		flag = false;
		break;
	}



	return flag;
}

bool difference(double a, double b, string c, double d)
{
	float absoluteDifference = difference(a, b);
	bool flag;
	switch (c)
	{
	case "==":
		if (absoluteDifference == d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "!=":
		if (absoluteDifference != d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<=":
		if (absoluteDifference <= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">=":
		if (absoluteDifference >= d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case "<":
		if (absoluteDifference < d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;
	case ">":
		if (absoluteDifference > d)
		{
			flag = true;
		}
		else
		{
			flag = false
		}
		break;

	case default:
		flag = false;
		break;
	}



	return flag;
}