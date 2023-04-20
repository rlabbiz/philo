/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ultis1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:39 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/20 21:26:47 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_thread(void *void_philo)
{
	t_philo *philo = (t_philo *)void_philo;
    
	if (philo->id % 2 != 0)
		usleep(200);
	while (1)
	{
		printf("%ld %d is thinking\n", ft_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", ft_time() - philo->start_time, philo->id);
		pthread_mutex_lock(&philo->arg->mutex2);
		philo->last_eat = ft_time();
		pthread_mutex_unlock(&philo->arg->mutex2);
		printf("%ld %d is eating\n", ft_time() - philo->start_time, philo->id);
		usleep(philo->arg->t_eat * 1000);
        pthread_mutex_lock(&philo->arg->mutex1);
        philo->check++;
        pthread_mutex_unlock(&philo->arg->mutex1);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->id);
		usleep(philo->arg->t_sleep * 1000);
	}
	return (NULL);
}