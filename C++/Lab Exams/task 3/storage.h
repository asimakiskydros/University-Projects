#ifndef storage_h
#define storage_h
template<class my_type>
class storage{
	private:
		my_type* arr;
		int length;
	public:
		storage(my_type input[],int len){
			length=len;
			arr=new my_type[length];
			for(int i=0;i<length;i++)
				arr[i]=input[i];
		}
		my_type &operator[](int index){
				return arr[index];
		}
};

#endif //storage_h