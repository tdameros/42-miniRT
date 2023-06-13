int	ft_get_smallest_int(int a, int b)
{
	return (a * (a < b) + b * (a >= b));
}
