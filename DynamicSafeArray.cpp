#include<iostream>

using namespace std;

template<typename X>
class DSA;

template<typename X>
istream& operator >> (istream &,DSA<X> &);

template<typename X>
ostream& operator << (ostream &,DSA<X> &);

class IndexException:public exception
{
	public:
		
		virtual const char * what() const throw()
		{
			return "Index Out Of Bound";
		}
}IE;
class LowerIndexException: public IndexException
{
	public:
		
		virtual const char * what() const throw()
		{
			return "Lower Index Out Of Bound";
		}
}LIE;
class UpperIndexException: public IndexException
{
	public:
		
		virtual const char * what() const throw()
		{
			return "Upper Index Out Of Bound";
		}
}UIE;
template<typename X>
class DSA
{
	private:
		
		X *Data;
		int Size;
		int Current_index;
	
	public:	
		
		DSA();
		DSA(int Size);
		DSA(const DSA<X> &);
		~DSA();
		int get_Size()const;
		int get_Current_index()const;
		DSA<X>& operator =(const DSA<X> &);
		friend istream& operator >> <X> (istream &,DSA &);
		friend ostream& operator << <X> (ostream &,DSA &);
		const X& operator [](int index)const;
		X&  operator [](int index);
		void Resize();
		bool operator==(const DSA<X>&);
		bool operator!=(const DSA<X>&);
		int Binary_Search(X key,int l,int r);
				
};

template<typename X>
DSA<X>::DSA() 
{
	Data=0;
	Size=1;
	Current_index=0;
}

template<typename X>
DSA<X>::DSA(int size)
{
	Data=new X[size];
	this->Size=size;
	Current_index=0;	
}

template<typename X>
DSA<X>::DSA(const DSA<X> &Obj)
{
	Data=new X[Obj.Size];
	Size=Obj.Size;
	Current_index=0;
	memcpy(this->Data,Obj.Data,sizeof(X) * Size);
}

template<typename X>
DSA<X>& DSA<X>::operator =(const DSA<X> &Obj)
{
	if(this!=&Obj)
	{
		delete[] Data;
		Data=new X[Obj.Size];
		Size=Obj.Size;
		memcpy(this->Data,Obj.Data,sizeof(X) * Size);
		Current_index=0;	
	}
		return *(this);
	
}

template<typename X>
DSA<X>::~DSA()
{
	if(Data!=0)
	{
		delete[] Data;
		Data=0;
	}
}

template<typename X>
int DSA<X>::get_Size()const
{
	return Size;
}

template<typename X>
int DSA<X>::get_Current_index()const
{
	return Current_index;
}
template<typename X>
istream& operator >>(istream &input,DSA<X> &Obj)
{
	cout<<"Enter The Elements For The Array"<<endl;
	for(int i=0;i<Obj.Size;i++)
	{
		input >> Obj.Data[i];
	}
	return input;
}
template<typename X>
ostream& operator <<(ostream &output,DSA<X> &Obj)
{
	cout<<"Elements of The Array"<<endl;
	for(int i=0;i<Obj.Size;i++)
	{
		output << Obj.Data[i]<<endl;
	}
	return output;
}

template<typename X> 
X& DSA<X>::operator [](int index)
{
	if(index<0)
	{
		throw LIE; 
	}
	else if(index>=Size)
	{
		Resize();
		return Data[index];
	}
	else
	{
		return Data[index];
	}
		
}

template<typename X>
const X& DSA<X>::operator [](int index) const
{
	if(index<0)
	{
		throw LIE;
	}
	else if(index>Size)
	{
		throw UIE;
	}
	else
	{
		return Data[index];	
	}
}

template<typename X>
void DSA<X>::Resize()
{
	X *New_Data=new  X[Size];
	memcpy(New_Data,Data,sizeof(X)*Size);
	delete[] Data;
	Data=new X[Size+2];
	memcpy(Data,New_Data,sizeof(X)*Size);
	delete[] New_Data;
	Size+=2;	
}

template<typename X>
bool DSA<X>::operator==(const DSA<X> &Obj)
{
	if(this!=&Obj)
	{
		if(Size==Obj.Size)
		{
			for(int i=0;i<Size;i++)
			{
				if(Data[i]!=Obj.Data[i])
				{
					return false;	
				}	
			}
			
			return true;	
		}
		else
		{
			return false;	
		}	
	}
	return true;
}

template<typename X>
bool DSA<X>::operator!=(const DSA<X> &Obj)
{
	if(this!=&Obj)
	{
		if(Size!=Obj.Size)
		{
			for(int i=0;i<Size;i++)
			{
				if(Data[i]!=Obj.Data[i])
				{
					return true;	
				}	
			}
			return true;	
		}
		else
		{
			return false;	
		}	
	}
	return false;
		
}

