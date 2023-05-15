#include <iostream>
#include <cmath>

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
	/*test testobj[10];
	for (int i =0; i<10; i++){
		testobj[i].setNum(i);
	}
	for (int i = 0; i<10; i++){
		testobj[i].printNum();
	}
	*/

	std::cout << cos(3.14159) << "\n";
	std::cout << cos(3.14159*1.5) << "\n";
	std::cout << cos(3.14159*2) << "\n";
	std::cout << cos(3.14159*2.5) << "\n";

	return 0;
}
