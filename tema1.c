#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir
{
	char *name;
	struct Dir *parent;
	struct File *head_children_files;
	struct Dir *head_children_dirs;
	struct Dir *next;
} Dir;

typedef struct File
{
	char *name;
	struct Dir *parent;
	struct File *next;
} File;

void touch(Dir *parent, char *name)
{
	if (parent->head_children_files == NULL)
	{
		File *file = malloc(sizeof(File));
		file->name = name;
		file->parent = parent;
		file->next = NULL;
		parent->head_children_files = file;
	}
	else
	{
		File *file = malloc(sizeof(File));
		file->name = name;
		file->parent = parent;
		file->next = NULL;
		File *aux = parent->head_children_files;
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, name) == 0)
			{
				printf("%s", "File already exists\n");
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			printf("%s", "File already exists\n");
			return;
		}
		aux->next = file;
	}
}

void mkdir(Dir *parent, char *name)
{
	if (parent->head_children_dirs == NULL)
	{
		Dir *dir = malloc(sizeof(Dir));
		dir->name = name;
		dir->parent = parent;
		dir->next = NULL;
		parent->head_children_dirs = dir;
	}
	else
	{
		Dir *dir = malloc(sizeof(Dir));
		dir->name = name;
		dir->parent = parent;
		dir->next = NULL;
		Dir *aux = parent->head_children_dirs;
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, name) == 0)
			{
				printf("%s", "Directory already exists\n");
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			printf("%s", "Directory already exists\n");
			return;
		}
		aux->next = dir;
	}
}

void ls(Dir *parent)
{
	if (parent->head_children_dirs != NULL)
	{
		Dir *aux1 = parent->head_children_dirs;
		while (aux1->next != NULL)
		{
			printf("%s\n", aux1->name);
			aux1 = aux1->next;
		}
		printf("%s\n", aux1->name);
	}
	if (parent->head_children_files != NULL)
	{
		File *aux = parent->head_children_files;
		while (aux->next != NULL)
		{
			printf("%s\n", aux->name);
			aux = aux->next;
		}
		printf("%s\n", aux->name);
	}
}

void rm(Dir *parent, char *name)
{
	if (parent->head_children_files == NULL)
	{
		printf("Could not find the file\n");
		return;
	}
	int flag = 1;
	if (strcmp(parent->head_children_files->name, name) == 0)
	{
		flag = 0;
		if (parent->head_children_files->next == NULL)
		{
			parent->head_children_files = NULL;
			return;
		}
		else
		{
			/* da free la elementul sters */
			parent->head_children_files = parent->head_children_files->next;
			return;
		}
	}
	File *aux = parent->head_children_files;
	if (aux->next == NULL)
	{
		printf("Could not find the file\n");
		return;
	}
	else
	{
		while (aux->next->next != NULL)
		{
			if (strcmp(aux->next->name, name) == 0)
			{
				flag = 0;
				aux->next = aux->next->next;
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->next->name, name) == 0)
		{
			flag = 0;
			aux->next = NULL;
			return;
		}
	}
	if (flag == 1)
	{
		printf("Could not find the file\n");
		return;
	}
}

void rmdir(Dir *parent, char *name)
{
	if (parent->head_children_dirs == NULL)
	{
		printf("Could not find the dir\n");
		return;
	}
	int flag = 1;
	if (strcmp(parent->head_children_dirs->name, name) == 0)
	{
		flag = 0;
		if (parent->head_children_dirs->next == NULL)
		{
			parent->head_children_dirs = NULL;
			return;
		}
		else
		{
			/* da free la elementul sters */
			parent->head_children_dirs = parent->head_children_dirs->next;
			return;
		}
	}
	Dir *aux = parent->head_children_dirs;
	if (aux->next == NULL)
	{
		printf("Could not find the dir\n");
		return;
	}
	else
	{
		while (aux->next->next != NULL)
		{
			if (strcmp(aux->next->name, name) == 0)
			{
				flag = 0;
				aux->next = aux->next->next;
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->next->name, name) == 0)
		{
			flag = 0;
			aux->next = NULL;
			return;
		}
	}
	if (flag == 1)
	{
		printf("Could not find the dir\n");
		return;
	}
}

void cd(Dir **target, char *name) {}

char *pwd(Dir *target) {}

void stop(Dir *target) {}

void tree(Dir *target, int level) {}

void mv(Dir *parent, char *oldname, char *newname) {}

int main()
{
	// FILE *pFile;
	// pFile = fopen("exemplu.in", "r");
	Dir *home = malloc(sizeof(Dir));
	char *comanda, *nume;
	do
	{
		/* aloca eficient memoria */
		comanda = malloc(10 * sizeof(char));
		nume = malloc(10 * sizeof(char));
		// fscanf(pFile, "%s", comanda);
		scanf("%s", comanda);
		if (strcmp(comanda, "touch") == 0)
		{
			// fscanf(pFile, "%s", nume);
			scanf("%s", nume);
			touch(home, nume);
		}
		if (strcmp(comanda, "mkdir") == 0)
		{
			// fscanf(pFile, "%s", nume);
			scanf("%s", nume);
			mkdir(home, nume);
		}
		if (strcmp(comanda, "ls") == 0)
		{
			ls(home);
		}
		if (strcmp(comanda, "rm") == 0)
		{
			// fscanf(pFile, "%s", nume);
			scanf("%s", nume);
			rm(home, nume);
		}
		if (strcmp(comanda, "rmdir") == 0)
		{
			// fscanf(pFile, "%s", nume);
			scanf("%s", nume);
			rmdir(home, nume);
		}
		// if (strcmp(comanda, "cd") == 0)
		// {
		// 	scanf("%s", nume);
		// 	cd(home, nume);
		// }
	} while (strcmp(comanda, "stop") != 0);
	return 0;
}