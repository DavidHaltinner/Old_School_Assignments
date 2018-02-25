copy (old, new);
	int old, new;
{
	int count;
	while ((count = read(old, buffer, sizeof(buffer))) > 0)
		write (new, buffer, count);
}

