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
	/* implementeaza verificare daca exista director cu numele name, la fel si la mkdir pt file */
	if (parent->head_children_files == NULL)
	{
		File *file = malloc(sizeof(File));
		// char* auxName = malloc(sizeof(name));
		// strcpy(auxName, name);
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
				free(file);
				free(name);
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			printf("%s", "File already exists\n");
			free(file);
			free(name);
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
		dir->head_children_dirs = NULL;
		dir->head_children_files = NULL;
		dir->next = NULL;
		parent->head_children_dirs = dir;
	}
	else
	{
		Dir *dir = malloc(sizeof(Dir));
		dir->name = name;
		dir->parent = parent;
		dir->head_children_dirs = NULL;
		dir->head_children_files = NULL;
		dir->next = NULL;
		Dir *aux = parent->head_children_dirs;
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, name) == 0)
			{
				printf("%s", "Directory already exists\n");
				free(dir);
				free(name);
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			printf("%s", "Directory already exists\n");
			free(dir);
			free(name);
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
		free(name);
		return;
	}
	int flag = 1;
	if (strcmp(parent->head_children_files->name, name) == 0)
	{
		flag = 0;
		File *aux = parent->head_children_files;
		if (parent->head_children_files->next == NULL)
		{
			parent->head_children_files = NULL;
			free(aux->name);
			free(aux);
			free(name);
			return;
		}
		else
		{
			/* da free la elementul sters */
			parent->head_children_files = parent->head_children_files->next;
			free(aux->name);
			free(aux);
			free(name);
			return;
		}
	}
	File *aux = parent->head_children_files;
	if (aux->next == NULL)
	{
		printf("Could not find the file\n");
		free(name);
		return;
	}
	else
	{
		while (aux->next->next != NULL)
		{
			if (strcmp(aux->next->name, name) == 0)
			{
				flag = 0;
				File *aux2 = aux->next;
				aux->next = aux->next->next;
				free(aux2->name);
				free(aux2);
				free(name);
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->next->name, name) == 0)
		{
			flag = 0;
			File *aux2 = aux->next;
			aux->next = NULL;
			free(aux2->name);
			free(aux2);
			free(name);
			return;
		}
	}
	if (flag == 1)
	{
		printf("Could not find the file\n");
		free(name);
		return;
	}
}

void rmdir(Dir *parent, char *name)
{
	if (parent->head_children_dirs == NULL)
	{
		printf("Could not find the dir\n");
		free(name);
		return;
	}
	int flag = 1;
	if (strcmp(parent->head_children_dirs->name, name) == 0)
	{
		flag = 0;
		if (parent->head_children_dirs->next == NULL)
		{
			/* elibereaza memoria directoarelor/fisierelor din directorul sters, trebuie implementat si mai jos */
			Dir *aux = parent->head_children_dirs;
			if (aux->head_children_dirs != NULL || aux->head_children_files != NULL)
			{
				if (aux->head_children_dirs != NULL)
				{
					Dir *aux2 = aux->head_children_dirs;
					while (aux2->next != NULL)
					{
						rmdir(aux, aux2->name);
						aux2 = aux2->next;
					}
					rmdir(aux, aux2->name);
				}
				if (aux->head_children_files != NULL)
				{
					File *aux2 = aux->head_children_files;
					while (aux2->next != NULL)
					{
						rm(aux, aux2->name);
						aux2 = aux2->next;
					}
					rm(aux, aux2->name);
				}
			}
			parent->head_children_dirs = NULL;
			free(aux->name);
			free(aux);
			free(name);
			return;
		}
		else
		{
			/* da free la elementul sters */
			/* elibereaza si memoria directoarelor/fisierelor din directorul sters, trebuie implementat si mai jos */
			Dir *aux = parent->head_children_dirs;
			if (aux->head_children_dirs != NULL || aux->head_children_files != NULL)
			{
				if (aux->head_children_dirs != NULL)
				{
					Dir *aux2 = aux->head_children_dirs;
					while (aux2->next != NULL)
					{
						rmdir(aux, aux2->name);
						aux2 = aux2->next;
					}
					rmdir(aux, aux2->name);
				}
				if (aux->head_children_files != NULL)
				{
					File *aux2 = aux->head_children_files;
					while (aux2->next != NULL)
					{
						rm(aux, aux2->name);
						aux2 = aux2->next;
					}
					rm(aux, aux2->name);
				}
			}
			parent->head_children_dirs = parent->head_children_dirs->next;
			free(aux->name);
			free(aux);
			free(name);
			return;
		}
	}
	Dir *aux = parent->head_children_dirs;
	if (aux->next == NULL)
	{
		printf("Could not find the dir\n");
		free(name);
		return;
	}
	else
	{
		while (aux->next->next != NULL)
		{
			if (strcmp(aux->next->name, name) == 0)
			{
				flag = 0;
				Dir *aux2 = aux->next;
				aux->next = aux->next->next;
				free(aux2->name);
				free(aux2);
				free(name);
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->next->name, name) == 0)
		{
			flag = 0;
			Dir *aux2 = aux->next;
			aux->next = NULL;
			free(aux2->name);
			free(aux2);
			free(name);
			return;
		}
	}
	if (flag == 1)
	{
		printf("Could not find the dir\n");
		free(name);
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
		{
			free(name);
			return;
		}
		free(name);
		return;
	}
	if ((*target)->head_children_dirs == NULL)
	{
		printf("No directories found!\n");
		free(name);
		return;
	}
	int flag = 1;
	if (strcmp((*target)->head_children_dirs->name, name) == 0)
	{
		flag = 0;
		(*target) = (*target)->head_children_dirs;
		free(name);
		return;
	}
	Dir *aux = (*target)->head_children_dirs;
	if (aux->next == NULL)
	{
		printf("No directories found!\n");
		free(name);
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
				free(name);
				return;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, name) == 0)
		{
			flag = 0;
			(*target) = aux;
			free(name);
			return;
		}
	}
	if (flag == 1)
	{
		printf("No directories found!\n");
		free(name);
		return;
	}
}

char *pwd(Dir *target)
{
	char *sirulPwd = malloc((2 + strlen(target->name)) * sizeof(char));
	strcpy(sirulPwd, target->name);
	strcat(sirulPwd, "/");
	// printf("%s", sirulPwd);
	// printf(">>%s<<\n", target->name);
	while (target->parent != NULL)
	{
		target = target->parent;
		sirulPwd = realloc(sirulPwd, (2 + strlen(sirulPwd) + strlen(target->name)) * sizeof(char));
		strcat(sirulPwd, target->name);
		strcat(sirulPwd, "/");
		// printf(">>%s<<\n", target->name);
	}
	char *auxPwd = malloc((1 + strlen(sirulPwd)) * sizeof(char));
	strcpy(auxPwd, "");
	char *token = strtok(sirulPwd, "/");
	while (token != NULL)
	{
		char *aux;
		aux = malloc((1 + strlen(auxPwd)) * sizeof(char));
		strcpy(aux, auxPwd);
		strcpy(auxPwd, "/");
		strcat(auxPwd, token);
		strcat(auxPwd, aux);
		free(aux);
		/*prelucreaza */
		token = strtok(NULL, "/");
	}
	free(sirulPwd);
	return auxPwd;
}

void stop(Dir *target)
{
	if (target->head_children_files != NULL)
	{
		File *aux = target->head_children_files;
		while (aux->next != NULL)
		{
			File *aux2 = aux;
			aux = aux->next;
			free(aux2->name);
			free(aux2);
			// aux = aux->next;
		}
		free(aux->name);
		free(aux);
	}
	if (target->head_children_dirs != NULL)
	{
		Dir *aux = target->head_children_dirs;
		while (aux->next != NULL)
		{
			Dir *aux2 = aux;
			if (aux->head_children_dirs != NULL || aux->head_children_files != NULL)
				stop(aux); ////
			aux = aux->next;
			free(aux2->name); ///
			free(aux2);		  ///
		}
		if (aux->head_children_dirs != NULL || aux->head_children_files != NULL)
			stop(aux);
		free(aux->name); ////
		// free(aux->name);
		free(aux);
	}
	if (strcmp(target->name, "home") == 0)
		free(target);
}

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
		free(oldname);
		free(newname);
		return;
	}
	if (direplin == 1)
	{
		/* cauta oldname in dir si file s*/
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
			if (newnameindir == 0 && parent->head_children_files != NULL)
			{
				/*cauta si in file */
				File *aux4 = parent->head_children_files;
				while (aux4->next != NULL)
				{
					if (strcmp(aux4->name, newname) == 0)
					{
						newnameindir = 1;
						break;
					}
					aux4 = aux4->next;
				}
				if (strcmp(aux4->name, newname) == 0)
					newnameindir = 1;
			}
			if (newnameindir == 0)
			/* daca newname nu exista deja in dir/file, se poate face schimbarea cu mv */
			{
				rmdir(parent, oldname);
				mkdir(parent, newname);
				free(oldname);
				return;
			}
			else
			{
				/* daca oldname s-a gasit in dir, dar newname exista deja, iar file e gol */
				if (fileeplin == 0)
				{
					printf("File/Director already exists\n");
					free(oldname);
					free(newname);
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
				free(oldname);
				free(newname);
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
			if (newnameinfile == 0 && parent->head_children_dirs != NULL)
			{
				/*cauta si in dir */
				Dir *aux5 = parent->head_children_dirs;
				while (aux5->next != NULL)
				{
					if (strcmp(aux5->name, newname) == 0)
					{
						newnameinfile = 1;
						break;
					}
					aux5 = aux5->next;
				}
				if (strcmp(aux5->name, newname) == 0)
					newnameinfile = 1;
			}
			if (newnameinfile == 0)
			/* daca newname nu exista deja in file/dir, se poate folosi mv */
			{
				rm(parent, oldname);
				touch(parent, newname);
				free(oldname);
				return;
			}
			else
			{
				/* daca newname exista deja in file/dir, iar lista de directoare s-a verificat deja */
				printf("File/Director already exists\n");
				free(oldname);
				free(newname);
				return;
			}
		}
		else
		{
			/* daca nu exista oldname in file */
			printf("File/Director not found\n");
			free(oldname);
			free(newname);
			return;
		}
	}
}

/* optimizeaza functiile
citeste tema inca o data
coding style
acolade pe rand cu antetul ca in java
comentarii
linii mai mici de 80 de caractere
whitespace
readme
mai multe fisiere + makefile */
int main()
{
	/* initializeaza directorul radacina */
	Dir *home = malloc(sizeof(Dir));
	home->name = "home";
	home->parent = NULL;
	home->head_children_files = NULL;
	home->head_children_dirs = NULL;
	home->next = NULL;
	/* citeste prima linie de la tastatura */
	char *line = malloc(MAX_INPUT_LINE_SIZE * sizeof(char));
	fgets(line, MAX_INPUT_LINE_SIZE, stdin);
	do
	{
		if (strcmp(line, "\n") == 0)
			continue;
		/* citeste primul cuvant de pe linie si il copiaza in command */
		char *token = strtok(line, "\n ");
		char *command = malloc((1 + strlen(token)) * sizeof(char));
		strcpy(command, token);
		/* apeleaza comanda touch */
		if (strcmp(command, "touch") == 0)
		{
			token = strtok(NULL, "\n ");
			char *name = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(name, token);
			touch(home, name);
		}
		/* apeleaza comanda mkdir */
		else if (strcmp(command, "mkdir") == 0)
		{
			token = strtok(NULL, "\n ");
			char *name = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(name, token);
			mkdir(home, name);
		}
		/* apeleaza comanda ls */
		else if (strcmp(command, "ls") == 0)
			ls(home);
		/* apeleaza comanda rm */
		else if (strcmp(command, "rm") == 0)
		{
			token = strtok(NULL, "\n ");
			char *name = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(name, token);
			rm(home, name);
		}
		/* apeleaza comanda rmdir */
		else if (strcmp(command, "rmdir") == 0)
		{
			token = strtok(NULL, "\n");
			char *name = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(name, token);
			rmdir(home, name);
		}
		/* apeleaza comanda cd */
		else if (strcmp(command, "cd") == 0)
		{
			token = strtok(NULL, "\n");
			char *name = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(name, token);
			cd(&home, name);
		}
		/* apeleaza comanda tree */
		else if (strcmp(command, "tree") == 0)
			tree(home, 0);
		/* apeleaza comanda pwd, afiseara sirul corespunzator */
		else if (strcmp(command, "pwd") == 0)
		{
			char *pathname = pwd(home);
			printf("%s", pathname);
			free(pathname);
		}
		/* apeleaza comanda mv */
		else if (strcmp(command, "mv") == 0)
		{
			token = strtok(NULL, "\n ");
			char *oldname = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(oldname, token);
			token = strtok(NULL, "\n ");
			char *newname = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(newname, token);
			mv(home, oldname, newname);
		}
		/* apeleaza comanda stop, elibereaza memoria */
		else if (strcmp(command, "stop") == 0)
		{
			while (home->parent != NULL)
				home = home->parent;
			stop(home);
		}
		/* trece peste alte comenzi */
		else
		{
			free(command);
			continue;
		}
		free(command);
	} while (fgets(line, MAX_INPUT_LINE_SIZE, stdin) != NULL);
	/* elibereaza memoria */
	free(line);
	return 0;
}