/* Example for determining Manhattan and Euclidean Distances between a CSV list of users and associated ratings. 
The idea is the shorter distance between two users means the users have similar
preferences */

#include <stdio.h>
#include "lib.h"
 
// Create Hash, from macro expansion, for storing users and their ratings
HASH(user, char *, struct user, rating, HASHSIZE)
// Get nearby users
int distance_compare(distance *d1, distance *d2) {
  int eq;
  if (d1->distance == d2->distance)
    eq = 0;
  else if (d1->distance < d2->distance)
    eq = -1;
  else
    eq = 1;
  return eq;
}

/* Rating comparison function: greatest to lowest */
int rating_compare(const rating *r1, const rating *r2) {
  int eq;
  if (r1->score == r2->score)
    eq = 0;
  else if (r1->score < r2->score)
    eq = 1;
  else
    eq = -1;
  return eq;
}

// TODO struct rec_args {
// args
  
// Returns number of nearby users calculated as near
int nearby_users(distance *ud, const user *u, user **users, int len) {
  int num_users = 0;
  int i = 0;
  int total = 0;
  // parse through users calculating distance
  while (i < HASHSIZE) {   
    const user *tmp = (*users);
    while (tmp && tmp->key != NULL && total < len) { 
      distance d = {tmp->key, euclidean_distance(u->value, tmp->value)};
      if (d.distance) {
        ud[total++] = d; num_users++;
      }
      tmp = tmp->next;
    }
    users++;
    i++; 
  }
  qsort(ud, num_users, sizeof(distance), (int (*)(const void *, const void *)) distance_compare);
  
  return num_users;
}

// TODO array boundary check
void rank (user *heuristic, distance *d, rating **results) {
  user *u = _user_find(heuristic->key);
  int i,j; 
  // TODO: Sort closest user's ratings. Store time stamp of when last sorted. If timestamp fresh don't sort again
  // As opposed to first find non-rated items, then sort non-rated items. 
  // This sort (potentially on a sub array, which would make no sense) would happen each time
  user *nu =  _user_find(d[0].key);
  printf("Closest user is: %s\n", nu->key);
  rating *r = nu->value;
  qsort(r, nu->v_it, sizeof(rating), (int (*)(const void *, const void*)) rating_compare);  
  // Compare ratings
  for (i = 0, j = 0; i < MAXRECOMMENDATIONS && i < nu->v_it; i++) {
    // TODO: Compare smaller array to bigger array
     if (in_rating_array(*r, u->value) == -1) {
       results[j++] = r; 
    }
    r++;
  }
}


char *filename; 
char *uid = NULL; // user id 
user *u;
distance distances[MAXDISTANCES];
rating *results[MAXRECOMMENDATIONS + 1] = {0}; 
int i = 0;

void _recommend(char *);

int main(int argc, char *argv[]) {
   // Open ratings file
   filename = "ratings.csv";
   load_data(filename, MAXLINE, 4, (item_add) _user_add); 
   
 return 0;
}

void _recommend(char *uid) {
   // Allow user to choose a userID
   if (uid == NULL) {
     int i = 0;

     printf("Enter a user id to find ratings\n");
     uid = calloc(UIDSIZE + 1, sizeof(char)); // +1 for \0 
     while (i < UIDSIZE && (uid[i] = getc(stdin)) != '\n') 
       i++; 
     uid[i] = '\0';
     printf("uid: %s\n", uid);
    } 
 
   // Get ratings for a user
   if ((u = _user_find(uid)) != NULL) {
       int i;
       for (i = 0; i < u->v_it; i++) {
	 rating r = u->value[i];
       }
    }  
   
  recommend(results, distances, u, _user_hash, MAXDISTANCES, (const void*) u, (similarity_t) nearby_users, (rank_t) rank);

  printf("\nRecommendations for user %s are:\n", u->key);
  
  while (results[i]) {
    rating *r = results[i];
    printf("%d. %s score: %f\n", i+1, r->key, r->score);
    i++;
  }
  // reset user_id and i;
  uid = NULL;
  i = 0;
}
