/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:44:27 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/20 18:24:08 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time()
{
	struct timeval 	time;
	long x;
	gettimeofday(&time, NULL);
	x = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (x);
}

void ft_destroy(t_array *arr, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->philos)
	{
		pthread_mutex_destroy(&arr->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->mutex1);
	pthread_mutex_destroy(&arg->mutex2);
	pthread_mutex_destroy(&arg->mutex3);
}

void ft_join(t_array *arr, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->philos)
	{
		pthread_join(arr->threads[i], NULL);
		i++;
	}
}

void ft_free(t_array *arr, t_arg *arg)
{
	ft_destroy(arr, arg);
	free(arr->mutex);
	free(arr->philos);
	free(arr->threads);
}

int main(int ac, char **av)
{
	t_array 		arr;
	t_arg			arg;
	
	if (ft_check_args(ac, av, &arg))
		return (1);
	ft_init_mutex(&arr, &arg);
	ft_create(&arr, &arg);
	if (ft_died(&arr, &arg) == 1)
	{
		ft_free(&arr, &arg);
		return (0);
	}
	ft_join(&arr, &arg);
	ft_free(&arr, &arg);
	return (0);
}
