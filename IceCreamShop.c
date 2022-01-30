// Customer is data type which has name and age_group variables
// There are 4 different Customer Group, Elder, Adult, Child and DailyReport
// current_xx_number is holding active customer in the group
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE 10
#define MAX_SUM 100

typedef struct
{
	char name[15];
	char age_group[10];
}
Customer;

Customer elder_queue[MAX_QUEUE];
Customer adult_queue[MAX_QUEUE];
Customer children_queue[MAX_QUEUE];
Customer dailyReport[100];

int current_elder_number = 0;
int current_adult_number = 0;
int current_children_number = 0;
int current_daily_activity = 0;

void DailyReport()
{
	int i;
	FILE * fp;
	fp = fopen("output.txt", "w");
	if (fp != NULL)
	{
		for (i = current_daily_activity - 1; i >= 0; i--)
		{
			fprintf(fp, "%c\t%s \n", dailyReport[i].age_group[0], dailyReport[i].name);
		}
		fclose(fp);
	}
}

int deQueue(Customer arr[], int number_to_remove, int *current_number, char customer_age_group)
{
	int i, j;
	for (i = 0; i < number_to_remove; i++)
	{
		if (current_daily_activity > MAX_SUM)
		{
			return -1;
		}

		if (*current_number > 0)
		{
			dailyReport[current_daily_activity] = arr[0];

			for (j = 0; j<*current_number; j++)
			{
				arr[j] = arr[j + 1];
			}
			(*current_number) --;
		}
		else
		{
			Customer c;
			strcpy(c.name, "*****");
			strcpy(c.age_group, &customer_age_group);
			dailyReport[current_daily_activity] = c;
		}
		current_daily_activity++;
	}
	return 0;
}

void ServeCustomers(char *customer_age_group, int number_to_remove)
{
	switch (*customer_age_group)
	{
		case 'E':
			deQueue(elder_queue, number_to_remove, &current_elder_number, *customer_age_group);
			break;
		case 'A':
			deQueue(adult_queue, number_to_remove, &current_adult_number, *customer_age_group);
			break;
		case 'C':
			deQueue(children_queue, number_to_remove, &current_children_number, *customer_age_group);
			break;
	}
}

void NewCustomer(Customer c)
{
	switch (*c.age_group)
	{
		case 'E':
			if (current_elder_number > MAX_QUEUE)
			{
				return;
			}
			elder_queue[current_elder_number++] = c;
			break;
		case 'A':
			if (current_adult_number > MAX_QUEUE)
			{
				return;
			}
			adult_queue[current_adult_number++] = c;
			break;
		case 'C':
			if (current_children_number > MAX_QUEUE)
			{
				return;
			}
			children_queue[current_children_number++] = c;
			break;
	}
}

int main()
{
	FILE * fp;
	char command[15];
	char customer_age_group[1];
	char data[15];

	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("Could not open file");
		return 1;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s\t%c\t%s\n", command, customer_age_group, data);
		if (strcmp(command, "NewCustomer") == 0)
		{
			Customer c;
			strcpy(c.name, data);
			strcpy(c.age_group, customer_age_group);
			NewCustomer(c);
		}
		if (strcmp(command, "ServeCustomers") == 0)
		{
			int number_to_remove = atoi(data);
			ServeCustomers(customer_age_group, number_to_remove);
		}
	}
	DailyReport();

	fclose(fp);
	return 0;
}