typedef struct {
    int age;
    char *name;
} person;

double geodist(double lat1, double lon1, double lat2, double lon2);
int palindrome(char *str);
void setperson(person *p);
void initpeople(person **people, int numpeople);
