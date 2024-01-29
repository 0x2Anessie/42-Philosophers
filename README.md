# Philosophers

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation.

## Running Tests

The program takes four to five arguments : 
- The number of philosophers
- The time a philosopher will die if he doesn’t eat
- The time it takes a philosopher to eat
- The time it takes a philosopher to sleep
- *Number of times all the philosophers need to eat before terminating the program

*optional argument

This test will create an infinity loop because every philosopher will have the time to eat so none of them will die.
To compile and run tests, run the following commands :

```bash
  $> make
  $> ./philo 5 800 200 200
```

## External functions used

[pthread_create](http://manpagesfr.free.fr/man/man3/pthread_create.3.html) : creates a new thread running concurrently with the calling thread.

[pthread_join](http://manpagesfr.free.fr/man/man3/pthread_join.3.html) : suspends the execution of the calling thread until the thread identified by th completes its execution.

[pthread_mutex_init](http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html) : initializes the mutex pointed to by mutex according to the mutex attributes specified by mutexattr . If mutexattr is NULL, the default parameters are used.

[pthread_mutex_lock](http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html) : locks the mutex.

[pthread_mutex_unlock](http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html) : unlocks the mutex.

[pthread_mutex_destroy](http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html) : destroys a mutex, freeing the resources it holds.

### Documentation

[To learn more about the Dining Philosopher Problem](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

