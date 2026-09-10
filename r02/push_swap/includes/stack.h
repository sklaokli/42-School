/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:27:15 by sklaokli          #+#    #+#             */
/*   Updated: 2026/01/20 22:44:17 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

/**
 * @brief Doubly linked list node structure for the stack.
 *
 * @param prev    Pointer to the previous node in the list.
 * @param content Pointer to the data stored (void * for generic use).
 * @param next    Pointer to the next node in the list.
 */
typedef struct s_stack	t_stack;

struct					s_stack
{
	t_stack				*prev;
	void				*content;
	t_stack				*next;
};

/**
 * @brief Allocates and creates a new stack node.
 *
 * @param content The content to initialize the new node with.
 * @return Pointer to the new node, or NULL if allocation fails.
 */
t_stack					*stack_new(void *content);

/**
 * @brief Retrieves the last node of the stack.
 *
 * @param head Pointer to the first node of the stack.
 * @return Pointer to the last node of the stack.
 */
t_stack					*stack_last(t_stack *head);

/**
 * @brief Adds a new node to the end of the stack.
 *
 * Handles the linking of both 'next' and 'prev' pointers to maintain
 * the doubly linked list structure.
 *
 * @param head Address of the pointer to the first node.
 * @param new  Pointer to the new node to be added.
 */
void					stack_add(t_stack **head, t_stack *new);

/**
 * @brief Counts the number of nodes in the stack.
 *
 * @param head Pointer to the first node of the stack.
 * @return The number of nodes in the stack.
 */
size_t					stack_size(t_stack *head);

/**
 * @brief Deletes and frees the entire stack.
 *
 * Iterates through the stack, deletes the content using the 'del' function,
 * frees the nodes, and sets the head pointer to NULL.
 *
 * @param head Address of the pointer to the first node.
 * @param del  Function pointer used to delete the content of each node.
 */
void					stack_clear(t_stack **head, void (*del)(void *));

#endif