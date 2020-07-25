#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class IndexTree
{
public:
	string word;
	int repetition;
	int* lines;
	IndexTree* left;
	IndexTree* right;
};

IndexTree* create_node(string iword, int line)
{
	IndexTree* node = new IndexTree;
	node->word = iword;
	node->right = NULL;
	node->left = NULL;
	node->repetition = 1;
	node->lines = new int;
	node->lines[0] = line;
	return node;
}
int compare(string str1, string str2)
{
	char c1 = tolower(str1[0]);
	char c2 = tolower(str2[0]);
	int i = 0;
	while (c1 != '\0' || c2 != '\0')
	{
		c1 = tolower(str1[i]);
		c2 = tolower(str2[i]);
		if (c1 < c2 || (c1 == '\0' && c2 != '\0'))
		{
			return -1;
		}
		else if (c1 > c2 || (c2 == '\0' && c1 != '\0'))
		{
			return 1;
		}
		else if (c1 == c2)
		{
			i++;
		}
	}
	return 0;

}
void insert_node(IndexTree** root, string iword, int line)
{
	IndexTree* Root = *root;

	if (Root != NULL)
{
		if (compare(iword,Root->word) < 0)
		{
			insert_node(&Root->left, iword, line);
		}
		else if (compare(iword,Root->word) == 0)
		{
			Root->repetition++;
			if (Root->lines[Root->repetition - 2] != line)
			{
				Root->lines = (int*)realloc(Root->lines, Root->repetition * sizeof(int));
				Root->lines[Root->repetition - 1] = line;
			}
		}
		else if (compare(iword,Root->word) > 0)
		{
			insert_node(&Root->right, iword, line);
		}
	}
	else if (Root == NULL)
	{
		IndexTree* node = new IndexTree;
		node = create_node(iword, line);
		*root = node;
	}
}


char* readFile(FILE* file)
{

	char* code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return NULL;

	code = (char*)malloc(n + 1);

	while (1 == 1)
	{
		if ((c = fgetc(file)) != EOF)
		{
			code[n++] = (char)c;
			code = (char*)realloc(code, n + 1);
		}
		else if ((c = fgetc(file)) == EOF)
		{
			break;
		}

	}

	code[n] = '\0';

	return code;
}
string readline(int line_number, string str)
{
	int line_n = 1;
	char* line = (char*)malloc(1);
	int i = 0;
	char c = str[0];
	while (line_n != line_number)
	{
		if (c == '\n')
		{

			line_n++;
		}
		i++;
		c = str[i];

	}
	int j = 0;
	while (c != '\n')
	{
		line[j] = c;
		j++;
		line = (char*)realloc(line, (j + 1) * sizeof(char));
		i++;
		if (c == '\0')
		{
			break;
		}
		c = str[i];
	}
	line[j] = '\0';
	return (string)line;
}

int line_count(string str)
{
	int i = 0;
	int line = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			line += 1;
		}
		i++;
	}
	return line;
}

char** split(string input)
{
	char** list;
	list = (char**)malloc(sizeof(char*));
	list[0] = (char*)malloc(1 * sizeof(char));
	int i = 0;
	int j = 0;
	int k = 0;
	while (1 == 1)
	{

		while (1 == 1)
		{
			if (input[k] == ' ')
			{
				k += 1;
				if (input[k] == '\0')
				{

					break;
				}
			}
			list[i][j] = input[k];
			k += 1;
			if (input[k] == '\0')
			{
				break;
			}


			if (input[k] == ' ')
			{
				j += 1;
				list[i] = (char*)realloc(list[i], (j + 1) * sizeof(char));

				break;
			}
			j += 1;
			list[i] = (char*)realloc(list[i], (j + 1) * sizeof(char));
		}
		if (input[k] == '\0')
		{
			j += 1;
			list[i][j] = 0;
			i += 1;
			list = (char**)realloc(list, (i + 1) * sizeof(char*));
			list[i] = (char*)malloc(sizeof(char));
			list[i][0] = 0;


			break;
		}
		list[i][j] = 0;
		i += 1;
		j = 0;
		list = (char**)realloc(list, (i + 1) * sizeof(char*));
		list[i] = (char*)malloc(sizeof(char));
	}
	return list;
}
void in_order_print(IndexTree* Root)
{
	if (Root->left != NULL)
	{
		in_order_print(Root->left);
	}
	{
		cout << Root->word << " " << Root->repetition<<" ";
		for (int i = 0; i < (Root->repetition);i++)
		{
			if (i == (sizeof(Root->lines)/sizeof(int))-1)
			{
				cout << Root->lines[i]<<"\n";
				break;
			}
			else
			{
				cout << Root->lines[i] << ",";
			}
		}
	}
	if (Root->right != NULL)
	{
		in_order_print(Root->right);
	}
}
int main()
{
	FILE* file = fopen("file.txt", "r");
	string str = readFile(file);
	char** curr_line;
	IndexTree* Root = new IndexTree;
	Root = NULL;
	int num_of_lines = line_count(str);
	int j = 0;
	for(int i = 1;i <= num_of_lines;i++)
	{
		curr_line = split(readline(i, str));
		j = 0;
		while (compare(curr_line[j] , "\0")!=0 )
		{
			insert_node(&Root, curr_line[j], i);
			j++;
		}
	}
	in_order_print(Root);
}
