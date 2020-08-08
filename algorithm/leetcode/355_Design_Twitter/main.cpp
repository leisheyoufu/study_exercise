/*
355. Design Twitter
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.
Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

struct Message {
    int tweetId;
    int term;
public:
    Message(int tweetId, int term)
    {
        this->term = term;
        this->tweetId = tweetId;
    }
};

class Twitter
{
public:
    /** Initialize your data structure here. */
    Twitter()
    {
        golbalTerm = 0;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId)
    {
        tweets[userId].push_back(Message(tweetId, golbalTerm++));
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId)
    {

        unordered_set<int> s;
        if(users.find(userId) != users.end()) {
            s = users[userId];
        }
        s.insert(userId);
        unordered_map<int, int> rank;
        for(int user : s) {
            rank[user] = 0;
        }
        vector<int> ret;
        for(int i=0; i<10; i++) {
            int selectedUser, term=-1, selectedTweetId;
            for(unordered_map<int, int>::iterator iter = rank.begin(); iter!=rank.end(); iter++) {
                int user = iter->first;
                if(tweets.find(user) == tweets.end()) {
                    continue;
                }
                int index = tweets[user].size() -1 - iter->second;
                if(index <0) {
                    continue;
                }
                if (tweets[user][index].term > term) {
                    term = tweets[user][index].term;
                    selectedTweetId = tweets[user][index].tweetId;
                    selectedUser = user;
                }
            }
            if (term==-1) {
                break;
            }
            rank[selectedUser]++;
            ret.push_back(selectedTweetId);
        }
        return ret;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId)
    {
        users[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId)
    {
        if (users.find(followerId) == users.end()) {
            return;
        }
        users[followerId].erase(followeeId);
    }
private:
    unordered_map<int, vector<Message>> tweets;
    int golbalTerm;
    unordered_map<int, unordered_set<int>> users;

};

void print(vector<int> v)
{
    for(int id : v) {
        cout << id << " ";
    }
    cout << endl;
}

int main()
{
    Twitter twitter;
    vector<int> ret;

    // User 1 posts a new tweet (id = 5).
    twitter.postTweet(1, 5);

    // User 1's news feed should return a list with 1 tweet id -> [5].
    print(twitter.getNewsFeed(1));

    // User 1 follows user 2.
    twitter.follow(1, 2);

    // User 2 posts a new tweet (id = 6).
    twitter.postTweet(2, 6);

    // User 1's news feed should return a list with 2 tweet ids -> [6, 5].
    // Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
    print(twitter.getNewsFeed(1));

    // User 1 unfollows user 2.
    twitter.unfollow(1, 2);

    // User 1's news feed should return a list with 1 tweet id -> [5],
    // since user 1 is no longer following user 2.
    print(twitter.getNewsFeed(1));
    system("pause");
    return 0;
}
