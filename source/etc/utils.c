/****************************************************************************
 *                                                JeeLab J-Guider ver Zero
 *--------------------------------------------------------------------------------------------------------*
 *
 *  - lisence -
 * 'JeeLab J-Guider' represents the best 'FREE Guider' for tiny microcomputer currently available on the market.
 * This code is 'FREE OF CHARGE' for non-commercial & individual developer only. Both of these conditions should be met!
 * If you are not a individual developer or if you want to use your computer for business purposes,
 * we offer a wide range of more suitable verison providing higher speed and more efficient processing.
 * If you use more infomation, contact us using e-mail or visit our site.
 *
 * e-mail: 
 *              info@jeelab.com
 *  
 * web site:    
 *               http://www.jeelab.com
 *               http://jeelab.tistory.com
 *
 ****************************************************************************/

#include "osapi.h"
#include "utils.h"

/* Insert Target node at the tail of the list */
void InsertTailList(ListNode* head, ListNode* node)
{
	// you have to check whether 'node' is connected before next processing
	// and whether 'head' is circular.
	node->Flink = head;
	node->Blink = head->Blink;
	head->Blink->Flink = node;
	head->Blink = node;

}

/* Insert Target node at the head of the list */
void InsertHeadList(ListNode* head, ListNode* node)
{
	// you have to check whether 'node' is connected befroe next processing
	// and whether 'head' is circular.
	node->Flink = head->Flink;
	node->Blink = head;
	head->Flink->Blink = node;
	head->Flink = node;

}

 /* remove the first node on the list*/
ListNode* RemoveHeadList(ListNode* head)
{
	ListNode* first;

	// require the confirmation whether 'head' is circular list
	// and whether 'head' is circular.
	first = head->Flink;
	first->Flink->Blink = head;
	head->Flink = first->Flink;

	return(first);

}

 /* remove entry from the list*/
void RemoveEntryList(ListNode* node)
{
	// require the confirmation whether 'node' and 'node->Blink' are circular list.
	node->Blink->Flink = node->Flink;
	node->Flink->Blink = node->Blink;
	InitializeListEntry(node);

}

 /*exchange the postion on linked list between 'dest' and 'src'*/
void MoveList(ListNode* dest, ListNode* src)
{
	// require the confirmation whether 'src' is circular list.
	dest->Flink = src->Flink;
	dest->Blink = src->Blink;
	src->Flink->Blink = dest;
	src->Blink->Flink = dest;
	InitializeListHead(src);
}
 
/*return the boolean value whether 'list' is circular.*/
BOOL IsListCircular(ListNode* list)
{
	ListNode* tmp = list;

	if (!IsNodeConnected(list))
		return(FALSE);

	for (tmp = tmp->Flink; tmp != list; tmp = tmp->Flink)
		if (!IsNodeConnected(tmp))
			return(FALSE);

	return(TRUE);

}

 /*retun the value whether target node is on the list*/
BOOL IsNodeOnList(ListNode* head, ListNode* node)
{
	ListNode* tmpNode;

	// require the confirmation whether 'head' is circular list.
	tmpNode = GetHeadList(head);

	while (tmpNode != head)
	{
		if (tmpNode == node)
			return(TRUE);

		tmpNode = tmpNode->Flink;
	}
	return(FALSE);

}
 

