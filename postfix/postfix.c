#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s){
	s->top = -1;
}

int is_empty(StackType* s){
	return (s->top == -1);
}

int is_full(StackType* s){
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item){
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

element pop(StackType* s){
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType* s){
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}




int prec(char op){				//연산자 우선순위
	switch (op)
	{
	case '(': case')': return 0;
	case '+': case'-': return 1;
	case '*': case'/': return 2;
	}
	return -1;
}

char* infix_to_postfix(char exp[]){				//후위변환함수

	static char str[2 * MAX_STACK_SIZE];
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	int j = 0;

	init_stack(&s);
	for (int i = 0; i < len; i++){
		ch = exp[i];
		switch (ch){
		case '+': case '-': case '*': case'/':
			str[j] = ' ';
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				j++;
				str[j] = (char)pop(&s);
			}
			push(&s, ch);
			break;
		case '(':
			str[j] = ' ';
			push(&s, ch);
			break;
		case ')':
			str[j] = ' ';
			top_op = pop(&s);
			while (top_op != '('){
				j++;
				str[j] = top_op;
				top_op = pop(&s);
				
			}
			break;
		default:
            if(isdigit(ch)){
                str[j] = ch;
            }else
                 str[j] = ' '; 
			break;
		}
		j++;
    }
	while (!is_empty(&s)) {
		str[j] = pop(&s);
		j++;
	}
	return str;
}

float eval(char exp[])
{
	int op1, op2, value;
	int len = strlen(exp);
	char ch;
	char str[2 * MAX_STACK_SIZE] = "";
	StackType s;
	init_stack(&s);
	for (int i = 0; i < len; i++)
	{
        value = 0;
		ch = exp[i];
		if (isdigit(ch)){       
            for(;;){
                value = value * 10 + (ch - '0');
                i++;          // check next char
                ch = exp[i];
			    if (! isdigit(ch)) {
                    push(&s, value);
                    i--;
                    break;
                }
            }
		}
        else if(ch == ' ')
            continue;
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int main(void)
{
	int result;
	char * postfix, * s = (char*)malloc(2*MAX_STACK_SIZE);
    printf("Enter Infix Expression>> ");
    fgets(s, 2*MAX_STACK_SIZE, stdin);
    printf("Postfix Expression: ");
    postfix = infix_to_postfix(s);
    printf("%s\n", postfix);
    result = eval(postfix);
    printf("Evaluation Result: %d\n", result);
    free(s);
	return 0;
}