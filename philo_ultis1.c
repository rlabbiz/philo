/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ultis1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:00:39 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/04/25 14:30:23 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->id % 2 != 0)
		usleep(20000);
	while (1)
	{
		pthread_mutex_lock(&philo->arg->mutex3);
		printf("%ld %d is thinking\n", (ft_time()
				- philo->start_time), philo->id);
		pthread_mutex_unlock(&philo->arg->mutex3);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->arg->mutex3);
		printf("%ld %d has taken a fork\n", (ft_time()
				- philo->start_time), philo->id);
		pthread_mutex_unlock(&philo->arg->mutex3);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->arg->mutex3);
		printf("%ld %d has taken a fork\n", (ft_time()
				- philo->start_time), philo->id);
		pthread_mutex_unlock(&philo->arg->mutex3);
		pthread_mutex_lock(&philo->arg->mutex3);
		printf("%ld %d is eating\n", ft_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->arg->mutex3);
		pthread_mutex_lock(&philo->arg->mutex2);
		philo->last_eat = ft_time();
		pthread_mutex_unlock(&philo->arg->mutex2);
		ft_sleep(philo->arg->t_eat);
		pthread_mutex_lock(&philo->arg->mutex1);
		philo->check++;
		pthread_mutex_unlock(&philo->arg->mutex1);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->arg->mutex3);
		printf("%ld %d is sleeping\n", ft_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->arg->mutex3);
		ft_sleep(philo->arg->t_sleep);
	}
	return (NULL);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}

void	ft_sleep(int time)
{
	long	start;

	start = ft_time();
	while (ft_time() - start < time)
		usleep(500);
}
