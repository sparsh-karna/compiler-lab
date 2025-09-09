#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 20

// Structures to store grammar
char production[MAX][MAX]; // Productions
char firstSets[MAX][MAX];  // FIRST sets
char followSets[MAX][MAX]; // FOLLOW sets
int n;                     // Number of productions

// Function prototypes
void computeFirst(char *result, char c);
void computeFollow(char *result, char c);
int isNonTerminal(char c);
void addToSet(char *set, char c);

// Utility: check if a symbol is already in the set
int contains(char *set, char c)
{
    for (int i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == c)
            return 1;
    }
    return 0;
}

// Add a symbol to a set if not already present
void addToSet(char *set, char c)
{
    if (!contains(set, c))
    {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Compute FIRST set of a non-terminal
void computeFirst(char *result, char c)
{
    // If terminal, add to FIRST
    if (!isNonTerminal(c))
    {
        addToSet(result, c);
        return;
    }

    // Scan productions for this non-terminal
    for (int i = 0; i < n; i++)
    {
        if (production[i][0] == c)
        {
            // If epsilon production
            if (production[i][2] == '#')
            {
                addToSet(result, '#');
            }
            else
            {
                int j = 2; // Start of RHS
                while (production[i][j] != '\0')
                {
                    char symbol = production[i][j];
                    char temp[MAX] = "";
                    computeFirst(temp, symbol);

                    // Add everything except epsilon
                    for (int k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            addToSet(result, temp[k]);
                    }

                    // If epsilon found, move to next symbol
                    if (contains(temp, '#'))
                    {
                        j++;
                        if (production[i][j] == '\0')
                        {
                            addToSet(result, '#');
                        }
                    }
                    else
                        break;
                }
            }
        }
    }
}

// Compute FOLLOW set of a non-terminal
void computeFollow(char *result, char c)
{
    // Rule 1: Add $ to FOLLOW(start symbol)
    if (production[0][0] == c)
        addToSet(result, '$');

    // Scan all productions
    for (int i = 0; i < n; i++)
    {
        for (int j = 2; production[i][j] != '\0'; j++)
        {
            if (production[i][j] == c)
            {
                char next = production[i][j + 1];

                // Case 1: Non-terminal is followed by something
                if (next != '\0')
                {
                    char temp[MAX] = "";
                    computeFirst(temp, next);

                    // Add FIRST(next) except epsilon
                    for (int k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            addToSet(result, temp[k]);
                    }

                    // If epsilon in FIRST(next), add FOLLOW(LHS)
                    if (contains(temp, '#'))
                    {
                        char tempFollow[MAX] = "";
                        computeFollow(tempFollow, production[i][0]);
                        for (int k = 0; tempFollow[k] != '\0'; k++)
                        {
                            addToSet(result, tempFollow[k]);
                        }
                    }
                }
                // Case 2: Non-terminal is at end → add FOLLOW(LHS)
                else
                {
                    if (c != production[i][0])
                    {
                        char tempFollow[MAX] = "";
                        computeFollow(tempFollow, production[i][0]);
                        for (int k = 0; tempFollow[k] != '\0'; k++)
                        {
                            addToSet(result, tempFollow[k]);
                        }
                    }
                }
            }
        }
    }
}

// Check if symbol is non-terminal
int isNonTerminal(char c)
{
    return isupper(c);
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", production[i]);
    }

    printf("\nFIRST and FOLLOW sets:\n");

    for (int i = 0; i < n; i++)
    {
        char nonTerminal = production[i][0];

        char first[MAX] = "";
        char follow[MAX] = "";

        computeFirst(first, nonTerminal);
        computeFollow(follow, nonTerminal);

        printf("FIRST(%c) = { ", nonTerminal);
        for (int j = 0; first[j] != '\0'; j++)
        {
            printf("%c ", first[j]);
        }
        printf("}\n");

        printf("FOLLOW(%c) = { ", nonTerminal);
        for (int j = 0; follow[j] != '\0'; j++)
        {
            printf("%c ", follow[j]);
        }
        printf("}\n\n");
    }

    return 0;
}
