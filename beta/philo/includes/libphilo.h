/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:08:46 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/20 18:37:23 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

// write , usleep
# include <unistd.h>

// malloc, free
# include <stdlib.h>

// printf
# include <stdio.h>

// true, false
# include <stdbool.h>

// pthread: create, join, detach; mutex: init, destroy, lock, unlock
# include <pthread.h>

// gettimeofday
# include <sys/time.h>

// INT_MAX, INT_MIN
# include <limits.h>

// errno
# include <errno.h>

/* ************************************************************************** */
/*                                                                            */
/*    Для использования функций из Libft необходимо включить                  */
/*    заголовочный файл "../libft/libft.h".                                   */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

// Reset
# define RST "\033[0m"

#ifndef MAX_PHILOS
# define MAX_PHILOS 200
#endif

// states of philosofer
typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	TOOK_FIRST_FORK,
	TOOK_SECOND_FORK,
	FULL
}				t_philo_state;

// operation codes for threads and mutexes
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	CREATE,
	DESTROY,
	DETACH,
	JOIN,
}				t_opcode;

// Bold
# define BLD "\033[1m"
// Foreground Colors
# define BLK "\033[1;30m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

// structures
typedef struct s_data t_data;

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx			mtx;
	int				id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mtx			philo_mtx;
	pthread_t		thread_id;
	t_data			*data;
}				t_philo;

struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit; // optional [5] || FLAF if not set 
	long			philo_nbr;
	long			start_time;
	bool			threads_created;
	bool			end_process; // philo died or all philos are full
	t_philo			*philos;
	t_fork			*forks;
	t_opcode		*code;
};

// parse_input_args.c
void			parse_input_args(t_data *data, int argc, char **argv);

// ft_free_utils.c
void			cleanup(t_data *data, char *error_msg, int exit_code);
void			ft_free_3d_array(void ****array);
void			ft_free_2d_array(void ***array);
void			ft_free_ptr(void **ptr);

// utils.c
void			ft_error(char *error_msg, int exit_code);
void			*ft_malloc(t_data *data, size_t bytes);

// mutex_utils.c
void			ft_mutex_handle(t_mtx *mtx, t_opcode code, t_data *data);

// thread_utils.c
void			ft_thread_handle(pthread_t *thread, void *(*func)(void *),
					void *data, t_opcode code);

#endif
