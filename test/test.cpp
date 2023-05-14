#include <iostream>

class test {
	public:
	
		void constr(){
			std::cout << "yay";
		};
		
		void setNum(int num){
			m_number=num;
		}
		
		void printNum(){
			std::cout << m_number;
		}
		
	private:
		int m_number;
		
};


int main(){
	test testobj[10];
	for (int i =0; i<10; i++){
		testobj[i].setNum(i);
	}
	for (int i = 0; i<10; i++){
		testobj[i].printNum();
	}
	

	return 0;
}
