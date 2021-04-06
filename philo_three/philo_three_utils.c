/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:49:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/07 01:21:51 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		milisec;

	gettimeofday(&time, NULL);
	milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milisec);
}

int			ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] || !s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
