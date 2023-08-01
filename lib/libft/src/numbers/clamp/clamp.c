int	ft_clamp(const int nb, const int min, const int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
