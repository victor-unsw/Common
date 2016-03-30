//
// Created by Demon on 31/03/16.
//

#include "parser.h"

void mark(unsigned char* FLAG, unsigned char position){
    *FLAG |= 1 << position;
}

/*
 * copies from [str,end)
 * Memory Allocated     : str
 * Memory Deallocated   : none
 */
char* copyString(const char* str,const char* end){

    // result size is considered 128 characters at max + 1 '\0'
    char* result = (char*)malloc(sizeof(char)* (MAX_SIZE+1));

    const char* pt = str;

    int i=0;
    while (pt != end)
        result[i++] = *pt++;

    if (i > 128){
        printf("local too long");
        return NULL;
    }

    result[i] = '\0';
    return result;
}


/*
 * CheckWord()
 * - checks the sanity of word.
 */
bool checkWord(const char* w, unsigned char* FLAG){
    int length = strlen(w);

    bool result = true;
    const char* pt = w;

    for (int i = 0; (i < length)&result; ++i) {
        if (i==0){
            if(!isalpha(*(pt+i)))
                result = false;
        }else if(i == (length-1)){
            if (!isalnum(*(pt+i)))
                result = false;
        }else
        if (!isalnum(*(pt+i)) && *(pt+i)!='-')
            result = false;
    }
    if (!result)
        mark(FLAG,WORD_SANITY);

    return result;
}


/*
 * returns number of words in the sequence
 * seperated by '.'
 * - returns -1 IF any word is insane
 *   or any size of any word <= 0
 */
int checkWordSequence(const char* s, unsigned char* FLAG){
    int     S_SIZE   = 10;                                                // initial amount of words in a sequence

    // reserve memory for char**
    char** sequences = (char**)malloc(sizeof(char*)*S_SIZE);
    int total_sequence = 0;

    const char* loc     = s;
    const char* prev    = s;
    const char* end     = s;
    while (*end++);     end--;

    // fill sequences from string s
    while (true) {
        loc = strchr(loc,'.');

        if (!loc){
            // no next location for '.'
            char* temp = copyString(prev,end);
            if (strlen(temp) <= 0 || !checkWord(temp,FLAG))
                return -1;

            sequences[total_sequence++] = temp;
            break;
        }

        else{
            // found one '.'
            char* temp = copyString(prev,loc);
            if (strlen(temp) <= 0 || !checkWord(temp,FLAG))
                return -1;

            sequences[total_sequence++] = temp;
            loc++;
            prev = loc;
        }
    }

    /*
    // show sequences
    for (int j = 0; j < total_sequence; ++j) {
        printf("-> %s\n",sequences[j]);
    }*/

    // free sequences
    for (int i = 0; i < total_sequence; ++i)
        free(sequences[i]);
    free(sequences);

    return total_sequence;
}


/*
 * pareser()
 */
unsigned char parser(const char* email){
    unsigned char FLAG = 0;
    bool result = true;

    size_t email_length = strlen(email);
    printf("%10s : %s [%ld]\n","email",email,email_length);
    char* seperator  = strchr(email,'@');

    if (seperator == NULL){
        mark(&FLAG,LOCAL_EXIST);
        return FLAG;
    }



    // INVARIANT : @ exists
    // --------- get local [local_exist] --------------
    char* local     = (char*)malloc(sizeof(char)* (MAX_SIZE+1));                            // allocated 129 bytes to 'local'
    char* temp      = copyString(email,seperator);                                          // get local from email
    strcpy(local,temp);                                                                     // copy into 'local'
    free(temp);                                                                             // free 'temp' memory

    int local_length= strlen(local);
    if (local_length <= 0) {                                                                // mark local exist flag
        mark(&FLAG,LOCAL_EXIST);
        return FLAG;
    }

    local = (char*)realloc(local,local_length+1);                                          // trim 'local' size as per length+1

    printf("%10s : %s [%ld]\n","local",local,strlen(local));
    int localCheck = checkWordSequence(local,&FLAG);
    if (localCheck < 1){
        mark(&FLAG,LOCAL_CHECK);
    }

    // INVARIANT : local exists
    // --------- get domain [domain_exist] --------------
    if (local_length+1 == email_length){                                                    // if domain doesn't exist
        mark(&FLAG,DOMAIN_EXIST);
        return FLAG;
    }

    char* domain    = (char*)malloc(sizeof(char) * (email_length-local_length));
    strcpy(domain,seperator+1);

    printf("%10s : %s [%ld]\n","domain",domain,strlen(domain));
    int domainCheck = checkWordSequence(domain,&FLAG);
    if (domainCheck < 2)
        mark(&FLAG,DOMAIN_CHECK);


    free(local);
    free(domain);

    return FLAG;
}


/*
 * shows error marked in flag
 */
void showErrors(unsigned char FLAG){
    if (FLAG&INSANE){
        printf("%10s : ", "PROBLEMS");
        for (int i = 0; i < 5; ++i) {
            int x = 0;
            x |= 1 << i;

            if (i == LOCAL_EXIST && (FLAG & x))
                printf("{ LOCAL DOESN'T EXIST }");
            else if(i == DOMAIN_EXIST && (FLAG & x))
                printf("{ DOMAIN DOESN'T EXIST }");
            else if(i == LOCAL_CHECK && (FLAG & x))
                printf("{ LOCAL CARDINALITY }");
            else if(i == DOMAIN_CHECK && (FLAG & x))
                printf("{ DOMAIN CARDINALITY }");
            else if (i == WORD_SANITY && (FLAG & x))
                printf("{ WORD SANITY }");
        }
        printf(" ]\n");
    }
}


