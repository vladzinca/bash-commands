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

void cd(Dir **target, char *name)
{
	if (strcmp(name, "..") == 0)
	{
		if ((*target)->parent != NULL)
			(*target) = (*target)->parent;
		else
			return;
		return;
	}
	if ((*target)->head_children_dirs == NULL)
	{
		printf("No directories found!\n");
		return;
	}
	int flag = 1;
	if (strcmp((*target)->head_children_dirs->name, name) == 0)
	{
		flag = 0;
		(*target) = (*target)->head_children_dirs;
		return;
	}
	Dir *aux = (*target)->head_children_dirs;
	if (aux->next == NULL)
	{
		printf("No directories found!\n");
		return;
	}
	else
	{
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, name) == 0)
			{
				flag = 0;
				(*target) = aux;
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			flag = 0;
			(*target) = aux;
			return;
		}
	}
	if (flag == 1)
	{
		printf("No directories found!\n");
		return;
	}
}

char *pwd(Dir *target)
{
	if (target->parent == NULL)
	{
		return "/home";
	}
	else
	{
		char *aux = malloc(1000 * sizeof(char));
		strcpy(aux, pwd(target->parent));
		strcat(strcat(aux, "/"), target->name);
		return aux;
		// return strcat(aux, target->name);
		// aux = strcat(pwd(target->parent), target->name);
	}
}

void stop(Dir *target) {}

void tree(Dir *target, int level)
{
	if (target->head_children_dirs != NULL)
	{
		Dir *aux1 = target->head_children_dirs;
		while (aux1->next != NULL)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf("%s\n", aux1->name);
			tree(aux1, level + 1);
			aux1 = aux1->next;
		}
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", aux1->name);
		tree(aux1, level + 1);
	}
	if (target->head_children_files != NULL)
	{
		File *aux = target->head_children_files;
		while (aux->next != NULL)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf("%s\n", aux->name);
			aux = aux->next;
		}
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", aux->name);
	}
}

void mv(Dir *parent, char *oldname, char *newname)
{
	/* daca avem fisier si director cu acelasi nume, se schimba doar directorul */
	int direplin = 1, fileeplin = 1;
	if (parent->head_children_dirs == NULL)
	{
		direplin = 0;
	}
	if (parent->head_children_files == NULL)
	{
		fileeplin = 0;
	}
	if (direplin == 0 && fileeplin == 0)
	{
		/* daca si dir si file sunt goale */
		printf("File/Director not found\n");
		return;
	}
	if (direplin == 1)
	{
		/* cauta oldname in dir */
		int oldnameindir = 0;
		Dir *aux = parent->head_children_dirs;
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, oldname) == 0)
			{
				oldnameindir = 1;
				break;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, oldname) == 0)
			oldnameindir = 1;
		if (oldnameindir == 1)
		{
			/* daca oldname s-a gasit in dir, cauta newname */
			int newnameindir = 0;
			Dir *aux1 = parent->head_children_dirs;
			while (aux1->next != NULL)
			{
				if (strcmp(aux1->name, newname) == 0)
				{
					newnameindir = 1;
					break;
				}
				aux1 = aux1->next;
			}
			if (strcmp(aux1->name, newname) == 0)
				newnameindir = 1;
			if (newnameindir == 0)
			/* daca newname nu exista deja in dir, se poate face schimbarea cu mv */
			{
				rmdir(parent, oldname);
				mkdir(parent, newname);
				return;
			}
			else
			{
				/* daca oldname s-a gasit in dir, dar newname exista deja, iar file e gol */
				if (fileeplin == 0)
				{
					printf("File/Director already exists\n");
					return;
				}
			}
		}
		else
		{
			/* daca oldname nu s-a gasit in dir, iar file e gol */
			if (fileeplin == 0)
			{
				printf("File/Director not found\n");
				return;
			}
		}
	}
	if (fileeplin == 1)
	{
		/* cauta oldname in file */
		int oldnameinfile = 0;
		File *aux2 = parent->head_children_files;
		while (aux2->next != NULL)
		{
			if (strcmp(aux2->name, oldname) == 0)
			{
				oldnameinfile = 1;
				break;
			}
			aux2 = aux2->next;
		}
		if (strcmp(aux2->name, oldname) == 0)
			oldnameinfile = 1;
		if (oldnameinfile = 1)
		{
			/* daca exista oldname in file, cauta newname in file */
			int newnameinfile = 0;
			File *aux3 = parent->head_children_files;
			while (aux3->next != NULL)
			{
				if (strcmp(aux3->name, newname) == 0)
				{
					newnameinfile = 1;
					break;
				}
				aux3 = aux3->next;
			}
			if (strcmp(aux3->name, newname) == 0)
				newnameinfile = 1;
			if (newnameinfile == 0)
			/* daca newname nu exista deja in file, se poate folosi mv */
			{
				rm(parent, oldname);
				touch(parent, newname);
				return;
			}
			else
			{
				/* daca newname exista deja in file, iar lista de directoare s-a verificat deja */
				printf("File/Director already exists\n");
				return;
			}
		}
		else
		{
			/* daca nu exista oldname in file */
			printf("File/Director not found\n");
			return;
		}
	}
}

int main()
{
	FILE *pFile;
	pFile = fopen("exemplu.in", "r");
	Dir *home = malloc(sizeof(Dir));
	char *comanda, *nume, *numevechi, *numenou;
	do
	{
		/* aloca eficient memoria */
		comanda = malloc(10 * sizeof(char));
		nume = malloc(10 * sizeof(char));
		numevechi = malloc(10 * sizeof(char));
		numenou = malloc(10 * sizeof(char));
		fscanf(pFile, "%s", comanda);
		// scanf("%s", comanda);
		if (strcmp(comanda, "touch") == 0)
		{
			fscanf(pFile, "%s", nume);
			// scanf("%s", nume);
			touch(home, nume);
		}
		if (strcmp(comanda, "mkdir") == 0)
		{
			fscanf(pFile, "%s", nume);
			// scanf("%s", nume);
			mkdir(home, nume);
		}
		if (strcmp(comanda, "ls") == 0)
		{
			ls(home);
		}
		if (strcmp(comanda, "rm") == 0)
		{
			fscanf(pFile, "%s", nume);
			// scanf("%s", nume);
			rm(home, nume);
		}
		if (strcmp(comanda, "rmdir") == 0)
		{
			fscanf(pFile, "%s", nume);
			// scanf("%s", nume);
			rmdir(home, nume);
		}
		if (strcmp(comanda, "cd") == 0)
		{
			fscanf(pFile, "%s", nume);
			// scanf("%s", nume);
			cd(&home, nume);
		}
		if (strcmp(comanda, "tree") == 0)
		{
			tree(home, 0);
		}
		if (strcmp(comanda, "pwd") == 0)
		{
			printf("%s", pwd(home));
		}
		if (strcmp(comanda, "mv") == 0)
		{
			fscanf(pFile, "%s", numevechi);
			fscanf(pFile, "%s", numenou);
			// scanf("%s", numevechi);
			// scanf("%s", numenou);
			mv(home, numevechi, numenou);
		}
	} while (strcmp(comanda, "stop") != 0);
	return 0;
}