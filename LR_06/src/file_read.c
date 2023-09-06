#include "../inc/file_read.h"

char *my_strdup(char *src)
{
	char *dst = calloc(strlen(src), sizeof(char));
	strcpy(dst, src);
	return dst;
}

char *read_word(FILE *file)
{
	char word1[MAX_WORD_LEN] = { 0 }, *word2;
	int rc;
	rc = fscanf(file, "%999s", word1);
	if (rc != 1)
		return NULL;
	word2 = my_strdup(word1);
	return word2;
}

int get_file_size(char *filename)
{
	char buf[MAX_WORD_LEN] = { 0 };

	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return 0;

	int rc, size = 0;

	while (!feof(file))
	{
		rc = fscanf(file, "%999s", buf);
		if (rc != 1)
			break;
		size++;
	}
	fclose(file);
	return size;
}

int read_file(char *filename, data_array_t *data)
{
	int size;
	size = get_file_size(filename);

	data->pointers = calloc(size, sizeof(char *));
	data->len = size;

	FILE *file = fopen(filename, "r");
	int i = 0;
	for (char **cur = data->pointers; cur < data->pointers + data->len; cur++, i++)
	{
		*cur = read_word(file);
		//if (*cur == NULL)
		//	break;
		*(data->pointers + i) = *cur;
	}
	fclose(file);
	return OK;
}

void output_data(data_array_t data)
{
	for (char **cur = data.pointers; cur < data.pointers + data.len; cur++)
	{
		printf("%s, ", *cur);
	}
	printf("\n");
}
