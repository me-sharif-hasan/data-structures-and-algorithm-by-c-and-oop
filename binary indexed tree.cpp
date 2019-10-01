/*
Sharif Hasan - CSE, PUST
Oct 01,2019 09:32 PM
*/
#include<bits/stdc++.h>
#define br cout<<"\n"
#define FOR(i,n) for(i=0;i<n;i++)
#define FROM(a,i,n) for(i=a;i<n;i++)
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;
class BIT
{
    public:
    BIT(int arr[],int size)
    {
        int i;
        this->size = size;
        this->TREE = new int[this->size+1];   
        for(i=0;i<this->size+1;i++) this->TREE[i]=0;
        for(i=0;i<this->size;i++)
        {
            update(i,arr[i]);
        }
    }
    void update(int index,int value)
    {
        ++index;
        while(index<this->size)
        {
            this->TREE[index] += value;
            index += index&(-index);
        }
    }
    int getSum(int index)
    {
        ++index;
        int sum=0;
        while(index>0)
        {
            sum+=this->TREE[index];
            index-=index&(-index);
        }
        return sum;
    }
    int getSumInRange(int l,int r)
    {
        return this->getSum(r)-this->getSum(l-1);
    }
    int currentKeyState(int key)
    {
        return this->getSumInRange(key,key);
    }
    void printTREE()
    {
        for(int i=0;i<=this->size;i++) cout<<this->TREE[i]<<" ";
    }
    
    private:
    int *TREE=NULL;
    int size=0;
};
/*Main function*/
int main()
{
/* 0 based indexing used in examples*/
int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
BIT bit(arr,12);
cout<<"The current key state of key 8 was "<<bit.currentKeyState(8)<<endl;
cout<<"Sum of elements from index 3 to 10 was "<<bit.getSumInRange(3,10)<<endl;
cout<<"Sum of elements from index 0 to 10 was "<<bit.getSum(10)<<endl;
cout<<"\tThe previous tree was \n";
bit.printTREE();
cout<<endl<<endl;

cout<<"Now we update at position 9 (index 8)"<<endl<<endl;

bit.update(8,91);
cout<<"The current key state of key 8 is "<<bit.currentKeyState(8)<<endl;
cout<<"Sum of elements from index 3 to 10 is "<<bit.getSumInRange(3,10)<<endl;
cout<<"Sum of elements from index 0 to 10 is "<<bit.getSum(10)<<endl;
cout<<"\tThe current tree is \n";
bit.printTREE();

return 0;
}


/*


The current key state of key 8 was 9
Sum of elements from index 3 to 10 was 60
Sum of elements from index 0 to 10 was 66
	The previous tree was
0 1 3 3 10 5 11 7 36 9 19 11 0

Now we update at position 9 (index 8)

The current key state of key 8 is 100
Sum of elements from index 3 to 10 is 151
Sum of elements from index 0 to 10 is 157
	The current tree is
0 1 3 3 10 5 11 7 36 100 110 11 0



*/
