#include "parser.h"


int main() {

    printf("hello");

    const char valid_emails[10][200] = {
            "jas@cse.unsw.edu.au",
            "john-shepherd@hotmail.com",
            "john.a.shepherd@gmail.com",
            "J.Shepherd@unsw.edu.au",
            "j.a.shepherd@acm.org",
            "j-a-shepherd@bargain-hunter.com",
            "jas@a-very-sill-domain.org",
            "john1988@my-favourite.org",
            "x-1@gmail.com",
            "a@b.c.com"
    };

    const char invalid_emails[7][200] = {
            "\"jas\"@cse.unsw.edu.au",
            "j..shepherd@funny.unsw.org",
            "123jas@marketing.abc.com",
            "john@123buynow.com.au",
            "jas@cse",
            "john@cse.unw.@edu.au",
            "x--@gmail.com"
    };



    unsigned char result = 0;
    for (int i = 0; (i < 10); ++i) {
        printf("[%d]\n",(i+1));
        parser(valid_emails[i],&result);
        showErrors(result);
        printf("\n");
    }

    printf("\n\n Invalide check :-\n");
    for (int i = 0; (i < 7); ++i) {
        printf("[%d]\n",(i+1));
        result = 0;
        result = parser(invalid_emails[i]);
        showErrors(result);
        printf("\n");

    }


    return 0;
}