#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 #include <string.h>   
 #include <errno.h>  
 #include <unistd.h> 
 #include "hpd_log.h"
 #include "hpd_string_api.h"
 /*------------------------------------------ 
 Name:date_on_request_callback 
 Purpose: This method is called on receiving the service request and after all search and conditional parameters are processed and before applying service delay time.
 Input:   None 
 Return:  The function controls service time. Return values can be: 
    0 - No service delay time. Override service delay time configure if any 
    -1 - Use service delay time as configured 
    >0 - Use service delay time in milli-seconds returned by this method 
------------------------------------------------*/ 
 int date_on_request_callback () 
{ 
  char query_val[1024], query_val_2[1024], http_hdr[1024], http_hdr_2[1024];
  int H=0,h,m,d,D; 
  h=atoi(ns_eval_string("{Hour}"));
  m=atoi(ns_eval_string("{Min}"));
  d=atoi(ns_eval_string("{Date}"));
  D=d+3;
  if (m > 0)
   {
     H=h+1;
     if (h < 23)
        {
         sprintf(query_val,"2020-06-%dT%d:00:00.000Z",d,H);
         sprintf(http_hdr, "Date: %s", query_val);
         ns_set_http_hdr(http_hdr);
         sprintf(query_val_2,"2020-06-%dT%d:00:00",D,H);
         sprintf(http_hdr_2, "Expires: %s", query_val_2);
         ns_set_http_hdr(http_hdr_2);
        }
     else 
        {
         d=d+1;
         sprintf(query_val,"2020-06-%dT%d:00:00.000Z",d,H);
         sprintf(http_hdr, "Date: %s", query_val);
         ns_set_http_hdr(http_hdr);
         sprintf(query_val_2,"2020-06-%dT%d:00:00",D,H);
         sprintf(http_hdr_2, "Expires: %s", query_val_2); 
         ns_set_http_hdr(http_hdr_2);
        }
   }
  else 
   {
    sprintf(query_val,"2020-06-%dT%d:00:00.000Z",d,h);
    sprintf(http_hdr, "Date: %s", query_val);
    ns_set_http_hdr(http_hdr);
    sprintf(query_val_2,"2020-06-%dT%d:00:00",D,H);
    sprintf(http_hdr_2, "Expires: %s", query_val_2);
    ns_set_http_hdr(http_hdr_2);
   }
  return -1;   
}
