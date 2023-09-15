#include "image.h"

void	put_background(t_image *destination, const t_image *source)
{
	register const unsigned int	*dest_end
		= destination->address + destination->height * destination->width;
	register unsigned int		*dest_curr;
	register unsigned int		*source_curr;

	source_curr = source->address;
	dest_curr = destination->address;
	while (dest_curr < dest_end)
		*dest_curr++ = *source_curr++;
}
