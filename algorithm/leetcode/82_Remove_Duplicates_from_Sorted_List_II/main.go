/*
82. Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	dummy := &ListNode{
		Val:  -1,
		Next: head,
	}
	next := head.Next
	prev := dummy
	for next != nil {
		curr := prev.Next
		if curr.Val != next.Val {
			if curr.Next == next {
				prev.Next = curr
				prev = curr
			} else {
				prev.Next = next
			}
		}
		next = next.Next
	}
	if prev.Next.Next != nil {
		prev.Next = nil
	}
	return dummy.Next
}

func main() {
	//v := [...]int{1, 1, 1, 2, 3, 3} // 2
	//v := [...]int{1, 1, 1, 2, 3} // 2 3
	v := [...]int{1, 2, 3, 3, 4, 4, 5} // 1,2,5
	head := &ListNode{Val: v[0]}
	curr := head
	for i := 1; i < len(v); i++ {
		node := &ListNode{Val: v[i]}
		curr.Next = node
		curr = curr.Next
	}
	for curr = head; curr != nil; curr = curr.Next {
		fmt.Printf("%d ", curr.Val)
	}
	fmt.Printf("\n")
	head = deleteDuplicates(head)
	for curr = head; curr != nil; curr = curr.Next {
		fmt.Printf("%d ", curr.Val)
	}
	fmt.Printf("\n")
}
