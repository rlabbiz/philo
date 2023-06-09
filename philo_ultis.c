/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ultis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:07:50 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/25 11:09:24 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(int ac, char **av, t_arg *arg)
{
	if (ac >= 5)
	{
		arg->philos = ft_atoi(av[1]);
		arg->t_die = ft_atoi(av[2]);
		arg->t_eat = ft_atoi(av[3]);
		arg->t_sleep = ft_atoi(av[4]);
		arg->check = 0;
		if (ac == 6)
			arg->n_eat = ft_atoi(av[5]);
		else
			arg->n_eat = -1;
		return (0);
	}
	else
		return (1);
}

void	ft_create(t_array *arr, t_arg *arg)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = ft_time();
	while (i < arg->philos)
	{
		arr->philos[i].check = 0;
		arr->philos[i].id = i + 1;
		arr->philos[i].start_time = start_time;
		arr->philos[i].last_eat = start_time;
		pthread_create(&arr->threads[i], NULL, &ft_thread, &arr->philos[i]);
		i++;
	}
}

void	ft_init_mutex(t_array *arr, t_arg *arg)
{
	int	i;

	i = 0;
	arr->philos = malloc(sizeof(t_philo) * arg->philos);
	arr->mutex = malloc(sizeof(pthread_mutex_t) * arg->philos);
	arr->threads = malloc(sizeof(pthread_t) * arg->philos);
	while (i < arg->philos)
	{
		pthread_mutex_init(&arr->mutex[i], NULL);
		arr->philos[i].right_fork = &arr->mutex[i];
		arr->philos[i].left_fork = &arr->mutex[(i + 1) % arg->philos];
		arr->philos[i].arg = arg;
		i++;
	}
	pthread_mutex_init(&arg->mutex1, NULL);
	pthread_mutex_init(&arg->mutex2, NULL);
	pthread_mutex_init(&arg->mutex3, NULL);
}

static void	ft_died_supp(t_array *arr, t_arg *arg, int *i, int *n)
{
	pthread_mutex_lock(&arg->mutex1);
	if (arg->n_eat != -1 && arr->philos[*i].check >= arg->n_eat)
		*n += 1;
	pthread_mutex_unlock(&arg->mutex1);
	*i += 1;
}

int	ft_died(t_array *arr, t_arg *arg)
{
	int	i;
	int	n;

	while (1)
	{
		i = 0;
		n = 0;
		while (i < arg->philos)
		{
			pthread_mutex_lock(&arg->mutex2);
			if ((ft_time() - arr->philos[i].last_eat) > arg->t_die)
			{
				pthread_mutex_unlock(&arg->mutex2);
				pthread_mutex_lock(&arg->mutex3);
				printf("%ld %d is died\n", (ft_time()
						- arr->philos[i].start_time), arr->philos[i].id);
				return (1);
			}
			pthread_mutex_unlock(&arg->mutex2);
			ft_died_supp(arr, arg, &i, &n);
		}
		if (n == arg->philos)
			return (1);
	}
}
