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
		File* aux = parent->head_children_files;
		while (aux->next!=NULL) {
			aux=aux->next;
		}
		aux->next=file;
	}
}

void mkdir(Dir *parent, char *name) {}

void ls(Dir *parent) {}

void rm(Dir *parent, char *name) {}

void rmdir(Dir *parent, char *name) {}

void cd(Dir **target, char *name) {}

char *pwd(Dir *target) {}

void stop(Dir *target) {}

void tree(Dir *target, int level) {}

void mv(Dir *parent, char *oldname, char *newname) {}

int main()
{
	Dir *home = malloc(sizeof(Dir));
	char *comanda, *nume;
	comanda = malloc(10 * sizeof(char));
	nume = malloc(10 * sizeof(char));
	scanf("%s", comanda);
	scanf("%s", nume);
	if (strcmp(comanda, "touch") == 0)
	{
		touch(home, nume);
	}
	scanf("%s", comanda);
	scanf("%s", nume);
	if (strcmp(comanda, "touch") == 0)
	{
		touch(home, nume);
	}
	// do
	// {
	// 	/*
	// 	Summary:
	// 		Reads from stdin a string and breaks it down into command and in
	// 		case it needs into a name.
	// 	*/
	// } while (/*condition*/);
	return 0;
}
