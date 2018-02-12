/*this program converts minterm's or maxterm's into ligical form*/ 
#include<iostream>

using namespace std;

typedef class node
{
	public:
	int a[9];
	node *next;
}node;


class convert
{
	public:
	int minterm[15],maxterm[15];
	node *head,*head1,*curr,*curr1,*temp,*h[5],*ans,*EPI;
	int min,max,input;
	int cnt0,cnt,cnt1;
	int M[15];
	convert()
	{
		head1=NULL;
		h[0]=NULL;
		h[1]=NULL;
		h[2]=NULL;
		h[3]=NULL;
		h[4]=NULL;
		h[5]=NULL;
		ans=NULL;
		EPI=NULL;
		cnt=0;
		cnt0=0;
		cnt1=0;
		head=new node;	
		min=0;
	}
	void accept(); // for accepting the minterm or maxterm
	void maxtomin(); // converts maxterm's into minterm's
	void sort(int,int); //sorts the array of minterm's
	void binary(int); //convert's sorted array of minterm's into binery number
	void fillnode(); //it stores binery number into link list
	void compare(int); //compares every list 
	void makenull(int);
	void fillans(node *);
	void fillansarr(node *);
	void checkans();
	void checkdecimal();
	void finalans(node *);// stores the final array of answer
	void fillEPI();
	void display();
	void displaynode(node *);
	void displaydecimal(node *);
};

void convert :: accept()
{
	int ch,i,flag=0,flag1=0;
//	cout<<"\n Enter total No. of input = ";
//	cin>>input;
	input = 4;
	do
	{
		flag=0;
		cout<<"\n\t 1 : Minterm's";
		cout<<"\n\t 2 : Maxterm's";
		cout<<"\n\nEnter your Choice = ";
		cin>>ch;
		switch(ch)
		{
		case 1:	cout<<"\nEnter Total Number of Minterm's = ";
				cin>>min;
				cout<<"\nEnter Minterms\n";
				for(i=1;i<=min;i++)
				{
					cout<<"\n\tNo."<<i<<" : ";
					cin>>minterm[i];
					binary(minterm[i]);	
				}
				flag1=1;
				//sort(min,flag1);
				break;
		
		case 2:cout<<"\nEnter Total Number of Maxterm's = ";
				cin>>max;
				cout<<"\nEnter Maxterms\n";
				for(i=0;i<max;i++)
				{
					cout<<"\n\tNo."<<i<<" :";
					cin>>maxterm[i];	
				}
				//sort(max,flag1);
				maxtomin();
				break;
		
		default:cout<<"****PLZ enter valid choice****";
				flag=1;
				break;		
		}
	}while(flag==1);
}

void convert :: maxtomin()
{
	int i,j,q=1,flag=0;
	for(i=1;i<=input;i++)
	{
		q=q*2;
	}
	for(i=0;i<q;i++)
	{
		flag=0;
		for(j=0;j<max;j++)
		{
			if(maxterm[j]==i)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
			{
				minterm[min]=i;
				binary(minterm[min]);
				if(minterm[min]<15)
					min++;
			}
	}
}

void convert :: sort(int term,int flag1)
{
	int i,j,temp;
	for(i=1;i<=term;i++)
	{
		for(j=1;j<=term;j++)
		{
			if(flag1==1&&minterm[i]<minterm[j])
			{
				temp=minterm[j];
				minterm[j]=minterm[i];
				minterm[i]=temp;			
			}
			if(flag1==0&&maxterm[i]<maxterm[j])
			{
				temp=maxterm[j];
				maxterm[j]=maxterm[i];
				maxterm[i]=temp;
			}
		}
	}
}

void convert :: binary(int num)
{
	int rem=0,i=3,j=0;
	if(cnt0==0)
	{
		head->a[4]=num;
		head->a[5]=16;
		while(num!=0)
		{
			rem=num%2;
			num=num/2;
			head->a[i]=rem;
			i--;
		}
		
		while(j<4)
		{
			if(head->a[j]!=1)
				head->a[j]=0;
			j++;
		}
		head->next=NULL;
		cnt0=1;
	}
	
	else
	{
		curr=head;
		while(curr->next!=NULL)
		{
			curr=curr->next;
		}
		curr->next=new node;
		curr=curr->next;
		
		curr->a[4]=num;
		curr->a[5]=16;
		
		while(num!=0)
		{
			rem=num%2;
			num=num/2;
			curr->a[i]=rem;
			i--;
		}
		
		while(j<4)
		{
			if(curr->a[j]!=1)
				curr->a[j]=0;
			j++;
		}
		curr->next=NULL;
	}
}

void convert :: fillnode()
{
	node *temp;
	int i;
	curr=head;
	while(curr!=NULL)
	{
		cnt=0;
		for(i=0;i<4;i++)
		{
			if(curr->a[i]==1)
				cnt++;
		}
		
		if(h[cnt]==NULL)
		{
			h[cnt]=new node;
			for(i=0;i<6;i++)
			{
				h[cnt]->a[i]=curr->a[i];
			}
			h[cnt]->next=NULL;
		}
		
		else
		{
			temp=h[cnt];
			
			while(temp->next!=NULL)
			{
			temp=temp->next;	
			}
			
			temp->next=new node;
			temp=temp->next;
			
			for(i=0;i<6;i++)
			{
				temp->a[i]=curr->a[i];
			}
			temp->next=NULL;
		}
		
		curr=curr->next;
	}
}

void convert :: compare(int q)
{
	int i,j,cnt1=0,cnt2,flag,flag1,flag2;
	
	while(cnt1<q)
	{
		flag=0;
		flag1=0;
		curr=h[cnt1];
		while(curr!=NULL)
		{
			curr1=h[cnt1+1];
			flag2=0;
			while(curr1!=NULL)
			{
				cnt2=0;
				for(i=0;i<4;i++)
				{
					if(curr->a[i]==curr1->a[i])
						cnt2++;
				}
				if(cnt2==3)
				{
					if(flag==0)
					{
						head1=new node;
						for(i=0;i<4;i++)
						{	
							if(curr->a[i]==curr1->a[i])
								head1->a[i]=curr->a[i];
							else
								head1->a[i]=2;
						}
						i=4;
						while(curr->a[i]!=16)
						{
							head1->a[i]=curr->a[i];
							head1->a[i+1]=16;
							i++;	
						}
						
						i=4;
						while(curr1->a[i]!=16)
						{
							j=4;
							while(head1->a[j]!=16)
							{
								j++;
							}
							head1->a[j]=curr1->a[i];
							head1->a[j+1]=16;
							i++;
						}
						
						head1->next=NULL;
						flag=1;
					}
					else
					{
						temp=head1;
						while(temp->next!=NULL)
						{
							temp=temp->next;
						}
						temp->next=new node;
						temp=temp->next;
						
						for(i=0;i<4;i++)
						{	
							if(curr->a[i]==curr1->a[i])
								temp->a[i]=curr->a[i];
							else
								temp->a[i]=2;
						}
						
						i=4;
						while(curr->a[i]!=16)
						{
							temp->a[i]=curr->a[i];
							temp->a[i+1]=16;
							i++;	
						}
						i=4;
						while(curr1->a[i]!=16)
						{
							j=4;
							while(temp->a[j]!=16)
							{
								j++;
							}
							temp->a[j]=curr1->a[i];
							temp->a[j+1]=16;
							i++;
						}
						
						temp->next=NULL;
					}
					flag1=1;
					flag2=1;
				}
				curr1=curr1->next;
			}
			if(flag2==0)
			{
				fillans(curr);
			}
			curr=curr->next;
		}
		if(flag1==1)
		h[cnt1]=head1;
		cnt1++;
	}	
}

void convert :: makenull(int n)
{
	int i,j,c;
	for(i=0;i<4;i++)
	{
		c=0;
		for(j=0;j<4;j++)
		{
			if(h[i]!=NULL)
				if(h[i]->a[j]==2)
					c++;
		}
		if(c==n)
		{
			h[i]=NULL;
		}
	}
}

void convert :: display()
{
	int i;
	cout<<"\nMinterm's are = {  ";
	for(i=1;i<=min;i++)
	{
		cout<<minterm[i];
		if(i!=min)
			cout<<"  ,  ";
	}
	cout<<"  }\n";
}

void convert :: displaynode(node *curr)
{
	int i;
	while(curr!=NULL)
	{
		cout<<"\t";
		for(i=0;i<4;i++)
		{
			cout<<" "<<curr->a[i];
		}
		curr=curr->next;
	}
}

void convert :: fillans (node *curr)
{
	int i;
	node *temp;
	if(ans==NULL)
	{
		ans=new node;
		for(i=0;i<4;i++)
		{
			ans->a[i]=curr->a[i];
		}
		i=4;
		while(curr->a[i]!=16)
		{
			ans->a[i]=curr->a[i];
			ans->a[i+1]=16;
			i++;
		}
		ans->next=NULL;
	}
	else
	{
		temp=ans;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=new node;
		temp=temp->next;
		for(i=0;i<4;i++)
		{
			temp->a[i]=curr->a[i];
		}
		i=4;
		while(curr->a[i]!=16)
		{
			temp->a[i]=curr->a[i];
			temp->a[i+1]=16;
			i++;
		}
		temp->next=NULL;
	}
	
}

void convert :: fillansarr(node *curr)
{
	int i;
	node *temp;

	while(curr!=NULL)
	{
		if(ans==NULL)
		{
			ans=new node;
			for(i=0;i<4;i++)
			{
				ans->a[i]=curr->a[i];
			}
			i=4;
			while(curr->a[i]!=16)
			{
				ans->a[i]=curr->a[i];
				ans->a[i+1]=16;
				i++;
			}
			ans->next=NULL;
		}
		else
		{
			temp=ans;
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=new node;
			temp=temp->next;
			for(i=0;i<4;i++)
			{
				temp->a[i]=curr->a[i];
			}
			i=4;
			while(curr->a[i]!=16)
			{
				temp->a[i]=curr->a[i];
				temp->a[i+1]=16;
				i++;
			}
			temp->next=NULL;
		}
		curr=curr->next;
	}
}

void convert :: checkans()
{
	int i,cnt;
	node *temp1;
	curr=ans;
	temp1=ans;
	while(curr!=NULL)
	{
		/*if(curr!=ans)
		{
			while(temp1->next!=curr)
			{
				temp1=temp1->next;
			}
		}*/
		temp=curr->next;
		while(temp!=NULL)
		{
			cnt=0;
			for(i=0;i<4;i++)
			{
				if(curr->a[i]==temp->a[i])
					cnt++;
			}
			if(cnt==3||cnt==4)
			{
				//cout<<"\ncnt"<<cnt;
				if(curr==ans)
				{
					ans=ans->next;
					curr=ans;
				}
				else
				{
					while(temp1->next!=curr)
					{
						temp1=temp1->next;
					}
					temp1->next=curr->next;
					curr->next=NULL;
					delete(curr);
					curr=temp1->next;
				}
			}	
			temp=temp->next;
		}
		curr=curr->next;
	}
}

void convert :: checkdecimal()
{
	int i,j;
	for(i=0;i<16;i++)
	{
		M[i]=0;
	}
	curr=ans;
		while(curr!=NULL)
		{
			i=4;
			while(curr->a[i]!=16)
				{
					j=curr->a[i];	
					M[j]=M[j]+1;
					i++;
				}	
			curr=curr->next;
		}
	/*for(i=0;i<16;i++)
	{
		cout<<"\nM["<<i<<"] = "<<M[i];
	}*/	
}

void convert :: finalans(node *curr)
{
	char c;
	int i;
	while(curr!=NULL)
	{
		for(i=0;i<4;i++)
		{
			if(i==0)
				c='A';
			else if(i==1)
				c='B';
			else if(i==2)
				c='C';
			else if(i==3)
				c='D';		
			if(curr->a[i]==0)
			{
				cout<<c<<"^";
			}
			if(curr->a[i]==1)
			{
				cout<<c;
			}
		}
		if(curr->next!=NULL)
			cout<<" + ";
		curr=curr->next;
	}
}

void convert :: fillEPI()
{
	int i,j;
	curr=ans;
	while(curr!=NULL)
	{
		i=4;
		while(curr->a[i]!=16)
		{
			if(M[curr->a[i]]==1)
			{
				if(EPI==NULL)
				{
					j=0;
					EPI=new node;
					while(curr->a[j]!=16)
					{
						EPI->a[j]=curr->a[j];
						j++;
					}
					EPI->next=NULL;
				}
				else
				{
					temp=EPI;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=new node;
					temp=temp->next;
					j=0;
					while(curr->a[j]!=16)
					{
						temp->a[j]=curr->a[j];
						j++;
					}
					temp->next=NULL;
				}
				break;
			}
			i++;
		}
		curr=curr->next;
	}
}

void convert :: displaydecimal(node *curr)
{
	int i;
	while(curr!=NULL)
	{
		cout<<"\t";
		for(i=0;i<4;i++)
		{
			cout<<" "<<curr->a[i];
		}
		i=4;
		cout<<" = ";
		while(curr->a[i]!=16)
		{
			cout<<" "<<curr->a[i];
			i++;
		}
		curr=curr->next;
	}
}

int main()
{
	cout<<"---------------THIS PROGRAM CONVERTS MINTERM'S/MAXTERM'S INTO LOGICAL FORM--------------\n";
	cout<<"\n\n** NOTE --this program works for only 4 inputs that means ABCD or PQRS";
	int i,j,q,cnt=0,p=0,r=2;
	convert ob1;
	ob1.accept();
//	ob1.display();
//	cout<<"\nMinterm's in binary =";
//	ob1.displaydecimal(ob1.head);
//	ob1.displaynode(ob1.head);
	ob1.fillnode();
//	cout<<"\n\n\t\tSTEP 1\n";
/*	for(i=0;i<5;i++)
	{
		cout<<"\nh ["<<i<<"] = ";
		ob1.displaydecimal(ob1.h[i]);
	}*/

	for(i=0;i<=4;i++)
	{
		if(ob1.h[i+1]==NULL)
			ob1.fillansarr(ob1.h[i]);
	}
	
	q=ob1.input;
	while(cnt!=4)
	{
		cnt=0;
		for(i=0;i<=3;i++)
		{
			if(ob1.h[i]==NULL)
				cnt++;
		}
		if(cnt!=4)
		{
//			cout<<"\n\n\t\tSTEP "<<r<<"\n";
			ob1.compare(q);
			ob1.makenull(p);
			ob1.fillansarr(ob1.h[q-1]);
		
/*			for(i=0;i<4;i++)
			{
				cout<<"\nh ["<<i<<"] = ";
				ob1.displaydecimal(ob1.h[i]);
			}
*/			q--;
			p++;
			r++;
		}
	}
	
	ob1.checkans();
	ob1.checkans();
	
//	cout<<"\n\nDisplaying answer";
//	ob1.displaydecimal(ob1.ans);
	
	ob1.checkdecimal();
	
//	cout<<"\n\n***Displaying Final Answer = ";
//	ob1.finalans(ob1.ans);
	cout<<"\n\n";

	cout<<"\n*** Final Answer = ";
	ob1.fillEPI();
	ob1.finalans(ob1.EPI);
	cout<<"\n\n";
	return 0;
 }
