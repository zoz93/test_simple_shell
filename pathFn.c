#include "shell.h"
/**
 * add_node - a function to modify the path
 * @head: the first node of the path
 * @path: .
 * Return: pointer
 */

list_path *add_node(list_path **head, char *path)
{
    char *s_cpy;
    list_path *l;

    l = malloc(sizeof(list_path));
    if (l == NULL)
        return (NULL);

    if (path)
    {
        s_cpy = _strdup(path);
        if (s_cpy == NULL)
        {
            free(l);
            return (NULL);
        }
        l->path = s_cpy;
        l->len = _strlen(s_cpy);
    }
    else
    {
        l->path = NULL;
        l->len = 0;
    }
    l->next = (*head);
    *head = l;
    return (l);
}

/**
 * free_list - frees a list_t list.
 * @head: pointer to a head pointer
 */
void free_list(list_path *head)
{

    if (head == NULL)
    {
        return;
    }
    free_list(head->next);
    if (head->path)
        free(head->path);
    free(head);
}

/**
 * print_list - print list of strings
 * @h: refrance of list_t "linked list of strings"
 * Return: list size
 */
size_t print_list(const list_path *p)
{
    int size;

    size = 0;
    if (p == NULL)
        return (0);

    while (p)
    {
        if (p->path == NULL)
            printf("[0] (nil)\n");
        else
            printf("[%d] %s\n", p->len, p->path);
        p = p->next;
        size++;
    }
    return (size);
}

list_path *set_all_paths_to_list()
{
    char *path_variable, *path_var_cpy, *token;
    list_path *paths_list;
    paths_list = NULL;
    path_variable = _getenv("PATH");
    if (path_variable == NULL)
        return (NULL);

    path_var_cpy = _strdup(path_variable);
    if (path_var_cpy == NULL)
        return (NULL); /*can't cpy*/

    token = strtok(path_var_cpy, ":");
    while (token != NULL)
    {
        add_node(&paths_list, token);
        token = strtok(NULL, ":");
    }
    free(path_var_cpy);
    return (paths_list); /*does not have access*/
}
