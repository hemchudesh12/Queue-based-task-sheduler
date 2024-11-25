#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure for a task
typedef struct {
	char name[20]; // Task name
	int priority; // Task priority
} Task;

// Define the structure for a queue
typedef struct Queue {
	Task *tasks; // Array of tasks
	int front; // Front of the queue
	int rear; // Rear of the queue
	int size; // Size of the queue
} Queue;

// Function to create a new queue
Queue *createQueue(int size) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->tasks = (Task *)malloc(size * sizeof(Task));
	q->front = 0;
	q->rear = 0;
	q->size = size;
	return q;
}

// Function to add a task to the queue
void enqueue(Queue *q, Task task) {
	if (q->rear == q->size) {
		printf("Queue is full. Cannot add more tasks.\n");
		return;
	}
	q->tasks[q->rear] = task;
	q->rear = (q->rear + 1) % q->size;
}

// Function to remove a task from the queue
Task dequeue(Queue *q) {
	if (q->front == q->rear) {
		printf("Queue is empty. Cannot remove tasks.\n");
		return (Task){.name = "", .priority = 0};
	}
	Task task = q->tasks[q->front];
	q->front = (q->front + 1) % q->size;
	return task;
}

// Function to print the tasks in the queue
void printQueue(Queue *q) {
	int i = q->front;
	printf("Tasks in the queue: \n");
	while (i != q->rear) {
		printf("Task: %s, Priority: %d\n", q->tasks[i].name, q->tasks[i].priority);
		i = (i + 1) % q->size;
	}
}

// Function to add a task with user input and auto-generate priority
void addTask(Queue *q) {
	Task task;
	printf("Enter task name: ");
	scanf("%s", task.name);
	// Auto-generate priority
	int priority = rand() % 10 + 1; // Random number between 1 and 10
	task.priority = priority; // Set priority
	enqueue(q, task);
	printf("Task added successfully! Your task '%s' has been assigned priority %d.\n", task.name, task.priority);
}

// Function to delete a task with user input
void deleteTask(Queue *q) {
	char name[20];
	printf("Enter task name: ");
	scanf("%s", name);
	int found = 0;
	for (int i = q->front; i != q->rear; i = (i + 1) % q->size) {
		if (strcmp(q->tasks[i].name, name) == 0) {
			dequeue(q);
			found = 1;
			printf("Task deleted successfully! Your task '%s' has been deleted.\n",name);
			break;
		}
	}
	if (!found) {
		printf("Task not found.\n");
	}
}

// Function to search for a task with user input
void searchTask(Queue *q) {
	char name[20];
	printf("Enter task name: ");
	scanf("%s", name);
	int found = 0;
	for (int i = q->front; i != q->rear; i = (i + 1) % q->size) {
		if (strcmp(q->tasks[i].name, name) == 0) {
			printf("Task found: %s, Priority: %d\n", q->tasks[i].name, q->tasks[i].priority);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Task not found.\n");
	}
}

// Function to select which feature to use
void selectFeature(Queue *q) {
	int choice;
	printf("Select an option:\n");
	printf("1. Add task\n");
	printf("2. Delete task\n");
	printf("3. Search task\n");
	printf("4. Print tasks\n");
	printf("5. Exit\n");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			addTask(q);
			break;
		case 2:
			deleteTask(q);
			break;
		case 3:
			searchTask(q);
			break;
		case 4:
			printQueue(q);
			break;
		case 5:
			exit(0); // Exit the program
		break;
		default:
			printf("Invalid option.\n");
			break;
	}
}

int main() {
	int size;
	printf("Enter the size of the queue: ");
	scanf("%d", &size);
	srand(time(0)); // Seed random number generator
	Queue *q = createQueue(size); // Create a queue with the specified size
	while (1) {
		selectFeature(q);
		printf("Press Enter to continue...");
		printf("\n"); // Print a newline for readability
	}
	return 0;
}