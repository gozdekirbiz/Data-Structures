/*Odevde Doubly Circular Linked List kullandim.Ileri ve geri gitme islemlerinin bulundugu node structimdan iki tane(head ve tail) olusturdum.
Bu sayede calma listesinde ileri-geri ile beraber en bastan en sona gidebilme islemlerini yapmis oldum.
Calan sarkilarin kaydini tutabilmek icin bir adet pointer kullandim.Boylece PlaySonga bagli fonksiyonlarin kontrolunu yapmis oldum.
Inputlari alabilmek için data adinda bir struct olusturdum ve inputlari satir satir fgets ile alarak tab karakterine gore parcaladim.
Gozde KIRBIZ 191180053*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	struct node* prev;
	struct node* next;
	char data[60];
};
struct data
{
	char name1[60];
	char name2[60];
};
struct node* head;
struct node* tail;
static struct node* iterator;
static int playcount;
void MoveSong(char place, char song1[60], char song2[60]);
void insert_atBeginning(char song[60]);
void insert_End(char song[60]);
void insert_position(char song[60], int position);
void deletesong(char song[60], int control);
void insertattheend(char song[60]);
void insertbeginning(char song[60]);
void print_listforward();
void print_listbackward();
int getListLength();
void openthefile();
void ReversePlaylist();
void PlaySong(char place);
int findposition(char song[60]);
void openthefile()
{
	FILE* fp;
	char str[100];
	int count = 0;
	int i = 0;
	fp = fopen("input.txt", "r");
	while (fgets(str, sizeof(str), fp) != NULL)
	{
		int len = strlen(str);
		str[len - 1] = '\0';
		char* tokenArray[100];
		tokenArray[0] = strtok(str, "\t");
		for (i = 1; i < 200; i++)
		{
			if ((tokenArray[i] = strtok(NULL, "\t")) == NULL)
				break;
		}
		count = i;
		if (strcmp(tokenArray[0], "InsertSong") == 0)
		{
			if (strcmp(tokenArray[1], "H") == 0)
			{
				struct data Data;
				strcpy(Data.name1, tokenArray[2]);
				insert_atBeginning(Data.name1);
			}
			else if (strcmp(tokenArray[1], "T") == 0)
			{
				struct data Data;
				strcpy(Data.name1, tokenArray[2]);
				insert_End(Data.name1);
			}
		}
		else if (strcmp(tokenArray[0], "RemoveSong") == 0)
		{
			struct data Data;
			strcpy(Data.name1, tokenArray[1]);
			deletesong(Data.name1, 0);
		}
		else if (strcmp(tokenArray[0], "ReversePlaylist") == 0)
		{
			ReversePlaylist(&head);

		}
		else if (strcmp(tokenArray[0], "MoveSong") == 0)
		{
			struct data Data;
			strcpy(Data.name1, tokenArray[2]);
			strcpy(Data.name2, tokenArray[3]);
			if (strcmp(tokenArray[1], "B") == 0)
				MoveSong('B', Data.name1, Data.name2);
			else if (strcmp(tokenArray[1], "A") == 0)
				MoveSong('A', Data.name1, Data.name2);
		}
		else if (strcmp(tokenArray[0], "PlaySong") == 0)
		{
			if (strcmp(tokenArray[1], "N") == 0)
				PlaySong('N');
			else if (strcmp(tokenArray[1], "P") == 0)
				PlaySong('P');
		}
		else if (strcmp(tokenArray[0], "PrintPlaylist") == 0)
		{
			if (strcmp(tokenArray[1], "F") == 0)
				print_listforward();
			else if (strcmp(tokenArray[1], "R") == 0)
				print_listbackward();
		}
		else
			printf("%s Unknown command", tokenArray[0]);
	}fclose(fp);
}
int getListLength()
{
	if (head == NULL) return 0;
	int count = 0;
	struct node* current = head;
	do
	{
		count++;
		current = current->next;
	} while (current != head);
	return count;
}
void print_listforward()
{
	FILE* fp;
	fp = fopen("output.txt", "a");
	struct node* ptr;
	ptr = head;
	if (head == NULL)
	{
		fprintf(fp, "No Songs to Print\n");
		fprintf(fp, "*****\n");
	}
	else
	{
		while (ptr->next != head)
		{
			fprintf(fp, "%s\n", ptr->data);
			ptr = ptr->next;
		}
		fprintf(fp, "%s\n", ptr->data);
		fprintf(fp, "*****\n");
	}
}
void print_listbackward()
{
	FILE* fp;
	fp = fopen("output.txt", "a");
	if (head == NULL)
	{
		fprintf(fp, "No Songs to Print\n");
		fprintf(fp, "*****\n");
	}
	else
	{
		struct node* current = head->prev;
		struct node* temp;
		temp = current;
		while (temp->prev != current)
		{
			fprintf(fp, "%s\n", temp->data);
			temp = temp->prev;
		}
		fprintf(fp, "%s\n", temp->data);
		fprintf(fp, "*****\n");
	}
}
int findposition(char song[60])
{
	struct node* current = head;
	int i = 1;
	do
	{
		if (strcmp(current->data, song) == 0)
			break;
		current = current->next;
		i++;
	} while (current != head);
	return i;
}
void insert_atBeginning(char song[60])
{
	struct node* newSong = (struct node*)malloc(sizeof(struct node));
	strcpy(newSong->data, song);
	newSong->next = newSong;
	newSong->prev = newSong;
	if (head == NULL)
	{
		head = newSong;
		tail = newSong;
	}
	else
	{
		newSong->next = head;
		newSong->prev = tail;
		head->prev = newSong;
		tail->next = newSong;
		head = newSong;
	}
}
void insert_End(char song[60])
{
	struct node* newSong = (struct node*)malloc(sizeof(struct node));
	strcpy(newSong->data, song);
	newSong->next = newSong;
	newSong->prev = newSong;
	if (head == NULL)
	{
		head = newSong;
		tail = newSong;
	}
	else
	{
		tail->next = newSong;
		newSong->next = head;
		newSong->prev = tail;
		tail = newSong;
		head->prev = tail;
	}
}
void insert_position(char song[60], int position)
{
	if (head != NULL)
	{
		struct node* current = head;
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		int count = 0;
		do
		{
			count++;
			temp = current;
			current = current->next;
		} while (current->next != head && count < position - 1);
		if (count == position - 1)
		{
			if (temp == tail)
				insert_End(song);
			else
			{
				struct node* newNode = (struct node*)malloc(sizeof(struct node));
				strcpy(newNode->data, song);
				temp->next = newNode;
				newNode->next = current;
				newNode->prev = temp;
				current->prev = newNode;
			}
			return;
		}
	}
	else
		return;
}
void insertbeginning(char song[60])
{
	struct node *ptr, *temp;
	ptr = (struct node*)malloc(sizeof(struct node));
	strcpy(ptr->data,song);
	if (head == NULL)
	{
		head = ptr;
		ptr->next = head;
		ptr->prev = head;
	}
	else
	{
		temp = head;
		while (temp->next != head)
		{
			temp = temp->next;
		}
		temp->next = ptr;
		ptr->prev = temp;
		head->prev = ptr;
		ptr->next = head;
		head = ptr;
	}
}
void insertattheend(char song[60])
{
	struct node* ptr, * temp;
	ptr = (struct node*) malloc(sizeof(struct node));
	strcpy(ptr->data,song);
	if (head == NULL)
	{
		head = ptr;
		ptr->next = head;
		ptr->prev = head;
	}
	else
	{
		temp = head;
		while (temp->next != head)
		{
			temp = temp->next;
		}
		temp->next = ptr;
		ptr->prev = temp;
		head->prev = ptr;
		ptr->next = head;
	}
}
void deletefirstsong()
{
	struct node* temp;
	if (head == NULL)
		return;
	else if (head->next == head)
	{
		head = NULL;
		free(head);
	}
	else
	{
		temp = head;
		while (temp->next != head)
		{
			temp = temp->next;
		}
		temp->next = head->next;
		head->next->prev = temp;
		free(head);
		head = temp->next;
	}
}
void deletelastsong()
{
	if (head == NULL)  return;
	struct node* temp = head;
	struct node* current = head;
	while (current->next != head)
	{
		temp = current;
		current = current->next;
	}
	temp->next = head;
	tail = temp;
	head->prev = tail;
	free(current);
}
void deletesong(char song[60], int control)
{
	int position = findposition(song);
	if (iterator != NULL && control == 0)
	{
		if (strcmp(iterator->data, song) != 0) //if song isnt playing at the moment
		{
			if (position == 1) //first song
			{
				deletefirstsong();
				return;
			}
			struct node* current = head;
			struct node* temp;
			int count = 0;
			do
			{
				count++;
				temp = current;
				current = current->next;
			} while (current->next != head && count < position - 1);
			if (count == position - 1)
			{
				if (current == tail)
				{
					deletelastsong();
					return;
				}
				temp->next = current->next;
				current->next->prev = temp;
				free(current);
				return;
			}
		}
		else
		{
			FILE* fp;
			fp = fopen("output.txt", "a");
			fprintf(fp, "Cannot Remove The Playing Song\n*****\n");
		}
	}
	else if (iterator != NULL && control != 0)
	{
		if (position == 1) //first song
		{
			deletefirstsong();
			return;
		}
		struct node* current = head;
		struct node* temp;
		int count = 0;
		do
		{
			count++;
			temp = current;
			current = current->next;
		} while (current->next != head && count < position - 1);
		if (count == position - 1)
		{
			if (current == tail)
			{
				deletelastsong();
				return;
			}
			temp->next = current->next;
			current->next->prev = temp;
			free(current);
			return;
		}
	}
	else if (iterator == NULL)
	{
		if (position == 1) //first song
		{
			deletefirstsong();
			return;
		}
		struct node* current = head;
		struct node* temp;
		int count = 0;
		do
		{
			count++;
			temp = current;
			current = current->next;
		} while (current->next != head && count < position - 1);
		if (count == position - 1)
		{
			if (current == tail)
			{
				deletelastsong();
				return;
			}
			temp->next = current->next;
			current->next->prev = temp;
			free(current);
			return;
		}
	}
}
void ReversePlaylist()
{
	if (head != NULL)
	{
		struct node* cur = head, * nextt, * temp;
		do
		{
			nextt = cur->next;
			temp = cur->prev;
			cur->prev = cur->next;
			cur->next = temp;
			cur = nextt;
		} while (cur != head);
		head = head->next;
	}
}
void MoveSong(char place, char songtomove[60], char songref[60])
{
	if (place == 'B')
	{
		if (iterator != NULL)
		{
			if (strcmp(songtomove, iterator->data) == 0)
			{
				iterator = head;
				int i;
				int nodeplace = findposition(songref);
				if (nodeplace == 1)
				{
					iterator = head;
					deletesong(songtomove, 1);
					insertbeginning(songtomove);
					iterator = iterator->prev;
				}
				else
				{
					deletesong(songtomove, 1);
					insert_position(songtomove, nodeplace);
					for (i = 1; i < nodeplace; i++)
					{
						iterator = iterator->next;
					}
					//printf("%s", iterator->data);
				}
			}
			else
			{
				int nodeplace = findposition(songref);
				if (nodeplace == 1)
				{
					deletesong(songtomove, 1);
					insertbeginning(songtomove);
				}
				else
				{
					deletesong(songtomove, 1);
					insert_position(songtomove, nodeplace);
				}
			}
		}
		else
		{
			int nodeplace = findposition(songref);
			if (nodeplace == 1)
			{
				deletesong(songtomove, 1);
				insert_position(songtomove, nodeplace);
			}
			else
			{
				deletesong(songtomove, 1);
				insert_position(songtomove, nodeplace);
			}
		}
		
	}
	else if (place == 'A')
	{
		int length = getListLength();
		if (iterator != NULL)
		{
			if (strcmp(songtomove, iterator->data) == 0)
			{
				iterator = head;
				int i;
				deletesong(songtomove, 1);
				int nodeplace = findposition(songref) + 1;
				if (nodeplace == length)
				{
					insertattheend(songtomove);
					for (i = 1; i < findposition(songref) + 1; i++)
						iterator = iterator->next;
				}
				else
				{
					insert_position(songtomove, nodeplace);
					for (i = 1; i < findposition(songref) + 1; i++)
						iterator = iterator->next;
					printf("%s", iterator->data);
				}
			}
			else
			{
				int nodeplace = findposition(songref);
				if (nodeplace == length)
				{
					deletesong(songtomove, 1);
					insertattheend(songtomove);
				}
				else
				{
					deletesong(songtomove, 1);
					insert_position(songtomove, nodeplace);
				}
			}
		}
		else
		{
			deletesong(songtomove, 1);
			int nodeplace = findposition(songref) + 1;
			if (nodeplace == length)
				insertattheend(songtomove);
			else
				insert_position(songtomove, nodeplace);
		}
	}
}
void PlaySong(char place)
{
	FILE* fp;
	fp = fopen("output.txt", "a");
	int length = getListLength();
	struct node* curr;
	if (head == NULL)
	{
		fprintf(fp, "No Songs to Play\n*****\n");
	}
	else
	{
		if (playcount == 0)
		{
			if (place == 'N')
			{
				iterator = head;
				fprintf(fp, "Playing %s\n", iterator->data);
				fprintf(fp, "******\n");
				playcount = playcount + 1;
			}
			else if (place == 'P')
			{
				iterator = tail;
				fprintf(fp, "Playing %s\n", iterator->data);
				fprintf(fp, "******\n");
				playcount = playcount + 1;
			}
		}
		else if (playcount != 0)
		{
			if (place == 'N')
			{
				iterator = iterator->next;
				fprintf(fp, "Playing %s\n", iterator->data);
				fprintf(fp, "******\n");
			}
			else if (place == 'P')
			{
				iterator = iterator->prev;
				fprintf(fp, "Playing %s\n", iterator->data);
				fprintf(fp, "******\n");
			}
		}
	}
}
int main()
{
	openthefile();
	return 0;
}