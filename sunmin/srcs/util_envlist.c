#include "minishell.h"

t_env	*ft_envnew(void *key, void *value)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	return (new);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	last = ft_envlast(*lst);
	last->next = new;
	new->next = (NULL);
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
	return (lst);
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
