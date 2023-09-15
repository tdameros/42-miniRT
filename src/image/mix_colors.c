unsigned int	mix_colors(const unsigned int added_color,
					const unsigned int base_color)
{
	const unsigned int	added_color_transparency = added_color >> 24;
	float				inverse_transparency;
	float				transparency;

	if (added_color_transparency == 255)
		return (base_color);
	if (added_color_transparency == 0)
		return (added_color);
	inverse_transparency = added_color_transparency / 255.f;
	transparency = 1.f - inverse_transparency;
	return (((unsigned int)(transparency * ((added_color & 0x00FF0000) >> 16)
			+ inverse_transparency * ((base_color & 0x00FF0000) >> 16)))
					<< 16
			| ((unsigned int)(transparency * ((added_color & 0x0000FF00) >> 8)
				+ inverse_transparency * ((base_color & 0x0000FF00) >> 8)))
					<< 8
			| (unsigned int)(transparency * (added_color & 0x000000FF)
				+ inverse_transparency * (base_color & 0x000000FF)));
}
