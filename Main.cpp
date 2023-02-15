#include <sstream>

#include "DynamicSafeArray.cpp"

#include "Singly_Linked_List Final.cpp"

#define MAX_SIZE 100

using namespace std;

struct node
{
	char Word[MAX_SIZE] = {};
	float Polarity = 0;
	float Subjectivity = 0;
} Temp;

DSA<node> Polar_Words(5);

void Create_Polar_Dictionary()
{
	int j = 0;
	string Text, File_Name = "vader_lexicon.txt";
	ifstream R_File;
	R_File.open(File_Name, ios::in);
	while (!R_File.eof())
	{
		int i = 0;
		node Obj;
		getline(R_File, Text);
		while (Text[i] != '\t')
		{
			Obj.Word[i] = Text[i];
			i++;
		}
		stringstream str_to_int_Pol(Text.substr(i, i + 5));
		str_to_int_Pol >> Obj.Polarity;
		stringstream str_to_int_Subj(Text.substr(i + 5, i + 10));
		str_to_int_Subj >> Obj.Subjectivity;
		Polar_Words[j] = Obj;
		node Obj1 = Polar_Words[j];
		//		cout<<Obj1.Word<<"		"<<Obj1.Polarity<<"		"<<Obj1.Subjectivity<<endl;
		j++;
	}

	R_File.close();
}
void Display(float pos, float neg, float neu, float Comp)
{
	string status;
	if (Comp > 0)
		status = "Positive";
	else
		status = "Negative";
	cout << endl
		 << "------------------------------------------------------------------" << endl;
	cout << "| Pos: " << pos << " "
		 << "Neg: " << neg << " "
		 << "Neu: " << neu << " "
		 << "Compound: " << Comp << " Status: " << status << "|";
	cout << endl
		 << "------------------------------------------------------------------" << endl;
	getch();
}
int linear_Search(node Obj, string key, int i)
{
	for (; Obj.Word[0] <= key[0];)
	{
		Obj = Polar_Words[++i];
		if (Obj.Word == key)
			return i;
	}
	return -1;
}
int Jump(node Obj, string key, int l, int r)
{
	Obj = Polar_Words[l];
	for (int i = 0; i < 2; i++)
	{
		while (Obj.Word[i] < key[i])
		{
			l = l + 10;
			Obj = Polar_Words[l];
		}
	}
	if (l - 10 < 0)
	{
		l = 0;
		Obj = Polar_Words[l];
		return linear_Search(Obj, key, l);
	}
	else
	{
		Obj = Polar_Words[l - 10];
		return linear_Search(Obj, key, l - 10);
	}
}
node Binary_Search(string key, int l, int r)
{
	while (l <= r)
	{
		int mid = (l + r) / 2;
		Temp = Polar_Words[mid];
		if (Temp.Word == key)
			return Temp;
		else if (Temp.Word[0] == key[0])
		{
			int i = Jump(Temp, key, l, mid);
			if (i >= 0)
				Temp = Polar_Words[i];
			else
			{
				Temp.Word[0] = ' ';
				Temp.Polarity = 0;
				Temp.Subjectivity = -10;
			}
			return Temp;
		}
		else if (Temp.Word[0] > key[0])
			r = mid - 1;
		else
			l = mid + 1;
	}
}
int Cal_Positive_and_Negative_Words(SinglyLinkedList<string> &Obj)
{
	int neg = 0, pos = 0;
	float pos_pol = 0, neg_pol = 0, Compound = 0, neu = 0;
	;
	Node<string> *temp = Obj.get_Head();
	while (temp != 0)
	{
		node Word = Binary_Search(temp->get_Data(), 0, Polar_Words.get_Size() - 1);
		if (Word.Polarity > 0)
		{
			pos++;
			pos_pol += Word.Polarity;
		}
		else if (Word.Polarity != 0)
		{
			neg++;
			neg_pol += Word.Polarity;
		}

		else
			neu++;

		temp = temp->get_Next();
	}
	pos_pol /= (pos + neg + neu);
	neg_pol /= (pos + neg + neu);
	neu /= (pos + neg + neu);
	Compound = pos_pol + neg_pol + neu;
	Display(pos_pol, neg_pol, neu, Compound);
	//	cout<<pos<<" "<<neg<<" "<<neu<<endl;
}
void Tokenization_and_StopWords()
{
	string S;
	ifstream File;
	File.open("read_data1.txt", ios::in);
	if (!File.is_open())
	{
		cout << "Can Not Open File" << endl;
		exit(0);
	}
	else
	{
		char Arr[MAX_SIZE] = {};
		while (getline(File, S))
		{
			int i = 0, j = -1;
			SinglyLinkedList<string> L1;
			while (S[i] != '\0')
			{
				if (S[i] != ' ' && isalpha(S[i]))
				{
					Arr[++j] = S[i];
				}
				else if (j != -1)
				{
					string D(Arr);
					L1.Add_Node_at_Last(D);
					for (; j > -1; j--)
					{
						Arr[j] = {};
					}
				}
				i++;
			}
			L1.lower();
			L1.print_Nodes();
			L1.stop_words();
			Cal_Positive_and_Negative_Words(L1);
		}
	}
}
int main(void)
{
	Create_Polar_Dictionary();
	Tokenization_and_StopWords();
}
