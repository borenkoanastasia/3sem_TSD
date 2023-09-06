#include "../inc/help_functions.h"
#include "../inc/tree_work.h"

// ОБЩИЙ СПИСОК СЛОВ

//Создание
int add_data_node(data_node_t **list, char *word)
{
	data_node_t *new_node = calloc(1, sizeof(data_node_t *));
	if (!new_node)
	{
		printf("Не удалось выделить память под узел списка слов\n");
		return ERR_CREATE;
	}
	new_node->data = word;
	new_node->next = NULL;
	if (!(*list))
	{
		*list = new_node;
		return OK;
	}
	data_node_t *cur = *list;
	for (; cur->next; cur = cur->next);
	cur->next = new_node;
	return OK;
}

// Очищение
void free_data(data_node_t **list)
{
	if (*list == NULL)
	{
		free(*list);
		return;
	}
	for (data_node_t *cur = (*list)->next; cur->next; cur = cur->next)
	{
		free(*list);
		*list = cur;
	}
	free(*list);
}

// Вывод
void output_data(data_node_t *list)
{
	printf("Список слов: ");
	if (list == NULL)
	{
		printf("Пуст\n");
		return;
	}
	printf("%s, ", list->data);
	for (data_node_t *cur = (list)->next; cur; cur = cur->next)
	{
		printf("%s, ", cur->data);
	}
	printf("\n");
}

// Получить размер хранилища
int get_data_size(data_node_t *data)
{
	int i = 0;
	for (data_node_t *cur = data; cur; cur = cur->next)
		i++;
	return i;
}

// Получить слово по индексу
char *get_data_word(data_node_t *data, int pos)
{
	data_node_t *cur = data;
	for (int i = 0; i < pos; i++)
		cur = cur->next;
	return cur->data;
}

// Сортировка данных
void sort_data(data_node_t **data, data_node_t **result)
{
	data_node_t *parent = NULL, *node = *data;
	int size = get_data_size(*data);
	for (int i = 0; i < size; i++)
	{
		parent = NULL, node = *data;
		for (data_node_t *cur2 = *data; cur2->next; cur2 = cur2->next)
		{
			if (strcmp(cur2->next->data, node->data) < 0)
			{
				node = cur2->next;
				parent = cur2;
			}
		}
		if (parent == NULL)
			*data = node->next;
		else
			parent->next = node->next;

		node->next = NULL;
		if (*result)
		{
			if (strcmp((*result)->data, node->data) == 0)
			{
				free(node);
				continue;
			}
			data_node_t *i;
			for (i = *result; i->next; i = i->next);
			(i)->next = node;
		}
		else
			*result = node;
	}
}

// Копирование списка
void copy_data(data_node_t *src, data_node_t **dst)
{
	add_data_node(dst, src->data);
	for (data_node_t *cur = src->next, *cur2 = *dst; cur; cur = cur->next, cur2 = cur2->next)
	{
		add_data_node(dst, cur->data);
	}
}

// STDOUT

// Очищение stdin
void clearInputBuf(void) 
{ 
      int garbageCollector; 
      while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF) 
      {}
}

// Напечатать линию
void output_line(int size)
{
	for(int i = 0; i <size; i++)
		printf("-");
	printf("\n");
}

// STDIN

// Ввод слова
int input_word(char **new_element)
{
	printf("Введите слово (макс. длина = %d, латинские буквы):\n", MAX_WORD_LEN);
	*new_element = read_word(stdin);
	if (*new_element == NULL)
		return ERR_INPUT;
	return check_word(*new_element);
}

int check_word(char *new_element)
{
	for (int i = 0; i < strlen(new_element); i++)
	{
		if (!strchr(GOOD_STRING, new_element[i]))
			return ERR_INPUT;
	}
	return OK;
}

// HELPERS

// Максимальное из двух
int max(int r1, int r2)
{
	if (r1 > r2)
		return r1;
	else
		return r2;
}

// Скопировать строку с выделением памяти
char *my_strdup(char *src)
{
	char *dst = calloc(strlen(src), sizeof(char));
	strcpy(dst, src);
	return dst;
}

// FILE

// Прочитать слово из файла
char *read_word(FILE *file)
{
	char word1[MAX_WORD_LEN] = { 0 }, *word2;
	int rc;
	rc = fscanf(file, "%99s", word1);
	if (rc != 1)
		return NULL;
	word2 = my_strdup(word1);
	return word2;
}

// Получить размер файла
int get_file_size(char *filename)
{
	char buf[MAX_WORD_LEN] = { 0 };

	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return 0;

	int rc, size = 0;

	while (!feof(file))
	{
		rc = fscanf(file, "%99s", buf); 
		if (rc != 1)
			break;
		size++;
	}
	fclose(file);
	return size;
}

// Считать файл в список
int read_file(char *filename, data_node_t **data)
{
	int size = get_file_size(filename);

	FILE *file = fopen(filename, "r");
	if (!file)
		return ERR_INPUT;
	char *word;
	int rc;
	for (int i = 0; i < size; i++)
	{
		word = read_word(file);
		rc = check_word(word);
		if (rc != OK)
		{
			printf("В файле содержится не подходящий символ\n");
			return ERR_WORK;
		}
		//printf("word = %s\n", word);
		//if (*cur == NULL)
		//	break;
		add_data_node(data, word);
	}
	fclose(file);
	return OK;
}
