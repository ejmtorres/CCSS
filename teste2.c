long int func(long int a, long int b)
{
	return a+b;
}

int main()
{
	long int a;
	long int b;
	int 	 f;

	a=1;
	b=2;
	f=func(a+1,b+2);
	return f;
}
