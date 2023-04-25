/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:07:46 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/25 14:14:37 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_arg
{
	int				philos;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				n_eat;
	int				check;
	pthread_mutex_t	mutex1;
	pthread_mutex_t	mutex2;
	pthread_mutex_t	mutex3;
}	t_arg;

typedef struct s_philo
{
	int		id;
	long	last_eat;
	long	start_time;
	void	*right_fork;
	void	*left_fork;
	int		check;
	t_arg	*arg;
}	t_philo;

typedef struct s_array
{
	pthread_mutex_t	*mutex;
	pthread_t		*threads;
	t_philo			*philos;
}	t_array;

void	ft_sleep(int time);
int		ft_atoi(char *str);
int		ft_check_args(int ac, char **av, t_arg *arg);
void	ft_create(t_array *arr, t_arg *arg);
void	ft_init_mutex(t_array *arr, t_arg *arg);
int		ft_died(t_array *arr, t_arg *arg);
long	ft_time(void);
void	ft_destroy(t_array *arr, t_arg *arg);
void	ft_join(t_array *arr, t_arg *arg);
void	*ft_thread(void *void_philo);
void	ft_free(t_array *arr, t_arg *arg);

#endif