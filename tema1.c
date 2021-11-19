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
			return;
		}
		else
		{
			/* da free la elementul sters */
			parent->head_children_files = parent->head_children_files->next;
			free(aux->name);
			free(aux);
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
				File *aux2 = aux->next;
				aux->next = aux->next->next;
				free(aux2->name);
				free(aux2);
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
			/* elibereaza memoria directoarelor/fisierelor din directorul sters, trebuie implementat si mai jos */
			Dir *aux = parent->head_children_dirs;
			if (aux->head_children_dirs != NULL || aux->head_children_files!=NULL)
			{
				if (aux->head_children_dirs != NULL)
				{
					Dir* aux2=aux->head_children_dirs;
					while (aux2->next!=NULL)
					{
						rmdir(aux, aux2->name);
						aux2=aux2->next;
					}
					rmdir(aux, aux2->name);
				}
				if (aux->head_children_files != NULL)
				{
					File* aux2 = aux->head_children_files;
					while (aux2->next!=NULL)
					{
						rm(aux, aux2->name);
						aux2=aux2->next;
					}
					rm(aux, aux2->name);
				}
			}
			parent->head_children_dirs = NULL;
			free(aux->name);
			free(aux);
			return;
		}
		else
		{
			/* da free la elementul sters */
			Dir *aux = parent->head_children_dirs;
			parent->head_children_dirs = parent->head_children_dirs->next;
			free(aux->name);
			free(aux);
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
				Dir *aux2 = aux->next;
				aux->next = aux->next->next;
				free(aux2->name);
				free(aux2);
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
	// char* aux;
	// if (target->parent == NULL)
	// {
	// 	aux = malloc(6*sizeof(char));
	// 	strcpy(aux, "/home");
	// 	return aux;
	// }
	// else
	// {
	// 	if (aux == NULL)
	// 	{
	// 		aux = malloc(1+sizeof(aux)+strlen(target->name));
	// 	}
	// 	else
	// 	// char * aux;
	// 	// char * altaux = malloc(1000*sizeof(char));
	// 	// strcpy(altaux, pwd(target->parent));
	// 	// char * aux = malloc((10+strlen(target->name))*sizeof(char));
	// 		aux = realloc(aux, 1000+strlen(target->name));
	// 	// char *aux = malloc((2 + strlen(pwd(target->parent)) + strlen(target->name)) * sizeof(char));
	// 	strcpy(aux, pwd(target->parent));
	// 	// char *aux2;
	// 	// strcat(strcat(aux, "/"), target->name);
	// 	// strcpy(aux2, pwd(target->parent));

	// 	// free(aux);
	// 	return strcat(strcat(aux, "/"), target->name);
	// }
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
				return;
			}
			else
			{
				/* daca newname exista deja in file/dir, iar lista de directoare s-a verificat deja */
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
	// FILE *pFile;
	// pFile = fopen("exemplu.in", "r");
	Dir *home = malloc(sizeof(Dir));
	home->name = "home";
	home->head_children_files = NULL;
	home->head_children_dirs = NULL;
	home->parent = NULL;
	char *comanda, *nume, *numevechi, *numenou;
	char *line = malloc(MAX_INPUT_LINE_SIZE * sizeof(char));
	fgets(line, MAX_INPUT_LINE_SIZE, stdin);
	do
	{
		/* aloca eficient memoria */
		if (strcmp(line, "\n") != 0)
		{
			char *token = strtok(line, "\n ");
			// while (token != NULL)
			// {
			// printf(">>%s<<\n", token);
			comanda = malloc((1 + strlen(token)) * sizeof(char));
			strcpy(comanda, token);
			if (strcmp(comanda, "touch") == 0)
			{
				token = strtok(NULL, "\n ");
				/// 1+
				nume = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(nume, token);
				// fscanf(pFile, "%s", nume);
				// // scanf("%s", nume);
				touch(home, nume);
				free(comanda);
			}
			else if (strcmp(comanda, "mkdir") == 0)
			{
				token = strtok(NULL, "\n ");
				nume = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(nume, token);
				mkdir(home, nume);
				free(comanda);
			}
			else if (strcmp(comanda, "ls") == 0)
			{
				ls(home);
				free(comanda);
			}
			else if (strcmp(comanda, "stop") == 0)
			{
				Dir *aux = home;
				while (strcmp(aux->name, "home") != 0)
					aux = aux->parent;
				stop(aux);
				free(comanda);
			}
			else if (strcmp(comanda, "rm") == 0)
			{
				token = strtok(NULL, "\n ");
				/* fa si aia cu daca Ana [3] sa fie marimea 4 */
				nume = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(nume, token);
				rm(home, nume);
				free(comanda);
				free(nume);
			}
			else if (strcmp(comanda, "rmdir") == 0)
			{
				token = strtok(NULL, "\n");
				nume = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(nume, token);
				rmdir(home, nume);
				free(comanda);
				free(nume);
			}
			else if (strcmp(comanda, "cd") == 0)
			{
				token = strtok(NULL, "\n");
				nume = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(nume, token);
				cd(&home, nume);
				free(comanda);
				free(nume);
			}
			else if (strcmp(comanda, "tree") == 0)
			{
				tree(home, 0);
				free(comanda);
			}
			else if (strcmp(comanda, "pwd") == 0)
			{
				// printf("%s", pwd(home));
				// pwd(home);

				// pwd(home);
				char *workingdirectory = pwd(home);
				printf("%s", workingdirectory);
				// // if (strcmp(workingdirectory, home->name) != 0)
				free(workingdirectory);
				free(comanda);
			}
			else if (strcmp(comanda, "mv") == 0)
			{
				token = strtok(NULL, "\n ");
				numevechi = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(numevechi, token);
				token = strtok(NULL, "\n ");
				numenou = malloc((1 + strlen(token)) * sizeof(char));
				strcpy(numenou, token);
				mv(home, numevechi, numenou);
				free(comanda);
			}
			else
			{
				free(comanda);
				continue;
			}
			// if (strcmp(comanda, "mv") == 0)
			// {
			// 	fscanf(pFile, "%s", numevechi);
			// 	fscanf(pFile, "%s", numenou);
			// 	// scanf("%s", numevechi);
			// 	// scanf("%s", numenou);
			// 	mv(home, numevechi, numenou);
		}
	} while (fgets(line, MAX_INPUT_LINE_SIZE, stdin) != NULL);
	// while ()
	// free(home);
	free(line);
	// fclose(pFile);
	return 0;
	/* adauga exceptii */
	/* maybe fflush stdin? */
}