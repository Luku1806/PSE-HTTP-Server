#include "../include/http_utils.h"



int hexToDec(string *hex){

    unsigned int val = 0;

    for(unsigned int i=0;i<hex->len;i++)
        if(hex->str[i] <= 57)
            val += (hex->str[i]-48)*(1<<(4*(hex->len-1-i)));
        else
            val += (hex->str[i]-55)*(1<<(4*(hex->len-1-i)));

    return val;


}


string *decodeURL(string *url){


    for(int i = 0; i < url->len; i++){

        if(url->str[i] == '%'){

            //TODO wenn str replace done ist



        }


    }


}








