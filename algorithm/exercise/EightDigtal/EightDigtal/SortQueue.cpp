#include "SortQueue.h"


SortQueue::SortQueue(void)
{
	head = NULL;
}

void SortQueue::enqueue(EightDigital *digital)
{
	if(!inQueue(digital))
	{
		if(this->head == NULL)
		{
			this->head = (Node *)malloc(sizeof(Node));
			this->head->val = digital;
			this->head->next = NULL;
		}
		else if(digital->f < head->val->f)
		{
			Node *node = (Node*)malloc(sizeof(Node));
			node->val = digital;
			node->next = head;
			this->head = node;
		}
		else
		{
			Node *node = (Node*)malloc(sizeof(Node));
			node->val = digital;
			node->next = NULL;
			Node *cur = this->head;

			while(cur->next !=NULL)
			{
				if(node->val->f <cur->next->val->f)
				{
					Node *temp = cur ->next;
					cur->next = node;
					node->next = temp;
					break;
				}
				if(cur->next == NULL)
				{
					cur->next = node;
					break;
				}
				cur = cur->next;
			}
		}
	}
			

}

EightDigital* SortQueue::dequeue()
{
	if(this->head != NULL)
	{
		EightDigital *val = this->head->val;
		Node *temp = head;	
		head = head->next;
			free(temp);
		temp = NULL;
		return val;
	}
	return NULL;
}

bool SortQueue::equal(EightDigital *digital1,EightDigital *digital2)
{

	for(int i =0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if( digital1->array[i][j] != digital2->array[i][j])
			{
				return false;
			}
		}
	}
		return true;
}

bool SortQueue::inQueue(EightDigital *digital)
{
	Node *temp = head;
	while(temp !=NULL)
	{
		if(equal(temp->val,digital) == true)
		{
			return true;
		}
		temp = temp -> next;
	}
	return false;
}

bool  SortQueue::delNode(EightDigital *digital)
{
	if(equal(head->val,digital))
	{

		if(digital->f < head->val->f)
		{
			Node *newHead = (Node *)malloc(sizeof(Node));
			newHead->val = digital;
			newHead->next = head->next;
			free(head);
			head = newHead;
			return true;
		}
	}
		Node *temp = head;

	while(temp->next !=NULL)
	{
		if(equal(temp->next->val,digital) == true)
		{
			if(digital->f < temp->next->val->f)
			{
				Node *delNode = temp->next;
				temp->next = temp->next->next;
				free(delNode);
				enqueue(digital);
				return true;
			}
		}
		temp = temp -> next;
	}
	return false;
}

void SortQueue::refreshNode(EightDigital *digital)
{
	if(equal(head->val,digital))
	{
		if(digital->f < head->val->f)
		{
			head->val->g = digital->g;
			head->val->f = digital->f;
		}
	}
		Node *temp = head;

	while(temp->next !=NULL)
	{
		if(equal(temp->next->val,digital) == true)
		{
			if(digital->f < temp->next->val->f)
			{	
				head->val->g = digital->g;
				head->val->f = digital->f;
			}
		}
		temp = temp -> next;
	}
	
}

EightDigital* SortQueue::getNode(EightDigital *digital)
{
	if(equal(head->val,digital))
	{
		return head->val;
	}
		Node *temp = head;

	while(temp->next !=NULL)
	{
		if(equal(temp->next->val,digital) == true)
		{
			
				return temp->next->val;
			
		}
		temp = temp -> next;
	}
	return NULL;
}