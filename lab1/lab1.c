#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isValidIdentifier(char identifier[], int n)
{
	if ((!isalpha(identifier[0])) && identifier[0] != '_')
	{
		printf("%c \n", identifier[0]);
		return 0;
	};
	for (int i = 1; i < n; i++)
	{
		if (!(isalnum(identifier[i])) && identifier[i] != '_')
		{
			printf("%c \n", identifier[i]);
			return 0;
		};
	}
	if (identifier[n - 1] == '_')
	{
		return 0;
	}
	int hasNumber = 0;
	for (int i = 0; i < n; i++)
	{
		if (isdigit(identifier[i]))
		{
			hasNumber = 1;
			for (int j = i; j < n; j++)
			{
				if (!isdigit(identifier[j]))
				{
					return 0;
				}
			}
			break;
		}
	}
	if (isalpha(identifier[0]) && !isupper(identifier[0]))
	{
		return 0;
	}
	if (n < 3 && identifier[0] != '_')
	{
		return 0;
	}
	if (n == 1 && identifier[0] != '_')
	{
		return 0;
	}
	int hasA = 0;
	for (int i = 0; i < n; i++)
	{
		if (identifier[i] == 'a' || identifier[i] == 'A')
		{
			hasA = 1;
			break;
		}
	}
	if (!hasA)
	{
		return 0;
	}
	if (isReservedWord(identifier))
	{
		return 0;
	}
	return 1;
}

int isReservedWord(char identifier[])
{
	char reserved[][20] = {"int", "float", "double", "char", "void", "if", "else", "for", "while", "do", "switch", "case", "default", "break", "continue", "return", "struct", "union", "enum", "typedef", "const", "static", "extern", "auto", "register", "signed", "unsigned", "short", "long", "sizeof", "goto"};
	int count = 31;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(identifier, reserved[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	char identifier[n];
	scanf("%s", identifier);
	int len = strlen(identifier);
	int isValid = isValidIdentifier(identifier, len);
	if (isValid)
	{
		printf("%s is a valid indetifier\n", identifier);
	}
	else
	{
		printf("%s is not a valid identifier\n", identifier);
	}
}
