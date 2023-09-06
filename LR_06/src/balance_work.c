#include "../inc/balance_work.h"
#include "../inc/amazing_output.h"

typedef struct node node;
/*
struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};
unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}
node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}
node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0 )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}
*/

int create_balance_tree_node(balance_tree_node_t **root, char *string)
{
	*root = calloc(1, sizeof(balance_tree_node_t));

	if (*root == NULL)
		return ERR_CREATE;
	(*root)->data = string;
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->len_right = 0;
	(*root)->len_left = 0;
	return OK;
}

void rotateright(balance_tree_node_t **p) // правый поворот вокруг p
{
	printf("Succes 0\n");
	balance_tree_node_t *q = (*p)->left;
	printf("Succes 1\n");
	q->len_right = (*p)->len_left;
	(*p)->len_left = q->len_right + 1;
	printf("Succes 1\n");
	(*p)->left = q->right;
	printf("Succes 2\n");
	q->right = *p;
	printf("Succes 3\n");
	//output_balance_tree(q);
	//output_balance_tree(*p);

	balance_tree_node_t *buf;
	printf("Succes 4\n");
	buf = q;
	printf("Succes 5\n");
	q = *p;
	printf("Succes 6\n");
	*p = buf;
	printf("Succes 7\n");
}
void rotateleft(balance_tree_node_t **q) // левый поворот вокруг q
{
	printf("Succes 0\n");
	balance_tree_node_t* p = (*q)->right;
	printf("Succes 1\n");

	p->len_left = (*q)->len_right;
	printf("Succes 2\n");
	(*q)->len_right = p->len_left + 1;
	printf("Succes 3\n");

	(*q)->right = p->left;
	printf("Succes 4\n");
	p->left = *q;
	printf("Succes 5\n");
	output_balance_tree(*q);
	output_balance_tree(p);

	balance_tree_node_t *buf;
	printf("Succes 6\n");
	buf = p;
	printf("Succes 7\n");
	p = *q;
	printf("Succes 8\n");
	*q = buf;
	printf("Succes 9\n");
}

void balance(balance_tree_node_t **root)
{
	//fixheight(p);
	//printf("start balance\n");
	if((*root)->len_left - (*root)->len_right == -2)
	{
		int balance_right;
		printf("rotate right\n");
		if ((*root)->right == NULL)
		{
			balance_right = 0;
		}
		else
		{
			balance_right = (*root)->right->len_left - (*root)->right->len_right;
		}
		//printf("start\n");
		if(balance_right > 0)
		{
			//printf("start\n");
			rotateright(&(*root)->right);
		output_balance_tree(*root);
		}
		rotateleft(root);
		//printf("end\n");
	}
	printf("len_left = %d, len_right = %d, balance = %d\n", (*root)->len_left, (*root)->len_right, (*root)->len_left - (*root)->len_right);
	if((*root)->len_left - (*root)->len_right == 2)
	{
		int balance_left;
		if ((*root)->left == NULL)
		{
			balance_left = 0;
		}
		else
		{
			balance_left = (*root)->right->len_left - (*root)->right->len_right;
		}
		printf("rotate left\n");
		if(balance_left > 0 )
			rotateleft(&(*root)->left);
		output_balance_tree(*root);
		rotateright(root);
	}
}

void add_balance_node(balance_tree_node_t **root, char *new_el)
{
	//printf("%s, %s\n", (*root)->data, new_el);
	int rc;
	if (strcmp((*root)->data, new_el) < 0)
	{
		(*root)->len_right++;
		//printf("");
		if ((*root)->right == NULL)
		{
			rc = create_balance_tree_node(&((*root)->right), new_el);
			if (rc != OK)
				printf("Ошибка при создании узла\n");
		}
		if ((*root)->right != NULL)
		{
			add_balance_node(&((*root)->right), new_el);
		}
		balance(root);
	}
	else if (strcmp((*root)->data, new_el) > 0)
	{
		(*root)->len_left++;
		if ((*root)->left == NULL)
		{
			rc = create_balance_tree_node(&((*root)->left), new_el);
			if (rc != OK)
				printf("Ошибка при создании узла\n");
		}
		if ((*root)->left != NULL)
		{
			add_balance_node(&((*root)->left), new_el);
		}
		balance(root);
	}
	balance(root);
}

void make_balance_tree_from_data(balance_tree_node_t **root, data_array_t data)
{
	create_balance_tree_node(root, data.pointers[0]);
	char *new_el;
	for (int i = 0;i < data.len; i++)
	{
		new_el = data.pointers[i];
		//printf("%d\n", i);
		add_balance_node(root, new_el);
		balance(root);
		output_balance_tree(*root);
	}
}