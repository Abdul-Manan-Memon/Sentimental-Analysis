#include<iostream>
#include<string>
#include<fstream>
using namespace std;
template<typename X>
class Node
{
	private:
		X Data;         			// Data In the Current Node
		float Polarity,Subjectivity;
		Node<X> *Next;				// Member Pointer, Part of Current Node, Contains Address of the Next Node
		 
		public:
			Node()
			{
				Data="NULL";
				Polarity=Subjectivity=0;
				Next=0;
			}
			Node(X data)
			{
				this->Data=data;
				this->Next=0;
			}
			Node(Node<X> *n)
			{
				this->Data=n->Data;
				this->Next=n->Next;
			}
			void Set_Data(X data)
			{
				this->Data=data;
			}
			void Set_Next(Node<X> *n)
			{
				this->Next=n->Next;
			}
			void Set_Polarity(float Polar)
			{
				Polarity=Polar;
			}
			void Set_Subjectivity(float Sub)
			{
				Subjectivity=Sub;
			}
			float get_Polarity() const
			{
				return Polarity;
			}
			
			X get_Data() const 
			{
				return Data;
			}
			Node<X>* get_Next()	const
			{
				return Next;				
			}
			template<typename s>
			friend class SinglyLinkedList;
};
template<typename X>
class SinglyLinkedList
{
	private:
		Node<X> *Head;			//PointerObject, Contains Data and Next, Points Towards The First Node 
		Node<X> *Tail;
		int Size;
		private:
		void Delete_All()
		{
			Node<X>*temp=Head;
			while(Head!=0)
			{
				Head=Head->Next;
				delete temp;
				temp=Head;
			}
			Size=0;
		}
		public:
			SinglyLinkedList()
			{
				Head=0;
				Tail=0;
				Size=0;
			}
			SinglyLinkedList(const SinglyLinkedList &Obj)
			{
				Node<X> *temp=Obj.Head;
				Head=0;
				Tail=0;
				Size=Obj.Size;
				if(Head==0)
				{	
					Head=new Node<X>;
					Head->Data=temp->Data;
					Head->Next=0;
					Tail=Head;
					temp=temp->Next;
				}
				while(temp!=0)
				{
					Tail->Next=new Node<X>;
					Tail=Tail->Next;
					Tail->Data=temp->Data;
					temp=temp->Next;		
				}
			}
			SinglyLinkedList& operator=(const SinglyLinkedList &Obj)
			{
				if(this!= &Obj)
				{
					Delete_All();
					Node<X> *temp=Obj.Head;
					Size=Obj.Size;
					Head=new Node<X>;
					Head->Data=temp->Data;
					Head->Next=0;
					Tail=Head;
					while(temp!=0)
					{
						Tail->Next=new Node<X>;
						Tail=Tail->Next;
						Tail->Data=temp->Data;
						temp=temp->Next;
					}
				}
				return *this;		
			}
			~SinglyLinkedList()
			{
				if(Head!=0)
				{
					Delete_All();	
				}				
			}
			Node<X>* get_Head() const
			{
				return Head;
			}
			Node<X>* get_Tail() const
			{
				return Head;
			}
			int get_Size()
			{
				return Size;
			}			
			void Add_Node_at_Last(X data)
			{
				if(Head==0)
				{
					Head=new Node<X>;
					Head->Data=data;
					Head->Next=0;
					Tail=Head;	
				}
				else
				{
					Tail->Next=new Node<X>;
					Tail=Tail->Next;
					Tail->Data=data;						
				}
				Size++;																		
			}
			void Add_at_First(X data)
			{
				if(Head==0)
				{
					Head=new Node<X>;
					Head->Data=data;
					Head->Next=0;
					Tail=Head;	
				}
				else
				{
					Node<X> *temp=new Node<X>;
					temp->Data=data;
					temp->Next=Head;
					Head=temp;
				}
				Size++;
			}
			void print_Nodes()
			{
				Node<X> *T=Head;
				while(T!=0)
				{
					X D=T->Data;
					cout<<D<<" ";
					T=T->Next;
				}
				cout<<endl;			
			}
			void Delete_a_Node(int index)
			{
				Node<X> *temp=Head,*prev=0;
				if(index==0)
				{
					Head=Head->Next;
					temp->Next=0;
					delete temp;
				}
				else if(index==Size-1)
				{
					while(temp!=Tail)
					{
						prev=temp;
						temp=temp->Next;
					}
					Tail=prev;
					Tail->Next=0;
					delete temp;		
				}
				else
				{
					while(index--)
					{
						prev=temp;
						temp=temp->Next;
					}
					prev->Next=temp->Next;
					temp->Next=0;
					delete temp;
				}
			}
			void Bubble_Sort()
			{
				bool swap=false;
				Node<X>*Store=0;
				int Element=0;
				while(Element<get_Size())
				{
					Node<X>*temp=Head;
					Node<X>*prev=Head;
					
					while(temp->Next!=0)
					{
						swap=false;
						if(temp==Head && temp->Data>temp->Next->Data)  
						{
							Store=temp->Next;         
							temp->Next=Store->Next; 
							Store->Next=temp;      
							Head=Store;
							prev=Head;
							swap=true;      		
						}
						else if(temp->Data>temp->Next->Data)
						{
							Store=temp->Next;  
							temp->Next=Store->Next;       
							Store->Next=temp;
							prev->Next=Store;
							prev=prev->Next;
							swap=true;   
	   
						}
						if(swap==false)
						{
							prev=temp;	
							temp=temp->Next;
						}
					}
					Element++;
				}
			}
			void Selection_Sort()
			{
				Node<X>*Current=Head;
				Node<X>*prev=0,*t_prev=Head;
				while(Current->Next!=0)
				{
					Node<X>*Min=Current;
					Node<X>*temp=Current;
					t_prev=Head;	
					while(temp!=0)
					{
						if(Min->Data>temp->Data) 
						{	
							Min=temp;					
						}
						temp=temp->Next;
					}
					while(t_prev->Next!=Min)
					{
						t_prev=t_prev->Next;	
					}
					if(Current!=t_prev)
					{
						if(Current==Head)
						{
							Node<X>*S_next=Min->Next;
							Min->Next=Current->Next;
							t_prev->Next=Current;
							Current->Next=S_next;
							Head=Min;
						}
						else
						{
							Node<X>*S_next=Min->Next;
							prev->Next=Min;
							Min->Next=Current->Next;
							t_prev->Next=Current;
							Current->Next=S_next;
						}
					}
					else
					{
						Node<X>*Temp=Min->Next;
						Current->Next=Temp;
						Min->Next=Current;
						prev->Next=Min;
					}
					prev=Min;
					Current=Min->Next;
				}
			}
			void Reverse()
			{
				Node<X>*Current=Head;    
				Node<X>*t_Next=NULL,*prev=NULL;  
				while(Current!=0)    
				{
					t_Next=Current->Next;           
					Current->Next=prev;  
					prev=Current;   
					Current=t_Next;  
				}
				Head=prev;
			}
			void Move_Node(SinglyLinkedList<int> &Obj)
			{
				Node<X>*temp=Obj.Head;
				Obj.Head=Obj.Head->Next;
				temp->Next=Head;
				Head=temp;
			}
			void Split_List()
			{
				SinglyLinkedList<int> Obj;
				int Count=0;
				Obj.Head=Head;
				Obj.Tail=Head;
				Head=Head->Next;
				while(Count<(Size/2-1))
				{
					Obj.Tail->Next=Head;
					Obj.Tail=Obj.Tail->Next;
					Head=Head->Next;
					Obj.Tail->Next=0;
					Count++;
				}
				print_Nodes();
				Obj.print_Nodes();		
			}
			void lower()
			{
				Node<X> *temp=Head;
				while(temp!=0)
				{
					if(temp->Data[0]>='A' && temp->Data[0]<='Z')
					{
						temp->Data[0]=temp->Data[0]+32;
					}
					temp=temp->Next;
				}
			}
			void stop_words()
			{
				string stop_word;
				ifstream file;
				Node<X> *temp=Head;
				int Count=0;
				bool check;
				string name="Stop Words.txt";
				while(temp!=0)
				{
					file.open("Stop Words.txt",ios::in);
					if(!file.is_open())
					{
						cout<<"Can Not Open File";
						exit(0);
					}
					while(getline(file,stop_word))
					{
						check=false;
						if(temp->Data==stop_word)
						{
							check=true;
							if(Count==0)
							{
								Head=Head->Next;
								temp->Next=0;
								delete temp;
								temp=Head;
								file.close();
								file.open("Stop Words.txt",ios::in);
							}
							else if(Count==Size-1)
							{
								Node<X> *prev=Head;
								while(prev->Next!=temp)
								{
									prev=prev->Next;
								}
								Tail=prev;
								Tail->Next=0;
								delete temp;
								temp=0;
								file.close();
								file.open("Stop Words.txt",ios::in);
							}
							else
							{
								int count1=Count-1;
								Node<X> *prev=Head;
								while(count1--)
								{
									prev=prev->Next;
								}
								prev->Next=temp->Next;
								temp->Next=0;
								delete temp;
								temp=prev->Next;
								file.close();
								file.open("Stop Words.txt",ios::in);
							}
						}
						
					}
					if(check==false)
					{
						temp=temp->Next;	
					}
					Count++;
					file.close();
				}
		}
			
};
