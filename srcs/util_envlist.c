#include "minishell.h"

t_env	*ft_envnew(void *key, void *value, int if_value)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	new->if_value = if_value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;
	t_env	*temp;

	temp = *lst;
	if (temp == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	temp = *lst;
	last = ft_envlast(temp);
	if (last)
	{
		last->next = new;		// 없으면 터짐
		new->prev = last;
	}
	new->next = (NULL);		// 없으면 터짐


/*	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	last = ft_envlast(*lst);
	last->next = new;
	new->next = (NULL);
	*/
}

t_env	*ft_envlast(t_env *lst)
{
	t_env *temp;


	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_env	*ft_envfind(t_env **lst, char *s)
{
	t_env *begin;

	begin = *lst;
	while (begin)
	{
		if ((ft_strcmp(begin->key, s)) == 0)
			return (begin);
		begin = begin->next;
	}
	return NULL;
}
