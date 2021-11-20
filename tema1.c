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
		/* daca nu exista niciun fisier sau director in directorul parent */
		if (parent->head_children_dirs == NULL)
		{
			File *file = malloc(sizeof(File));
			file->name = name;
			file->parent = parent;
			file->next = NULL;
			parent->head_children_files = file;
		}
		/* daca nu exista niciun fisier dar exista directoare in directorul parent */
		else
		{
			Dir *auxDir = parent->head_children_dirs;
			while (auxDir->next != NULL)
			{
				if (strcmp(auxDir->name, name) == 0)
				{
					printf("File already exists\n");
					free(name);
					return;
				}
				auxDir = auxDir->next;
			}
			/* daca ultimul director din directorul parent are numele name */
			if (strcmp(auxDir->name, name) == 0)
			{
				printf("File already exists\n");
				free(name);
				return;
			}
			/* daca nu s-a gasit director cu numele name si nu exista fisiere in directorul parent */
			File *file = malloc(sizeof(File));
			file->name = name;
			file->parent = parent;
			file->next = NULL;
			parent->head_children_files = file;
		}
	}
	else
	{
		/* daca exista fisiere in directorul parent */
		File *auxFile = parent->head_children_files;
		while (auxFile->next != NULL)
		{
			if (strcmp(auxFile->name, name) == 0)
			{
				printf("File already exists\n");
				free(name);
				return;
			}
			auxFile = auxFile->next;
		}
		if (strcmp(auxFile->name, name) == 0)
		{
			printf("File already exists\n");
			free(name);
			return;
		}
		/* daca nu s-a gasit fisier cu numele name si nu exista directoare in directorul parent */
		if (parent->head_children_dirs == NULL)
		{
			File *file = malloc(sizeof(File));
			file->name = name;
			file->parent = parent;
			file->next = NULL;
			auxFile->next = file;
		}
		/* daca nu s-a gasit fisier cu numele name dar exista directoare in directorul parent */
		else
		{
			Dir *auxDir = parent->head_children_dirs;
			while (auxDir->next != NULL)
			{
				if (strcmp(auxDir->name, name) == 0)
				{
					printf("File already exists\n");
					free(name);
					return;
				}
				auxDir = auxDir->next;
			}
			if (strcmp(auxDir->name, name) == 0)
			{
				printf("File already exists\n");
				free(name);
				return;
			}
			/* daca nu s-au gasit fisier sau director cu numele name in directorul parent */
			File *file = malloc(sizeof(File));
			file->name = name;
			file->parent = parent;
			file->next = NULL;
			auxFile->next = file;
		}
	}
}

void mkdir(Dir *parent, char *name)
{
	if (parent->head_children_dirs == NULL)
	{
		/* daca nu exista niciun director sau fisier in directorul parent */
		if (parent->head_children_files == NULL)
		{
			Dir *dir = malloc(sizeof(Dir));
			dir->name = name;
			dir->parent = parent;
			dir->head_children_dirs = NULL;
			dir->head_children_files = NULL;
			dir->next = NULL;
			parent->head_children_dirs = dir;
		}
		/* daca nu exista niciun director dar exista fisiere in directorul parent */
		else
		{
			File *auxFile = parent->head_children_files;
			while (auxFile->next != NULL)
			{
				if (strcmp(auxFile->name, name) == 0)
				{
					printf("Directory already exists\n");
					free(name);
					return;
				}
				auxFile = auxFile->next;
			}
			if (strcmp(auxFile->name, name) == 0)
			{
				printf("Directory already exists\n");
				free(name);
				return;
			}
			/* daca nu s-a gasit fisier cu numele name si nu exista directoare in directorul parent */
			Dir *dir = malloc(sizeof(Dir));
			dir->name = name;
			dir->parent = parent;
			dir->head_children_dirs = NULL;
			dir->head_children_files = NULL;
			dir->next = NULL;
			parent->head_children_dirs = dir;
		}
	}
	else
	{
		/* daca exista directoare in directorul parent */
		Dir *auxDir = parent->head_children_dirs;
		while (auxDir->next != NULL)
		{
			if (strcmp(auxDir->name, name) == 0)
			{
				printf("Directory already exists\n");
				free(name);
				return;
			}
			auxDir = auxDir->next;
		}
		if (strcmp(auxDir->name, name) == 0)
		{
			printf("Directory already exists\n");
			free(name);
			return;
		}
		/* daca nu s-a gasit director cu numele name si nu exista fisiere in directorul parent */
		if (parent->head_children_files == NULL)
		{
			Dir *dir = malloc(sizeof(Dir));
			dir->name = name;
			dir->parent = parent;
			dir->head_children_dirs = NULL;
			dir->head_children_files = NULL;
			dir->next = NULL;
			auxDir->next = dir;
		}
		/* daca nu s-a gasit director cu numele name dar exista fisiere in directorul parent */
		else
		{
			File *auxFile = parent->head_children_files;
			while (auxFile->next != NULL)
			{
				if (strcmp(auxFile->name, name) == 0)
				{
					printf("File already exists\n");
					free(name);
					return;
				}
				auxFile = auxFile->next;
			}
			if (strcmp(auxFile->name, name) == 0)
			{
				printf("File already exists\n");
				free(name);
				return;
			}
			/* daca nu s-au gasit director sau fisier cu numele name in directorul parent */
			Dir *dir = malloc(sizeof(Dir));
			dir->name = name;
			dir->parent = parent;
			dir->head_children_dirs = NULL;
			dir->head_children_files = NULL;
			dir->next = NULL;
			auxDir->next = dir;
		}
	}
}

void ls(Dir *parent)
{
	/* afiseaza directoarele din directorul parent */
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
	/* afiseaza fisierele din directorul parent */
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
	/* daca nu exista niciun fisier in directorul parent */
	if (parent->head_children_files == NULL)
	{
		printf("Could not find the file\n");
		free(name);
		return;
	}
	/* daca primul fisier din directorul parent are numele name */
	if (strcmp(parent->head_children_files->name, name) == 0)
	{
		File *delFile = parent->head_children_files;
		if (parent->head_children_files->next == NULL)
			parent->head_children_files = NULL;
		else
			parent->head_children_files = parent->head_children_files->next;
		free(delFile->name);
		free(delFile);
		free(name);
		return;
	}
	/* daca primul fisier din directorul parent nu are numele name, dar este singurul fisier din directorul parent */
	if (parent->head_children_files->next == NULL)
	{
		printf("Could not find the file\n");
		free(name);
		return;
	}
	/* daca primul fisier din directorul parent nu are numele name, dar exista si alte fisiere in directorul parent */
	else
	{
		File *auxFile = parent->head_children_files;
		while (auxFile->next->next != NULL)
		{
			if (strcmp(auxFile->next->name, name) == 0)
			{
				File *delFile = auxFile->next;
				auxFile->next = auxFile->next->next;
				free(delFile->name);
				free(delFile);
				free(name);
				return;
			}
			auxFile = auxFile->next;
		}
		/* daca ultimul fisier din directorul parent are numele name */
		if (strcmp(auxFile->next->name, name) == 0)
		{
			File *delFile = auxFile->next;
			auxFile->next = NULL;
			free(delFile->name);
			free(delFile);
			free(name);
			return;
		}
	}
	/* daca fisierul cu numele name nu a fost gasit in directorul parent */
	printf("Could not find the file\n");
	free(name);
	return;
}

void rmdir(Dir *parent, char *name)
{
	/* daca nu exista niciun director in directorul parent */
	if (parent->head_children_dirs == NULL)
	{
		printf("Could not find the dir\n");
		free(name);
		return;
	}
	/* daca primul director din directorul parent are numele name */
	if (strcmp(parent->head_children_dirs->name, name) == 0)
	{
		/* mai intai sterge recursiv toate directoarele si fisierele care se afla in directorul cu numele name */
		Dir *delDir = parent->head_children_dirs;
		if (delDir->head_children_dirs != NULL || delDir->head_children_files != NULL)
		{
			if (delDir->head_children_dirs != NULL)
			{
				Dir *childDir = delDir->head_children_dirs;
				while (childDir->next != NULL)
				{
					rmdir(delDir, childDir->name);
					childDir = childDir->next;
				}
				rmdir(delDir, childDir->name);
			}
			if (delDir->head_children_files != NULL)
			{
				File *childFile = delDir->head_children_files;
				while (childFile->next != NULL)
				{
					rm(delDir, childFile->name);
					childFile = childFile->next;
				}
				rm(delDir, childFile->name);
			}
		}
		if (parent->head_children_dirs->next == NULL)
			parent->head_children_dirs = NULL;
		else
			parent->head_children_dirs = parent->head_children_dirs->next;
		free(delDir->name);
		free(delDir);
		free(name);
		return;
	}
	/* daca primul director din directorul parent nu are numele name, dar este singurul director din directorul parent */
	if (parent->head_children_dirs->next == NULL)
	{
		printf("Could not find the dir\n");
		free(name);
		return;
	}
	/* daca primul director din directorul parent nu are numele name, dar exista si alte directoare in directorul parent */
	else
	{
		Dir *auxDir = parent->head_children_dirs;
		while (auxDir->next->next != NULL)
		{
			if (strcmp(auxDir->next->name, name) == 0)
			{
				Dir *parentDir = auxDir->next;
				if (parentDir->head_children_dirs != NULL || parentDir->head_children_files != NULL)
				{
					if (parentDir->head_children_dirs != NULL)
					{
						Dir *childDir = parentDir->head_children_dirs;
						while (childDir->next != NULL)
						{
							rmdir(parentDir, childDir->name);
							childDir = childDir->next;
						}
						rmdir(parentDir, childDir->name);
					}
					if (parentDir->head_children_files != NULL)
					{
						File *childFile = parentDir->head_children_files;
						while (childFile->next != NULL)
						{
							rm(parentDir, childFile->name);
							childFile = childFile->next;
						}
						rm(parentDir, childFile->name);
					}
				}
				Dir *delDir = auxDir->next;
				auxDir->next = auxDir->next->next;
				free(delDir->name);
				free(delDir);
				free(name);
				return;
			}
			auxDir = auxDir->next;
		}
		/* daca ultimul director din directorul parent are numele name */
		if (strcmp(auxDir->next->name, name) == 0)
		{
			Dir *parentDir = auxDir->next;
			if (parentDir->head_children_dirs != NULL || parentDir->head_children_files != NULL)
			{
				if (parentDir->head_children_dirs != NULL)
				{
					Dir *childDir = parentDir->head_children_dirs;
					while (childDir->next != NULL)
					{
						rmdir(parentDir, childDir->name);
						childDir = childDir->next;
					}
					rmdir(parentDir, childDir->name);
				}
				if (parentDir->head_children_files != NULL)
				{
					File *childDir = parentDir->head_children_files;
					while (childDir->next != NULL)
					{
						rm(parentDir, childDir->name);
						childDir = childDir->next;
					}
					rm(parentDir, childDir->name);
				}
			}
			Dir *delDir = auxDir->next;
			auxDir->next = NULL;
			free(delDir->name);
			free(delDir);
			free(name);
			return;
		}
	}
	/* daca directorul cu numele name nu a fost gasit in directorul parent */
	printf("Could not find the dir\n");
	free(name);
	return;
}

void cd(Dir **target, char *name)
{
	/* daca primeste numele ".." schimba directorul curent in directorul parinte al celui curent */
	if (strcmp(name, "..") == 0)
	{
		if ((*target)->parent != NULL)
			(*target) = (*target)->parent;
		free(name);
		return;
	}
	/* daca nu primeste numele "..", iar in directorul curent nu exista niciun director */
	if ((*target)->head_children_dirs == NULL)
	{
		printf("No directories found!\n");
		free(name);
		return;
	}
	/* daca primul director din directorul curent are numele name */
	if (strcmp((*target)->head_children_dirs->name, name) == 0)
	{
		(*target) = (*target)->head_children_dirs;
		free(name);
		return;
	}
	/* daca primul director din directorul curent nu are numele name, dar este singurul director din directorul curent */
	if ((*target)->head_children_dirs->next == NULL)
	{
		printf("No directories found!\n");
		free(name);
		return;
	}
	/* daca primul director din directorul curent nu are numele name, dar exista si alte directoare in directorul curent */
	else
	{
		Dir *auxDir = (*target)->head_children_dirs;
		while (auxDir->next != NULL)
		{
			if (strcmp(auxDir->name, name) == 0)
			{
				(*target) = auxDir;
				free(name);
				return;
			}
			auxDir = auxDir->next;
		}
		/* daca ultimul director din directorul curent are numele name */
		if (strcmp(auxDir->name, name) == 0)
		{
			(*target) = auxDir;
			free(name);
			return;
		}
	}
	/* daca directorul cu numele name nu a fost gasit in directorul curent */
	printf("No directories found!\n");
	free(name);
	return;
}

char *pwd(Dir *target)
{
	/* creeaza sirul pwd invers, de forma target/.../home/ */
	char *inverseString = malloc((2 + strlen(target->name)) * sizeof(char));
	strcpy(inverseString, target->name);
	strcat(inverseString, "/");
	while (target->parent != NULL)
	{
		target = target->parent;
		inverseString = realloc(inverseString, (2 + strlen(inverseString) + strlen(target->name)) * sizeof(char));
		strcat(strcat(inverseString, target->name), "/");
	}
	/* sparge sirul obtinut cu strtok si creeaza sirul dorit, punand in el cuvintele in ordinea dorita /home/.../target */
	char *pwdString = malloc((1 + strlen(inverseString)) * sizeof(char));
	char *token = strtok(inverseString, "/");
	while (token != NULL)
	{
		char *oldString = malloc((1 + strlen(pwdString)) * sizeof(char));
		strcpy(oldString, pwdString);
		strcpy(pwdString, "/");
		strcat(strcat(pwdString, token), oldString);
		free(oldString);
		token = strtok(NULL, "/");
	}
	free(inverseString);
	return pwdString;
}

void stop(Dir *target)
{
	/* daca exista fisiere in directorul curent, elibereaza memoria alocata lor */
	if (target->head_children_files != NULL)
	{
		File *auxFile = target->head_children_files;
		while (auxFile->next != NULL)
		{
			File *freeFile = auxFile;
			auxFile = auxFile->next;
			free(freeFile->name);
			free(freeFile);
		}
		free(auxFile->name);
		free(auxFile);
	}
	/* daca exista directoare in directorul curent, elibereaza memoria alocata lor */
	if (target->head_children_dirs != NULL)
	{
		Dir *auxDir = target->head_children_dirs;
		while (auxDir->next != NULL)
		{
			Dir *freeDir = auxDir;
			/* elibereaza recursiv memoria alocata directoarelor si fisierelor din directorul eliberat */
			if (auxDir->head_children_dirs != NULL || auxDir->head_children_files != NULL)
				stop(auxDir);
			auxDir = auxDir->next;
			free(freeDir->name);
			free(freeDir);
		}
		/* elibereaza memoria alocata ultimului fisier */
		if (auxDir->head_children_dirs != NULL || auxDir->head_children_files != NULL)
			stop(auxDir);
		free(auxDir->name);
		free(auxDir);
	}
	/* elibereaza memoria alocata directorului radacina */
	if (strcmp(target->name, "home") == 0)
		free(target);
}

void tree(Dir *target, int level)
{
	/* afiseaza recursiv directoarele din directorul curent si continutul lor sub forma de tree */
	if (target->head_children_dirs != NULL)
	{
		Dir *auxDir = target->head_children_dirs;
		while (auxDir->next != NULL)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf("%s\n", auxDir->name);
			tree(auxDir, level + 1);
			auxDir = auxDir->next;
		}
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", auxDir->name);
		tree(auxDir, level + 1);
	}
	/* afiseza fisierele din directorul curent sub forma de tree */
	if (target->head_children_files != NULL)
	{
		File *auxFile = target->head_children_files;
		while (auxFile->next != NULL)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf("%s\n", auxFile->name);
			auxFile = auxFile->next;
		}
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", auxFile->name);
	}
}

void mv(Dir *parent, char *oldname, char *newname)
{
	/* daca nu exista niciun director sau fisier in directorul parent */
	if (parent->head_children_dirs == NULL && parent->head_children_files == NULL)
	{
		printf("File/Director not found\n");
		free(oldname);
		free(newname);
		return;
	}
	/* daca exista directoare in directorul parent */
	if (parent->head_children_dirs != NULL)
	{
		/* cauta un director cu numele oldname in directorul parent */
		int oldnameAsDir = 0;
		Dir *aux = parent->head_children_dirs;
		while (aux->next != NULL)
		{
			if (strcmp(aux->name, oldname) == 0)
			{
				oldnameAsDir = 1;
				break;
			}
			aux = aux->next;
		}
		if (strcmp(aux->name, oldname) == 0)
			oldnameAsDir = 1;
		/* daca s-a gasit un director cu numele oldname in directorul parent, cauta director cu numele newname */
		if (oldnameAsDir == 1)
		{
			int newnameAsDirOrFile = 0;
			Dir *aux1 = parent->head_children_dirs;
			while (aux1->next != NULL)
			{
				if (strcmp(aux1->name, newname) == 0)
				{
					newnameAsDirOrFile = 1;
					break;
				}
				aux1 = aux1->next;
			}
			if (strcmp(aux1->name, newname) == 0)
				newnameAsDirOrFile = 1;
			/* daca nu s-a gasit un director cu numele newname si exista fisiere in directorul parent, cauta si fisier cu numele newname */
			if (newnameAsDirOrFile == 0 && parent->head_children_files != NULL)
			{
				File *aux4 = parent->head_children_files;
				while (aux4->next != NULL)
				{
					if (strcmp(aux4->name, newname) == 0)
					{
						newnameAsDirOrFile = 1;
						break;
					}
					aux4 = aux4->next;
				}
				if (strcmp(aux4->name, newname) == 0)
					newnameAsDirOrFile = 1;
			}
			/* daca nu s-a gasit niciun director sau fisier cu numele newname in directorul parent, se poate aplica mv */
			if (newnameAsDirOrFile == 0)
			{
				rmdir(parent, oldname);
				mkdir(parent, newname);
				return;
			}
			/* daca s-a gasit un director sau fisier cu numele newname, nu se poate aplica mv */
			else
			{
				if (parent->head_children_files == NULL)
				{
					printf("File/Director already exists\n");
					free(oldname);
					free(newname);
					return;
				}
			}
		}
		/* daca nu s-a gasit un director cu numele oldname si nu exista fisiere in directorul parent, nu se poate aplica mv */
		else
		{
			if (parent->head_children_files == NULL)
			{
				printf("File/Director not found\n");
				free(oldname);
				free(newname);
				return;
			}
		}
	}
	if (parent->head_children_files != NULL)
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
				// free(oldname);
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
coding style, int i = 0, else { if, oldname si newname flag bool true si false
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