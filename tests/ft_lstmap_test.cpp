extern "C"
{
#define new tripouille
#include "libft.h"
#undef new
}

#include "sigsegv.hpp"
#include <string.h>
#include <malloc.h>

void check(bool succes) {if (succes) cout << FG_GREEN << "OK "; else cout << FG_RED << "KO ";}

void freeList(t_list *head) {if (head) freeList(head->next); free(head);}
void * addOne(void * p) {void * r = malloc(sizeof(int)); *(int*)r = *(int*)p + 1; return (r);}
int main(void)
{
	signal(SIGSEGV, sigsegv);
	cout << FG_LGRAY << "ft_lstmap\t: ";

	int tab[] = {0, 1, 2, 3};
	t_list * l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list * m = ft_lstmap(l, addOne, free);
	t_list * tmp = l;
	for (int i = 0; i < 4; ++i)
	{
		check(*(int*)tmp->content == i);
		tmp = tmp->next;
	}
	tmp = m;
	for (int i = 0; i < 4; ++i)
	{
		check(*(int*)tmp->content == i + 1);
		tmp = tmp->next;
	}
	freeList(l); ft_lstclear(&m, free);
	cout << ENDL;
	return (0);
}