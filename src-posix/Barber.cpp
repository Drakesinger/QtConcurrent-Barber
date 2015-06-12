/***
Author: Horia Mut
*/

#define NB_CLIENTS	10
#define NB_PLACES	5

#include "stdafx.h"
#include <pthread.h>
#include <semaphore.h>

// http://en.wikipedia.org/wiki/Sleeping_barber_problem

// Threads.
void *BarberThread(void *arg);
void *ClientThread(void *arg);

// Waiting room.
int AvailablePlaces = NB_PLACES;

// Semaphore to say that the barber is ready.
sem_t SemBarberReady;

// Semaphore to say that the client is ready.
sem_t SemClientReady;

// Semaphore for access to global value AvailablePlaces.
sem_t SemAccesAvailablePlaces;

int barber()
{
	// Initialize Semaphores
	sem_init(&SemBarberReady, 0, 0);		// Barber is not ready.
	sem_init(&SemClientReady, 0, 0);		// Client is not ready.
	sem_init(&SemAccesAvailablePlaces, 0, 1);	// Access possible to the AvailablePlaces value for one thread.

	pthread_t TBarber;

	if (pthread_create(&TBarber, NULL, BarberThread, (void*)0) != 0)
	{
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	pthread_t TClients[NB_CLIENTS];
	int i = 0;
	for (i = 0; i < NB_CLIENTS; ++i)
	{
		if (pthread_create(&TClients[i], NULL, ClientThread, (void*)(i + 1)) != 0)
		{
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	for (i = 0; i < NB_CLIENTS; ++i)
	{
		pthread_join(TClients[i], NULL);
	}
	pthread_join(TBarber, NULL);

	return EXIT_SUCCESS;
}

// Barber thread task.
void *BarberThread(void *arg)
{
	while (true)
	{
		// Wait for a client to be ready.
		sem_wait(&SemClientReady);

		// Lock the access to AvailablePlaces. No more clients can come in.
		sem_wait(&SemAccesAvailablePlaces);

		// Barber is in charge of a client.
		// Increment the number of available places.
		++AvailablePlaces;
		printf("Barber is in charge of a client. \n");

		// Unlock access to AvailablePlaces. Clients can now come in again.
		sem_post(&SemAccesAvailablePlaces);

		// Barber is ready.
		sem_post(&SemBarberReady);

		// Barber is working.
		printf("Barber is working. \n\n");
		Sleep(20);
	}

	return NULL;
}

// Client thread task.
void *ClientThread(void *arg)
{
	int clientID = (int)arg;

	// Lock access to AvailablePlaces to avoid writing at the same time.
	sem_wait(&SemAccesAvailablePlaces);

	printf("Client %d came in. \n", clientID);

	// Check if there are any available places to sit down.
	if (AvailablePlaces > 0)
	{
		// Client sits down.
		--AvailablePlaces;
		printf("Client %d sits down. \n", clientID);

		// Unlock access to AvailablePlaces. No longer using it.
		sem_post(&SemAccesAvailablePlaces);

		// Client is ready.
		sem_post(&SemClientReady);
		printf("Client %d is ready and waits for the barber. \n\n", clientID);

		// Client waits for the barber to be ready.
		sem_wait(&SemBarberReady);
		printf("Client %d is taken care of by the barber. Sweeny Todd. \n\n", clientID);
	}
	// No more room. Client goes home.
	else
	{
		printf("Client %d goes home. Waiting room is full. \n\n", clientID);

		// Unlock access to AvailablePlaces. No longer using it.
		sem_post(&SemAccesAvailablePlaces);
	}

	return NULL;
}