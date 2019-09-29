/* Richard Boyd
Memory Management
Takes in a decimal and displays it in a bunch of different ways
*/

#include<stdio.h>
#include<math.h>

//takes in a number and prints it in binary
void printBinary(int n)
{
	int binary[32];
	int i = 0;
	while (n > 0) {
		binary[i] = n % 2;
		n = n / 2;
		i++;
	}
	for (int j = i - 1; j >= 0; j--) {
		printf("%d", binary[j]);
    }
	printf("\n");
}

//takes in a number and prints it in hexadecimal
void printHex(int n)
{
	char hexDigit[100];
	int i = 0;
	while (n > 0) {
		int test = 0;
		test = n % 16;
		if (test < 10) {
			hexDigit[i] = test + 48;
			i++;
		}
		else {
			hexDigit[i] = test + 55;
			i++;
		}
		
		n = n / 16;
	}
	for (int j = i - 1; j >= 0; j--) {
		printf("%c", hexDigit[j]);
	}
	printf("\n");
}

int main(void)
{
	int input;
	printf("Enter a number between 0 and 4095, then hit enter: \n");
	scanf("%d", &input);
	printf("You entered: %d \n", input);
	printf("Here's that number in binary: ");
	printBinary(input);
	printf("Here's that number in hexadecimal: ");
	printHex(input);
	
	int leftShift = input << 16;
	printf("That number shifted 16 bits to the left is: %d \n", leftShift);
	printf("Here's that new number in binary: ");
	printBinary(leftShift);
	printf("Here's that new number in hexadecimal: ");
	printHex(leftShift);
	
	return 0;
}