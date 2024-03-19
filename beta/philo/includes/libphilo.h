/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:08:46 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 14:10:49 by dzuiev           ###   ########.fr       */
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

// Bold
# define BLD "\033[1m"

// Foreground Colors
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

// structures

typedef struct s_data t_data;

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx			mutex;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_counter;
	bool			full;
	long			last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_data			*data;
}				t_philo;

struct s_data
{
	long			philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	bool			end_flag; // philo died or all philos are full
	int				meals_limit; // optional [5] || FLAF if not set 
	t_philo			*philos;
	t_fork			*forks;
};

// ft_free_utils.c
void			ft_free_3d_array(void ****array);
void			ft_free_2d_array(void ***array);
void			ft_free_ptr(void **ptr);

// utils.c
void			ft_error(char *error_msg, int exit_code);

#endif
