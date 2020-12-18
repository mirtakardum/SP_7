#include<stdio.h>
#include<stdlib.h>

struct stog;
typedef struct stog* Pozicija;
typedef struct stog {
	int br;
	Pozicija next;
}_stack;

int ucitaj(char[20]);
Pozicija newElement();
void putIntoStack(Pozicija, Pozicija);
void calculate(Pozicija, char);
void printResult(Pozicija);

int main() {
	_stack head;
	head.next = NULL;
	int err = 0;
	err = ucitaj("postfix.txt", &head);
	if (!err)
		return -1;

	printResult(&head);
}

int ucitaj(char dat[20], Pozicija p) {
	FILE* ulz = fopen(dat, "r");
	if (ulz == NULL) {
		printf("Greska pri otvaranju datoteke");
		return -1;
	}

	int i = 0;
	char pom = ' ';
	while (!feof(ulz)) {
		fscanf(ulz, "%c", &pom);
		i++;
	}

	rewind(ulz);
	char* buffer = NULL;
	buffer = (char*)malloc(sizeof(char) * i);
	i = 0;

	while (!feof(ulz)) {
		fscanf(ulz, "%c", (buffer + i));
		i++;
	}
	fclose(ulz);

	int lenght = 0;
	int returnValue = 1;
	int read = 0;

	while (returnValue) {
		Pozicija q = newElement();
		if (q == NULL) {
			printf("Greska pri alokaciji");
			return -2;
		}
		char op = ' ';

		returnValue = sscanf(buffer + lenght, "%d%n", &q->br, &read);

		if (returnValue == 0) {
			returnValue = sscanf(buffer + lenght, " %c%n", &op, &read);
			calculate(p, op);
		}
		else
			putIntoStack(p, q);

		lenght += read;
	}

	return 1;
}
Pozicija newElement() {
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(Pozicija));

	return p;
}

void putIntoStack(Pozicija p, Pozicija q) {
	q->next = p->next;
	p->next = q;
}

void calculate(Pozicija p, char op) {
	Pozicija operand1 = NULL;
	Pozicija operand2 = NULL;

	if (p->next == NULL || p->next->next == NULL) {
		printf("Stog nije pravilno popunjen");
		return;
	}

	operand2 = p->next;
	operand1 = p->next->next;

	switch (op) {
	case '+':
		p->next->br = operand1->br + operand2->br;
		break;

	case '-':
		p->next->br = operand1->br - operand2->br;
		break;

	case '*':
		p->next->br = operand1->br * operand2->br;
		break;

	case '/':
		p->next->br = operand1->br / operand2->br;
		break;

	default:
		printf("Nepoznata operacija\n");
		break;
	}

	p->next = operand1->next;
	free(operand1);
}

void printResult(Pozicija p) {
	p = p->next;
	printf("Konacni rezultat je %d\n", p->br);
}