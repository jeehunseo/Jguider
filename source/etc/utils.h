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

#ifndef __UTILS_H
#define __UTILS_H

#include "types.h"


/* MINIMUM & MAXIMUM MACRO*/
#ifndef max
	#define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef min
	#define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif

/* BACKWARD COMPATIBILITY*/
BOOL StrnCmp(const U8* str1, U16 len1, const U8* str2, U16 len2);
#define StrnCmp(s1, l1, s2, l2) oMemCmp(s1, l1, s2, l2)


/* UPPER MACRO : LOWER CASE -> UPPER CASE*/
#ifndef ToUpper
	#define ToUpper(ch)  (((ch) >= 'a' && (ch) <= 'z') ? ((ch) - 'a' + 'A') : (ch))
#endif


/* DOUBLE LINKED LIST (CIRCLAR LIST)*/
#ifndef LISTS_DEFINED
typedef struct  _ListNode 
{
    struct _ListNode *Flink;
    struct _ListNode *Blink;

} ListNode;
#endif


/* MACRO AND FUNCTION TO CHECK DOUBLE LINKED LIST AS A TOOL */
#define InitializeListHead(ListHead)	((ListHead)->Flink = (ListHead)->Blink = (ListHead))
#define InitializeListEntry(Node)	((Node)->Flink = (Node)->Blink = 0 )
#define IsEntryAvailable(Node)	(((Node)->Flink == 0))
#define IsListEmpty(ListHead) (((ListHead)->Flink == (ListHead)))
#define GetHeadList(ListHead) (ListHead)->Flink
#define GetTailList(ListHead) (ListHead)->Blink
#define GetNextNode(Node) (Node)->Flink
#define IsNodeConnected(n) (((n)->Blink->Flink == (n)) && ((n)->Flink->Blink == (n)))


void InsertTailList(ListNode* head, ListNode* entry);
void InsertHeadList(ListNode* head, ListNode* entry);
ListNode* RemoveHeadList(ListNode* head);
void RemoveEntryList(ListNode* entry);
BOOL IsNodeOnList(ListNode* head, ListNode* node);
BOOL IsListCircular(ListNode* list);

void MoveList(ListNode* dest, ListNode* src);

#endif
